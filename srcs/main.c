/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 15:58:14 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	g_env = {0, 0, NULL};

void	interrupt_signal(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit_signal(int signum)
{
	(void) signum;
	exit(0);
}

void	loop(t_line **lines)
{
	int	i;

	i = 0;
	if (lines[0]->cmds[0]->kw == NULL)
		return ;
	while (lines[i])
	{
		exec(lines[i]->cmds, 0, 0);
		i++;
	}
}

int	main(int argc, char *argv[], char **ev)
{
	char	*line;
	t_line	**lines;

	(void) argc;
	(void) argv;
	init(ev, &g_env);
	//signal(SIGINT, interrupt_signal);
	//signal(11, quit_signal);
	while (1)
	{
		line = readline(SHELL_TEXT);
		add_history(line);
		if (line[0])
		{
			expend(&line);
			lines = parse(line);
			loop(lines);
			free_lines(lines);
		}
	}
}
