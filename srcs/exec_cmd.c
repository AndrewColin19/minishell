
#include "../includes/minishell.h"

void 	cmd_exec(char *cmd, char **env)
{
	char 	**splited;
	char 	*path;

	splited = ft_split(cmd, ' ');
	path = ft_strjoin(CMD_PATH, splited[0]);
	if (open(path, O_RDONLY) == -1)
	{
		put_error(": command not found", cmd);
		return ;
	}
	if (execve(path, splited, env) == -1)
		printf("Error\n");
}