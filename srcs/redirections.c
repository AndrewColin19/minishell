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

int		ft_create_file(char *cmd, int ap)
{
	char	*file;
	int		i;
	int		j;

	i = inc_i(cmd, '>');
	while (cmd[i] == '>' || cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[j] != ' ' && cmd[j] != '\0')
		j++;
	file = malloc(j - i);
	j = 0;
	while (cmd[i] != ' ' && cmd[i] != '\0')
		file[j++] = cmd[i++];
	open(file, O_CREAT, S_IRWXU);
	if (ap)
		return (open(file, O_APPEND | O_RDWR));
	else
		return (open(file, O_TRUNC | O_RDWR));
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

int		check_redirection_o(char **cmd)
{
	int	file;

    if (ft_str_contain(">>", cmd[0]))
    {
        file = ft_create_file(cmd[0], 1);
		delete_redirection(cmd, '>');
		write(1, "1", 1);
		return (file);
    }	
    else if (ft_str_contain(">", cmd[0]))
    {
        file = ft_create_file(cmd[0], 0);
		delete_redirection(cmd, '>');
		return (file);
    }
	return (0);
}

int		check_redirection_i(char **cmd)
{
	int	file;

    if (ft_str_contain("<<", cmd[0]))
    {
		file = heredoc(cmd[0]);
		delete_redirection(cmd, '<');
		return (file);
    }	
    else if (ft_str_contain("<", cmd[0]))
    {
		file = read_file(cmd[0]);
		delete_redirection(cmd, '<');
		return (file);
    }
	return (0);
}

int		write_redirection(int input, int fd)
{
	char	c;
	
	while (read(input, &c, 1))
		write(fd, &c, 1);
	close(fd);
	return (-1);
}