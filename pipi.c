/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:50 by alex              #+#    #+#             */
/*   Updated: 2025/05/09 16:24:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int	pids[argc - 3];
	int	pipes[argc - 2][2];
	int	i;
	int	processes;

	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile \"cmd1 [options]\" \"cmd2 [options]\" outfile\n"), 1);
	i = 0;
	processes = argc - 3;
	while (i < processes + 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error with pipes\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while	(i < processes)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with fork\n");
			return (0);
		}
		if (pids[i] == 0)
		{
			//child process
			int	j;

			j = 0;
			while (j < processes + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			int	x;
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				printf("Error reading [%d]\n", i);
				return (1);
			}
			printf("(%d) Got %d\n", i, x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error writing\n");
				return (1);
			}
			printf("(%d) Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][0]);
			return (0);
		}
		i++;
	}
	//main
	int	y;

	y = ft_atoi(argv[1]);
	printf("Main sent %d\n", y);
	if (write(pipes[0][1], &y, sizeof(int)) == -1)
	{
		printf("Error writing\n");
		return (1);
	}
	if (read(pipes[processes][0], &y, sizeof(int)) == -1)
	{
		printf("Error reading[%d]\n", processes);
		return (1);
	}
	printf("the result is %d\n", y);
	while (i++ < processes)
		wait(NULL);
	return (0);
}
