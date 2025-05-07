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

//ping process
void	first_command()
{
	close(fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(infile_fd);
	close(outfile_fd);
	excecute_commands(argv, envp);
}

void	second_command()
{
	char	*arr[] = {"grep", "rtt", NULL};
	char	*env[] = {NULL};

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve("/bin/grep", arr, env);
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
		perror("File Error-52");
	while (i < pipex.cmd_count
	{
		pid = fork();
		if (pid == -1)
			perror("Fork Error-57")
	}
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
		first_command(argc, argv, fd);
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
		second_command(fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
