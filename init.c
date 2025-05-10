/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:34 by aramos            #+#    #+#             */
/*   Updated: 2025/05/10 19:08:15 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**pipes_forks(t_pipex *pipex, int argc, char **argv)
{
	int		**pipes;
	pid_t	pid;
	int		i;

	i = 0;
	pipes_init(&pipes, argc);
	while (i < pipex->cmd_count)
	{
		if (i < pipex->cmd_count - 1 && pipe(pipes[i]) == -1)
			ft_printf("Error with pipes\n");
		pid = fork();
		if (pid < 0)
			ft_printf("Error with fork\n");
		if (pid == 0)
			child_process(i, argv, pipex, pipes);
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < pipex->cmd_count - 1)
			close(pipes[i][1]);
		i++;
	}
	return (pipes);
}

int	pipes_init(int ***pipes, int argc)
{
	int	i;

	i = 0;
	*pipes = malloc((argc - 4) * sizeof(int *));
	if (!*pipes)
		return (ft_printf("Error with malloc\n"), 1);
	while (i < argc - 4)
		*pipes[i++] = malloc(2 * sizeof(int));
	return (0);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->infile = open(argv[1], O_RDONLY);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex->cmd_count = argc - 3;
	pipex->env = envp;
	if (pipex->infile < 0 || pipex->outfile < 0)
		return (perror("File Error\n"), 1);
	return (0);
}
