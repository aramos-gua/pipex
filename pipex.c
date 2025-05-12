/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/12 17:19:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int i, char **argv, t_pipex *pipex, int **pipes)
{
	int	j;

	j = -1;
	if (i == 0)
	{
		if (pipex->infile >= 0)
			dup2(pipex->infile, STDIN_FILENO);
		else
		{
			write(2, "pipex: Infile Error\n", 20);
			exit(1);
		}
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i == pipex->cmd_count - 1)
	{
		if (pipex->outfile >= 0)
			dup2(pipex->outfile, STDOUT_FILENO);
		else
		{
			write(2, "pipex: Outfile Error\n", 22);
			exit(1);
		}
	}
	else
		dup2(pipes[i][1], STDOUT_FILENO);
	while (++j < pipex->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	close(pipex->infile);
	close(pipex->outfile);
	execute_command(argv[2 + i], pipex);
}

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

	i = 0;
	path_env = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = path_builder(cmd, paths);
	if (!full_path)
	{
		free_split(paths);
		return (NULL);
	}
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (free_split(paths), NULL);
}

void	execute_command(char *cmd_str, t_pipex *pipex)
{
	char	**args;
	char	*path;

	args = ft_split(cmd_str, ' ');
	if (!args || !args[0] || !args[0][0])
	{
		write(2, "pipex: Command Not Found\n", 25);
		if (args)
			free_split(args);
		exit(127);
	}
	path = get_command_path(args[0], pipex->env);
	if (!path)
	{
		write(2, "pipex: Command Not Found\n", 25);
		free_split(args);
		exit(127);
	}
	if (execve(path, args, pipex->env) == -1)
	{
		perror("execve");
		free(path);
		free_split(args);
		exit (1);
	}
	free(path);
	free_split(args);
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;
	t_pipex	pipex;
	int		status;
	pid_t	last_pid;
	pid_t	pid;
	int		i;

	last_pid = -1;
	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile\
			\"cmd1 [options]\" \"cmd2 [options]\" outfile\n"), 1);
	if (pipex_init(&pipex, argc, argv, envp) == 1)
		return (pipex.return_val);
	pipes = pipes_forks(&pipex, argc, argv, &last_pid);
	close(pipex.infile);
	close(pipex.outfile);
	close_pipes(&pipex, pipes);
	while (i++ < pipex.cmd_count)
	{
		pid = wait(&status);
		if (pid == last_pid && WIFEXITED(status))
			pipex.return_val = WIFEXITED(status);
	}
	free_pipes(argc, pipes);
	return (pipex.return_val);
}
