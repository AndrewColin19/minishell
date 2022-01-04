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

void	ft_exec(char *path, char **splited, int in, int out)
{
	pid_t	pid;
	int		status;
	char	**env;

	env = g_env.var_env;
	pid = fork();
	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
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

void	cmd_exec(char *cmd, int in, int out)
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
	ft_exec(path, splited, in, out);
}
