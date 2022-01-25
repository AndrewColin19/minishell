/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:18:49 by acolin            #+#    #+#             */
/*   Updated: 2022/01/07 19:33:09 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec(char *path, char **splited, int in, int out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (execve(path, splited, g_env.var_env) == -1)
			printf("Error\n");
	}
	else
	{
		waitpid(pid, &status, 0);
		g_env.status = WEXITSTATUS(status);
	}
}

char	*get_exec_path(char *cmd, char *path, int *exist)
{
	char	**splited_path;
	int		i;

	i = 0;
	splited_path = ft_split(get_var_env(&g_env, "PATH"), ':');
	if (open(cmd, O_RDONLY) > -1)
	{
		*exist = 1;
		return (cmd);
	}
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

void	cmd_exec(t_cmd *cmd, int in, int out)
{
	char	*path;
	int		exist;

	exist = 0;
	path = NULL;
	path = get_exec_path(cmd->kw, path, &exist);
	if (exist == 0)
	{
		put_error(": command not found", cmd->cmd);
		g_env.status = 127;
		return ;
	}
	ft_exec(path, cmd->args, in, out);
}
