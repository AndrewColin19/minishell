/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/01/08 01:23:15 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	g_env = {0, NULL};

void	select_cmd(char *cmd, int in, int out)
{
	if (check_cmd(cmd, ECHO, 1))
		cmd_echo(out, cmd);
	else if (check_cmd(cmd, PWD, 0))
		cmd_pwd(out, &g_env);
	else if (check_cmd(cmd, ENV, 0))
		cmd_env(out, g_env);
	else if (check_cmd(cmd, CD, 0))
		cmd_cd(&g_env, cmd);
	else
		cmd_exec(cmd, in, out);
}

int		get_redirect(char **cmds, int i, int fct (char **))
{
	int		redirect;
	int		tmp;

	redirect = fct(&cmds[i]);
	tmp = fct(&cmds[i]);
	while (tmp)
	{
		redirect = tmp;
		tmp = fct(&cmds[i]);
	}
	return (redirect);
}

void	exec(char **cmds, int i, int in)
{
	int 	pipes[2];
	int		redirect_out;
	int		redirect_in;

	pipe(pipes);
	redirect_out = get_redirect(cmds, i, check_redirection_o);
	redirect_in = get_redirect(cmds, i, check_redirection_i);
	if (redirect_in)
		in = redirect_in;
	if (cmds[i + 1] || redirect_out)
	{
		if (cmds[i][0])
		{
			select_cmd(cmds[i], in, pipes[1]);
			if (redirect_in)
				redirect_in = 0;
		}
		close(pipes[1]);
		if (redirect_out)
		{
			if (redirect_in)
				write_redirection(in, redirect_out);
			else
				write_redirection(pipes[0], redirect_out);
		}
		if (cmds[i + 1])
			exec(cmds, i + 1, pipes[0]);
	}
	else
		select_cmd(cmds[i], in, 1);
}

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

int	main(int argc, char *argv[], char **ev)
{
	char	**cmds;
	char	*line;

	(void) argc;
	(void) argv;
	init(ev, &g_env);
	signal(SIGINT, interrupt_signal);
	signal(11, quit_signal);
	while (1)
	{
		line = readline(SHELL_TEXT);
		if (line[0])
		{
			cmds = parse(line);
			exec(cmds, 0, 0);
		}
	}
}
