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

void	child_routine(pid_t pid, int *number)
{
	printf("Child routine started, pid is %d, number is: %d\n", pid, *number);
}

void	parent_routine(pid_t pid, int *number)
{
	printf("parent routine started\n");
	*number = 24;
	printf("PID is %d, number is %d\n", pid, *number);
}

int	main(void)
{
	pid_t	pid;
	int		number;

	number = 42;
	printf("Before forking, the number is %d\n", number);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
		child_routine(pid, &number);
	else if (pid > 0)
		parent_routine(pid, &number);
	return (0);
}
