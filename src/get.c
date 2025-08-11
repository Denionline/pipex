/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:16:31 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/11 11:26:05 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_fd get_fdfile(t_head *head)
{
	t_fd	fdfile;

	fdfile.in = STDIN_FILENO;
	if (head->file.in)
		fdfile.in = open(head->file.in, O_RDONLY);
	fdfile.out = open(head->file.out, head->file.outflag);
	return (fdfile);
}

char *get_valid_path(char **paths, char *command)
{
	char	*complete_path;
	char	*path_bar;
	int		j;

	j = 0;
	while (paths[j])
	{
		path_bar = ft_strjoin(paths[j], "/");
		complete_path = ft_strjoin(path_bar, command);
		free(path_bar);
		if (!access(complete_path, F_OK))
			return (complete_path);
		free(complete_path);
		j++;
	}
	return (NULL);
}

char	**get_paths(char *env[])
{
	const char	*prefix = "PATH=";
	const int	lprefix = ft_strlen(prefix);
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], prefix, lprefix))
			return (ft_split(env[i] + lprefix, ':'));
		i++;
	}
	return (NULL);
}

int	get_cmds_amount(int ac, char *av[])
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

t_cmd	get_cmd(t_head *head, char *command, char **paths)
{
	t_cmd	cmd;

	cmd.args = ft_split(command, ' ');
	cmd.path = get_valid_path(paths, cmd.args[0]);
	if (!cmd.path)
		end(head, 2, command);
	return (cmd);
}
