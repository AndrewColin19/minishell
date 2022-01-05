/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2022/01/05 13:28:04 by acolin           ###   ########.fr       */
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

	void	exec_rec(char **cmds, int i, int in)
	{
		int 	pipes[2];
		int		redirect_out;

		pipe(pipes);
		redirect_out = check_redirection(&cmds[i]);
		if (cmds[i + 1])
		{
			select_cmd(cmds[i], in, pipes[1]);
			close(pipes[1]);
			if (redirect_out)
				write_redirection(pipes[0], redirect_out);
			exec_rec(cmds, i + 1, pipes[0]);
		}
		else
		{
			if (redirect_out)
			{
				select_cmd(cmds[i], in, pipes[1]);
				close(pipes[1]);
				write_redirection(pipes[0], redirect_out);
			}
			else
				select_cmd(cmds[i], in, 1);
		}
	}

void	exec(char **cmds)
{
	exec_rec(cmds, 0, 0);
	/*int		i;
	int 	pipes[2];
	int		fd;
	int		redirect;

	i = -1;
	fd = 0;
	while (cmds[++i] && cmds[i + 1])
	{
		redirect = check_redirection(&cmds[i]);
		if (i != 0)
			fd = pipes[0];
		pipe(pipes);
		select_cmd(cmds[i], fd, pipes[1]);
		close(pipes[1]);
		if (redirect != NULL)
			write_redirection(pipes[0], redirect);
	}
	redirect = check_redirection(&cmds[i]);
	if (redirect)
	{
		fd = pipes[0];
		pipe(pipes);
		select_cmd(cmds[i], fd, pipes[1]);
		close(pipes[1]);
		write_redirection(pipes[0], redirect);
	}
	else
		select_cmd(cmds[i], pipes[0], 1);*/
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
			exec(cmds);
		}
	}
}
