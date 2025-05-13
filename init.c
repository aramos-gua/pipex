/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:34 by aramos            #+#    #+#             */
/*   Updated: 2025/05/13 14:01:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	p_f_helper(t_pipex *pipex, pid_t *last_pid, char **argv, int **pipes)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_printf("Error with fork\n");
			exit(1);
		}
		if (i == pipex->cmd_count -1)
			*last_pid = pid;
		if (pid == 0)
			child_process(i, argv, pipex, pipes);
		i++;
	}
}

int	**pipes_forks(t_pipex *pipex, char **argv, pid_t *last_pid)
{
	int		**pipes;
	int		i;

	i = 0;
	pipex->return_val = 0;
	pipes_init(&pipes, pipex->cmd_count);
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error with pipes\n");
			exit(1);
		}
		i++;
	}
	p_f_helper(pipex, last_pid, argv, pipes);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return (pipes);
}

int	pipes_init(int ***pipes, int cmd_count)
{
	int	i;

	i = 0;
	*pipes = malloc((cmd_count - 1) * sizeof(int *));
	if (!*pipes)
		return (ft_printf("Error with malloc\n"), 1);
	while (i < cmd_count - 1)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!(*pipes)[i])
		{
			while (--i >= 0)
				free((*pipes)[i]);
			free(*pipes);
			ft_printf("Error with malloc\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->heredoc_on = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	pipex->env = envp;
	if (pipex->heredoc_on)
	{
		pipex->infile = read_heredoc(argv[2]);
		pipex->outfile = open(argv[argc - 1], O_CREAT | \
			O_WRONLY | O_APPEND, 0644);
		pipex->cmd_count = argc - 4;
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			pipex->return_val = 1;
		pipex->outfile = open(argv[argc - 1], O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
		pipex->cmd_count = argc - 3;
	}
	if (pipex->outfile < 0)
	{
		ft_printf("Error with %s permissions\n", argv[argc - 1]);
		pipex->return_val = 1;
		close(pipex->infile);
	}
	return (0);
}
