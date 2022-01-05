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

void	delete_redirection(char **cmd, char c)
{
	int		i;
	int		j;
	int		nb_char;

	i = 0;
	while (cmd[0][i] != c)
		i++;
	j = i;
	while (cmd[0][j] == c || cmd[0][j] == ' ')
		j++;
	while (cmd[0][j] != ' ')
		j++;
	while (cmd[0][j] == ' ')
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