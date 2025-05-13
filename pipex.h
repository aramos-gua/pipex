/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:58 by aramos            #+#    #+#             */
/*   Updated: 2025/05/13 13:38:08 by alex             ###   ########.fr       */
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
	int		heredoc_on;
	int		prev_fd;
	char	**env;
	int		return_val;
}	t_pipex;

int		pipes_init(int ***pipes, int cmd_count);
int		pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
void		child_process(int i, char **argv, t_pipex *pipex, int **pipes);
void	execute_command(char *cmd_str, t_pipex *pipex, int **pipes);
void	free_split(char **arr);
void	close_pipes(t_pipex *pipex, int **pipes);
void	free_pipes(int argc, int **pipes);
int		**pipes_forks(t_pipex *pipex, char **argv, pid_t *last_pid);
int		read_heredoc(char *delimiter);

#endif
