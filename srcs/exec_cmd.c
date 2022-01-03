/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:18:49 by acolin            #+#    #+#             */
/*   Updated: 2021/12/16 16:29:48 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char 	*read_result(int fd)
{
	char 	*result;
	char 	*buf;

	result = malloc(2);
	buf = malloc(2);
	result[1] = '\0';
	buf[1] = '\0';
	if (read(fd, result, 1) <= 0)
		return (NULL);
	while (read(fd, buf, 1) > 0)
		result = ft_strjoin(result, buf);
	close(fd);
	return (result);
}

void	ft_exec(char *path, char **splited, char **env, int *fd, int last)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDIN_FILENO);
		if (!last)
			dup2(fd[0], STDOUT_FILENO);
		if (execve(path, splited, env) == -1)
			printf("Error\n");
	}
	else
		waitpid(pid, &status, 0);
}

char	*get_exec_path(char *cmd, char *path, int *exist)
{
	char	**splited_path;
	int		i;

	i = 0;
	splited_path = ft_split(get_var_env(&g_env, "PATH"), ':');
	while (splited_path[i])
	{
		splited_path[i] = ft_strjoin(splited_path[i], "/");
		path = ft_strjoin(splited_path[i], cmd);
		if (open(path, O_RDONLY) > -1)
		{
			*exist = 1;
			return (path);
		}
		i++;
	}
	*exist = 0;
	return (NULL);
}

void	cmd_exec(char *cmd, char **env, int *fd, int last)
{
	char	**splited;
	char	*path;
	int		exist;

	splited = ft_split(cmd, ' ');
	exist = 0;
	path = NULL;
	path = get_exec_path(splited[0], path, &exist);
	if (exist == 0)
	{
		put_error(": command not found", cmd);
		return ;
	}
	ft_exec(path, splited, env, fd, last);
}
