/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:18 by aramos            #+#    #+#             */
/*   Updated: 2025/05/09 12:51:09 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_process(int i, char **argv, t_pipex *pipex, int pipes[][2])
{
	int	j;

	j = 0;
	if (i == 0)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else if (i == pipex->cmd_count - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	while (j < pipex->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	close(pipex->infile);
	close(pipex->outfile);
	execute_command(argv[2 + i], pipex);
	return (ft_printf("Error evexve\n"), 1);
}

char	*get_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env = NULL;
	char	*full_path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break ;
		}
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
			continue ;
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_split(paths);
	return (NULL);
}

void	execute_command(char *cmd_str, t_pipex *pipex)
{
	char	**args;
	char	*path;

	args = ft_split(cmd_str, ' ');
	if (!args || !args[0])
	{
		perror("Command Parse Error");
		exit(1);
	}
	path = get_command_path(args[0], pipex->env);
	if (!path)
	{
		perror("Command Not Found");
		free_split(args);
		exit(1);
	}
	execve(path, args, pipex->env);
	perror("execve Error");
	free(path);
	free_split(args);
	ft_printf("Executed %s successfully\n", args[0]);
	exit(1);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i]);
	free(arr);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipes[argc - 4][2];
	pid_t	pid;
	t_pipex	pipex;
	int		i;
	int		j;

	i = 0;
	if (argc < 5)
		return (ft_printf("Usage: ./pipex infile \"cmd1 [options]\" \"cmd2 [options]\" outfile\n"), 1);
	pipex.infile = open(argv[1], O_RDONLY); 
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipex.cmd_count = argc - 3;
	pipex.prev_fd = -1;
	pipex.env = envp;
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (ft_printf("File Error\n"), 1);
	while (i < pipex.cmd_count)
	{
		if (i < pipex.cmd_count - 1 && pipe(pipes[i]) == -1)
			return (ft_printf("Error with pipes\n"), 1);
		pid = fork();
		if (pid < 0)
			return  (ft_printf("Error with fork\n"), 1);
		if (pid == 0)
			child_process(i, argv, &pipex, pipes);
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < pipex.cmd_count - 1)
			close(pipes[i][1]);
		if (pipex.prev_fd != -1)
			close(pipex.prev_fd);
	}
	close(pipex.infile);
	close(pipex.outfile);
	while (wait(NULL) > 0)
		;
	return (0);
}
