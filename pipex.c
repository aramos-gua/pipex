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

int	main(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		//child process
		int		file;
		int		file2;
		int		err;
		//char	*arr[] = {"ping", "-c 3", "google.com", NULL};
		//char	*env[] = {NULL};

		file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return (2);
		printf("The fd to pingResults.txt is %d\n", file);
		file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n", file2);
		close(file);

		err = execlp("ping", "ping", "-c 1", "google.com", NULL);
		if (err == -1)
			return (3);
	}
	return (0);
}
