/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:44:31 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/26 18:14:14 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_kw(char *cmd, char type)
{
	int		i;
	int		j;
	char	*file;

	i = inc_i(cmd, type);
	while (cmd[i] == type || cmd[i] == ' ')
		i++;
	j = i;
	while (ft_isalnum(cmd[j]))
		j++;
	if (j == i)
	{
		printf("syntax error near unexpected token\n");
		exit(1);
	}
	file = malloc(j - i);
	j = 0;
	while (cmd[i] != ' ')
		file[j++] = cmd[i++];
	return (file);
}

int	read_file(t_redir *r)
{
	int		fd;
	char	c;
	int		pipes[2];

	fd = open(r->kw, O_RDONLY);
	if (fd < 0)
	{
		perror(r->kw);
		return (-1);
	}
	pipe(pipes);
	while (read(fd, &c, 1))
		write(pipes[1], &c, 1);
	close(pipes[1]);
	return (pipes[0]);
}

int	heredoc(t_redir *r)
{
	char	*line;
	int		pipes[2];

	pipe(pipes);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, r->kw) == 0)
		{
			close(pipes[1]);
			return (pipes[0]);
		}
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
	}
}

int	write_redirection(int input, int fd)
{
	char	c;

	while (read(input, &c, 1))
		write(fd, &c, 1);
	close(fd);
	return (-1);
}

int	ft_create_file(t_redir *redir)
{
	open(redir->kw, O_CREAT, S_IRWXU);
	if (redir->type)
		return (open(redir->kw, O_APPEND | O_RDWR));
	else
		return (open(redir->kw, O_TRUNC | O_RDWR));
}
