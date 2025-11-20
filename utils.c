#include "poulet.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, j) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**path;
	char	*string_path;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	path = ft_split(my_getenv("PATH", env), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		string_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(string_path, F_OK | X_OK) == 0)
		{
			ft_strclear(path);
			return (string_path);
		}
		free(string_path);
		i++;
	}
	ft_strclear(path);
	return (NULL);
}
