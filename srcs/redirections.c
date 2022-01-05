/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:10:35 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/05 11:34:12 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_str_contain(char *substr, char *str)
{
	int 	i;
	int     j;

	i = 0;
	while (str[i])
	{
		if (str[i] == substr[0])
		{
			j = 0;
			while (substr[j] && str[i + j]
				&& substr[j] == str[i + j])
				j++;
			if (substr[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int		ft_create_file(char *cmd, int ap)
{
	char	*file;
	int		i;
	int		j;

	i = 0;
	while (cmd[i] != '>')
		i++;
	while (cmd[i] == '>' || cmd[i] == ' ')
		i++;
	j = i;
	while (cmd[j] != ' ')
		j++;
	file = malloc(j - i + 2);
	j = 0;
	while (cmd[i] != ' ')
		file[j++] = cmd[i++];
	open(file, O_CREAT, S_IRWXU);
	if (ap)
		return (open(file, O_APPEND | O_RDWR));
	else
		return (open(file, O_TRUNC | O_RDWR));
}

void	delete_redirection(char **cmd)
{
	int		i;
	int		j;
	int		nb_char;

	i = 0;
	while (cmd[0][i] != '>')
		i++;
	j = i;
	while (cmd[0][j] == '>' || cmd[0][j] == ' ')
		j++;
	while (cmd[0][j] != ' ')
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

int		check_redirection(char **cmd)
{
	int	file;

    if (ft_str_contain(">>", cmd[0]))
    {
        file = ft_create_file(cmd[0], 1);
		delete_redirection(cmd);
		return (file);
    }	
    else if (ft_str_contain("<<", cmd[0]))
    {
		//Heredoc (read input until << xxxx)
		return (0);
    }
    else if (ft_str_contain(">", cmd[0]))
    {
        file = ft_create_file(cmd[0], 0);
		delete_redirection(cmd);
		return (file);
    }
    else if (ft_str_contain("<", cmd[0]))
    {
        //ft_read_file();
        return (0);
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