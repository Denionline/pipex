/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:52:13 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/06 16:53:49 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *get_valid_path(char **paths, char *command)
{
	char	*complete_path;
	char	*path_bar;
	int		j;

	j = 0;
	while (paths[j])
	{
		path_bar = ft_strjoin(paths[j], "/");
		complete_path = ft_strjoin(path_bar, command);
		if (!access(complete_path, F_OK))
			return (complete_path);
		free(path_bar);
		free(complete_path);
		j++;
	}
	return (NULL);
}

static char	**get_path(char *env[])
{
	const char	*prefix = "PATH=";
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], prefix, ft_strlen(prefix)))
			return (ft_split(ft_strlen(prefix) + env[i], ':'));
		i++;
	}
	return (NULL);
}

static int	get_amount(int ac, char *av[])
{
	int	amount;
	int	i;

	amount = 0;
	i = 0;
	while (i < ac)
	{
		if (access(av[i], F_OK))
			amount += 1;
		i++;
	}
	return (amount);
}

static t_cmd	get_cmd(char *command, char **paths)
{
	t_cmd	cmd;

	cmd.args = ft_split(command, ' ');
	cmd.path = get_valid_path(paths, cmd.args[0]);
	return (cmd);
}

static t_cmd	*get_commands(t_head *head, int ac, char *av[], char **paths)
{
	t_cmd	*commands;
	int		j;
	int		i;

	commands = ft_calloc(get_amount(ac, av) + 1, sizeof(t_cmd *));
	if (!commands)
		return (NULL);
	j = 0;
	i = 0;
	while (i < ac)
	{
		if (!access(av[i], F_OK | R_OK | W_OK))
		{
			if (!head->file.in)
				head->file.in = ft_strdup(av[i]);
			else
				head->file.out = ft_strdup(av[i]);
		}
		else
			commands[j++] = get_cmd(av[i], paths);
		i++;
	}
	commands[j].path = NULL;
	return (commands);
}

void	parse(t_head *head, int ac, char *av[], char *ev[])
{
	head->cmds = get_commands(head, ac, av, get_path(ev));
}
