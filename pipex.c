/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/03 19:11:49 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

//ping process
void	first_command(int *fd)
{
	char	*arr[] = {"ping", "-c", "5", "google.com", NULL};
	char	*env[] = {NULL};

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve("/bin/ping", arr, env);
}

void	second_command(int *fd)
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
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		first_command(fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		return (3);
	if (pid2 == 0)
	{
		second_command(fd);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
