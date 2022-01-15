/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:44:31 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/05 15:26:58 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *get_kw(char *cmd, char type)
{
    int     i;
	int		j;
	char	*file;

    i = inc_i(cmd, type);
	while (cmd[i] == type || cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[j] != ' ')
		j++;
	file = malloc(j - i);
	j = 0;
	while (cmd[i] != ' ')
		file[j++] = cmd[i++];
	return (file);
}

int		read_file(t_redir *r)
{
	int		fd;
	char	c;
	int		pipes[2];

	fd = open(r->kw, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory", r->kw);//errno
		return (0);
	}
	pipe(pipes);
	while (read(fd, &c, 1))
		write(pipes[1], &c, 1);
	close(pipes[1]);
	return (pipes[0]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*sa;
	unsigned char	*sb;
	size_t			i;

	sa = (unsigned char *) s1;
	sb = (unsigned char *) s2;
	i = 0;
	while (sa[i] == sb[i] && sa[i] != '\0' && sb[i] != '\0')
		i++;
	return (sa[i] - sb[i]);
}

int		heredoc(t_redir *r)
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