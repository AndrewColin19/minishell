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

char    *get_file(char *cmd)
{
    int     i;
	int		j;
	char	*file;

    i = 0;
	while (cmd[i] != '<')
		i++;
	while (cmd[i] == '<' || cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[j] != ' ')
		j++;
	file = malloc(j - i + 2);
	j = 0;
	while (cmd[i] != ' ')
		file[j++] = cmd[i++];
	return (file);
}

int		read_file(char *cmd)
{
	char	*file;
	int		fd;
	char	c;
	int		pipes[2];

	file = get_file(cmd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory", file);//errno
		free(file);
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

int		heredoc(char *cmd)
{
	char	*kw;
	char	*line;
	int		pipes[2];

	pipe(pipes);
	kw = get_file(cmd);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, kw) == 0)
		{
			close(pipes[1]);
			return (pipes[0]);
		}
		write(pipes[1], line, ft_strlen(line));
		write(pipes[1], "\n", 1);
	}
}