/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:10:35 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/05 16:29:02 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_create_file(t_redir *redir)
{
	open(redir->kw, O_CREAT, S_IRWXU);
	if (redir->type)
		return (open(redir->kw, O_APPEND | O_RDWR));
	else
		return (open(redir->kw, O_TRUNC | O_RDWR));
}

void	get_redirect(t_redir **redir, int *in, int *out)
{
	t_redir	*r;

	r = *redir;
	while (r)
	{
		if (r->type == 0 || r->type == 1)
			*out = ft_create_file(r);
		else if (r->type == 2)
			*in = read_file(r);
		else if (r->type == 3)
			*in = heredoc(r);
		r = r->next;
	}
}

int 	inc_i(char *cmd, char c)
{
	int 	i;
	char 	quote;

	i = 0;
	while (cmd[i] && cmd[i] != c)
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			if (cmd[i - 1] != '\\')
			{
				quote = cmd[i];
				i++;
				while (cmd[i] && cmd[i] != quote)
				{
					if (cmd[i] == quote && cmd[i - 1] != '\\')
						break ;
					else
						i++;
				}
			}
		}
		i++;
	}
	return (i);
}

void	delete_redirection(char **cmd, char c)
{
	int		i;
	int		j;
	int		nb_char;

	i = inc_i(cmd[0], c);
	j = i;
	while ((cmd[0][j] == c || cmd[0][j] == ' ') && cmd[0][j])
		j++;
	while (cmd[0][j] != ' ' && cmd[0][j])
		j++;
	while (cmd[0][j] == ' ' && cmd[0][j])
		j++;
	nb_char = j - i;
	while (nb_char--)
	{
		j = i;
		while (cmd[0][j])
		{
			cmd[0][j] = cmd[0][j + 1];
			j++;
		}
	}
}

int 	ignore_quotes(char *cmd, int i)
{
	int 	j;
	char 	quote;

	quote = cmd[i];
	j = 1;
	while (cmd[i + j])
	{
		if (cmd[i + j] == quote && cmd[i + j - 1] != '\\')
				return (j);
		j++;
	}
	return (j);
}

t_redir	*get_redirection(char **cmd, int i)
{
	t_redir	*redir;

	while (cmd[0][i])
	{
		if ((cmd[0][i] == '\'' || cmd[0][i] == '\"') && cmd[0][i - 1] != '\\')
			i += ignore_quotes(cmd[0], i);
		else if (cmd[0][i] == '>' || cmd[0][i] == '<')
		{
			redir = malloc(sizeof(t_redir));
			if (cmd[0][i] == '>' && cmd[0][i + 1] == '>')
				redir->type = 1;
			else if (cmd[0][i] == '>')
				redir->type = 0;
			else if (cmd[0][i] == '<' && cmd[0][i + 1] == '<')
				redir->type = 3;
			else
				redir->type = 2;
			redir->kw = get_kw(cmd[0], cmd[0][i]);
			delete_redirection(cmd, cmd[0][i]);
			redir->next = get_redirection(cmd, i);
			return (redir);
		}
		else
			i++;
	}
	return (NULL);
}

int		write_redirection(int input, int fd)
{
	char	c;
	
	while (read(input, &c, 1))
		write(fd, &c, 1);
	close(fd);
	return (-1);
}