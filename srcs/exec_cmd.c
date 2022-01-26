/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:18:49 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 17:45:28 by acolin           ###   ########.fr       */
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
			perror(path);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_env.status = WEXITSTATUS(status);
	}
	free(path);
}

void	free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*get_exec_path(char *cmd, char *path, int *exist)
{
	char	**splited_path;
	char	*test;
	int		i;

	i = 0;
	splited_path = ft_split(get_var_env("PATH"), ':');
	while (splited_path[i])
	{
		test = ft_strjoin(splited_path[i], "/");
		path = ft_strjoin(test, cmd);
		free(test);
		if (open(path, O_RDONLY) > -1)
		{
			*exist = 1;
			free_tab(splited_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(splited_path);
	*exist = 0;
	return (NULL);
}

int	is_path(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	cmd_exec(t_cmd *cmd, int in, int out)
{
	char	*path;
	int		exist;

	exist = 0;
	path = NULL;
	if (open(cmd->kw, O_RDONLY) > -1)
	{
		exist = 1;
		path = ft_strdup(cmd->kw);
	}
	else if (!is_path(cmd->kw))
		path = get_exec_path(cmd->kw, path, &exist);
	if (exist == 0)
	{
		put_error(": command not found", cmd->cmd);
		g_env.status = 127;
	}
	else
		ft_exec(path, cmd->args, in, out);
}
