/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:58 by aramos            #+#    #+#             */
/*   Updated: 2025/05/09 11:06:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		cmd_count;
	//int		pipe_fd[2];
	int		prev_fd;
	char	**env;
}	t_pipex;

int		child_process(int i, char **argv, t_pipex *pipex, int pipes[][2]);
void	execute_command(char *cmd_str, t_pipex *pipex);
void	free_split(char **arr);

#endif
