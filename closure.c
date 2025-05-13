/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:14:23 by aramos            #+#    #+#             */
/*   Updated: 2025/05/13 14:21:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex, int **pipes)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	free_pipes(int cmd_count, int **pipes)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
		free(pipes[i++]);
	free(pipes);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	execute_command_exit(t_pipex *pipex, char **args, int **pipes)
{
	write(2, "pipex: Command Not Found\n", 25);
	free_split(args);
	free_pipes(pipex->cmd_count, pipes);
	exit(127);
}
