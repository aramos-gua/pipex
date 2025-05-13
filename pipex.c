/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/13 18:33:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_builder(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	int		full_path_len;

	i = 0;
	while (paths[i])
	{
		full_path_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(full_path_len);
		if (!full_path)
		{
			i++;
			continue ;
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", full_path_len);
		ft_strlcat(full_path, cmd, full_path_len);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	i = -1;
	path_env = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_env = env[i] + 5;
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = path_builder(cmd, paths);
	if (!full_path)
		return (free_split(paths), NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (free_split(paths), NULL);
}

void	execute_command(char *cmd_str, t_pipex *pipex, int **pipes)
{
	char	**args;
	char	*path;

	args = ft_split(cmd_str, ' ');
	if (!args || !args[0] || !args[0][0])
		execute_command_exit(pipex, args, pipes);
	path = get_command_path(args[0], pipex->env);
	if (!path)
		execute_command_exit(pipex, args, pipes);
	if (execve(path, args, pipex->env) == -1)
	{
		perror("execve");
		free(path);
		free_split(args);
		free_pipes(pipex->cmd_count, pipes);
		exit (1);
	}
	free(path);
	free_split(args);
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_pipex	pipex;
	pid_t	last_pid;

	last_pid = -1;
	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile\
			\"cmd1 [options]\" \"cmd2 [options]\" outfile\n"), 1);
	pipex_init(&pipex, argc, argv, envp);
	pipes = pipes_forks(&pipex, argv, &last_pid);
	close(pipex.infile);
	close(pipex.outfile);
	wait_children(&pipex, last_pid);
	free_pipes(pipex.cmd_count, pipes);
	return (pipex.return_val);
}
