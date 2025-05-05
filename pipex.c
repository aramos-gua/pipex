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

int	main(void)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		//child process
		close(fd[0]);
		char	str[200];
		printf("Input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';

		int len = strlen(str) + 1;
		if (write(fd[1], &len, sizeof(int)) == -1)
			return (4);

		if (write(fd[1], str, sizeof(char) * len) == -1)
			return (3);
		close(fd[1]);
	}
	else
	{
		//parent process
		close(fd[1]);
		char	str_p[200];
		int		len_p;

		if (read(fd[0], &len_p, sizeof(int)) == -1)
			return (5);
		if (read(fd[0], str_p, sizeof(char) * len_p) == -1)
			return (6);
		printf("Received %s \n", str_p);
		close(fd[0]);
		wait(NULL);
	}
	return (0);
}
