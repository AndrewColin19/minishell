/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/01/05 15:05:51 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	exec(char **cmds, int i, int in)
{
	int 	pipes[2];
	int		redirect_out;
	int		redirect_in;

	pipe(pipes);
	redirect_out = check_redirection_o(&cmds[i]);
	redirect_in = check_redirection_i(&cmds[i]);
	if (redirect_in)
		in = redirect_in;
	if (cmds[i + 1] || redirect_out)
	{
		select_cmd(cmds[i], in, pipes[1]);
		close(pipes[1]);
		if (redirect_out)
			write_redirection(pipes[0], redirect_out);
		if (cmds[i + 1] )
			exec(cmds, i + 1, pipes[0]);
	}
	else
		select_cmd(cmds[i], in, 1);
}

int	main(int argc, char *argv[], char **ev)
{
	char	**cmds;

	(void) argc;
	(void) argv;
	init(ev, &g_env);
	while (1)
	{
		cmds = parse(readline(SHELL_TEXT));
		if (cmds == NULL)
		{
			printf("Error\n");
			free_cmds(cmds);
		}
		else
		{
			expend_var(cmds);
			exec(cmds, 0, 0);
		}
	}
}
