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

void	ft_exec(char *path, char **splited, char **env, char *input, int fd)
{
	pid_t	pid;
	int		status;
	int 	p_input[2];

	pid = fork();
	if (pid == 0)
	{
		if (input != NULL)
		{
			pipe(p_input);
			dup2(p_input[0], STDIN_FILENO);
			write(p_input[1], input, ft_strlen(input));
			close(p_input[0]);
			close(p_input[1]);
		}
		dup2(fd, STDOUT_FILENO);
		if (execve(path, splited, env) == -1)
			printf("Error\n");
	}
	else
		waitpid(pid, &status, 0);
}

void	cmd_exec(char *cmd, char **env, char *input, int fd)
{
	char	**splited;
	char	*path;

	splited = ft_split(cmd, ' ');
	path = ft_strjoin(CMD_PATH, splited[0]);
	if (open(path, O_RDONLY) == -1)
	{
		put_error(": command not found", cmd);
		return ;
	}
	else
		ft_exec(path, splited, env, input, fd);
}
