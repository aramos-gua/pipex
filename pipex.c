/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/06 22:57:24 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int i, char **argv, t_pipex *pipex)
{
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipex->prev_fd, STDIN_FILENO);
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	if (pipex->prev_fd != -1)
		close(prefix->prev_fd);
	close(pipex->infile);
	close(pipex->outfile);
	excecute_command(argv[2 + i], pipex);
}

void	excecute_command(char *cmd_str, t_pipex *pipex)
{
	char	**args;
	char	*path;

	args = ft_split(cmd_str, ' ');
	if (!args || !args[0])
		perror("Command Parse Error");
	path = get_command_path(args[0], pipex->envp);
	if (!path)
	{
		perror("Command Not Found");
		free_split(args);
	}
	execve(path, args, pipex->envp);
	perror("execve Error");
	free(path);
	free_split(args);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_pipex	pipex;
	pid_t	pid;
	int		i;

	if (argc < 5)
		return (("Usage: ./pipex infile cmd1 cmd2 outfile"), 1);
	pipex.infile = open(argv[1], O_RDONLY); 
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.cmd_count = argc - 3;
	pipex.prev_fd = -1;
	pipex.envp = envp;
	if (pipex.infile < 0 || pipex.outfile < 0)
		perror("File Error");
	while (i < pipex.cmd_count)
	{
		if (i < pipex.cmd_count - 1 && pipe(pipex.pipe_fd) == -1)
			perror("Pipe Error");
		pid = fork();
		if (pid == -1)
			perror("Fork Error");
		if (pid == 0)
			child_process(i, argv, &pipex);
		if (pipex.prev_fd != -1)
			close(pipex.prev_fd);
		if (i < pipex.cmd_count - 1)
			pipex_prev_fd = pipex.pipe_fd[0];
		close(pipex.pipe_fd[1]);
	}
	while (wait(NULL) > 0);
	return (0);
}

