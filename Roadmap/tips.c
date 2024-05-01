void	execute_command_internal_or_external(char *args[], t_status *status)
{
	if (is_builtin(args[0]))
		execute_builtin(args[0], args, status);
	else
		execute_external_command(args[0], args, g_environment, status);
}

int	is_builtin(const char *command)
{
	char	*command_copy;
	char	*token;

	command_copy = ft_strdup(command);
	token = ft_strtok(command_copy, " \t\n");
	if (ft_strcmp(token, "echo") == 0
		|| ft_strcmp(token, "cd") == 0
		|| ft_strcmp(token, "pwd") == 0
		|| ft_strcmp(token, "export") == 0
		|| ft_strcmp(token, "unset") == 0
		|| ft_strcmp(token, "env") == 0
		|| ft_strcmp(token, "exit") == 0)
	{
		free(command_copy);
		return (1);
	}
	free(command_copy);
	return (0);
}