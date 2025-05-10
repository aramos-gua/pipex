/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:14:23 by aramos            #+#    #+#             */
/*   Updated: 2025/05/10 18:42:26 by aramos           ###   ########.fr       */
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

void	free_pipes(int argc, int **pipes)
{
	int	i;

	i = 0;
	while (i < argc - 4)
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
