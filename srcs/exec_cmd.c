
#include "../includes/minishell.h"

void 	cmd_exec(char *cmd, char **env)
{
	char 	**splited;
	char 	*path;
	pid_t	pid;
	int 	status;

	splited = ft_split(cmd, ' ');
	path = ft_strjoin(CMD_PATH, splited[0]);
	if (open(path, O_RDONLY) == -1)
	{
		put_error(": command not found", cmd);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, splited, env) == -1)
			printf("Error\n");
	}
	else
		waitpid(pid, &status, 0);
}