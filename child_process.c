/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:28:55 by alex              #+#    #+#             */
/*   Updated: 2025/05/13 15:26:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(int i, t_pipex *pipex, int **pipes)
{
	int	devnull;

	if (pipex->infile >= 0)
		dup2(pipex->infile, STDIN_FILENO);
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	dup2(pipes[i][1], STDOUT_FILENO);
}

void	last_command(t_pipex *pipex, int **pipes)
{
	if (pipex->outfile >= 0)
		dup2(pipex->outfile, STDOUT_FILENO);
	else
	{
		write(2, "pipex: Outfile Error\n", 22);
		free_pipes(pipex->cmd_count, pipes);
		exit(1);
	}
}

int	heredoc(t_pipex *pipex, char **argv, int i, int **pipes)
{
	int	cmd_shift;

	if (pipex->heredoc_on)
		cmd_shift = 3;
	else
		cmd_shift = 2;
	if (!argv[cmd_shift + i] || !argv[cmd_shift + i][0])
	{
		write(2, "pipex: Command Not Found\n", 25);
		free_pipes(pipex->cmd_count, pipes);
		exit(127);
	}
	return (cmd_shift);
}

void	child_process(int i, char **argv, t_pipex *pipex, int **pipes)
{
	int	j;
	int	cmd_shift;

	j = -1;
	cmd_shift = heredoc(pipex, argv, i, pipes);
	if (i == 0)
		first_command(i, pipex, pipes);
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i == pipex->cmd_count - 1)
		last_command(pipex, pipes);
	else
		dup2(pipes[i][1], STDOUT_FILENO);
	while (++j < pipex->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	close(pipex->infile);
	close(pipex->outfile);
	execute_command(argv[cmd_shift + i], pipex, pipes);
}

int	wait_children(t_pipex *pipex, pid_t last_pid)
{
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = wait(&status);
		if (pid == last_pid && WIFEXITED(status))
			pipex->return_val = WEXITSTATUS(status);
		i++;
	}
	return (pipex->return_val);
}
