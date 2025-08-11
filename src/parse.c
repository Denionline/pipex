/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:52:13 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/11 14:29:26 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_file(t_head *head, char *name, int pos)
{
	if (!head->is_heredoc && pos == 0 && !access(name, R_OK))
		head->file.in = ft_strdup(name);
	else
	{
		head->file.out = ft_strdup(name);
		if (head->is_heredoc)
			head->file.outflag = O_WRONLY | O_CREAT | O_APPEND;
		else
			head->file.outflag = O_WRONLY | O_CREAT;
	}
}

static t_cmd	*get_handle_cmds(t_head *head, int ac, char *av[], char **paths)
{
	const char	*here_doc = "here_doc";
	t_cmd		*commands;
	int			j;
	int			i;

	head->cmds_size = get_cmds_amount(ac, av);
	commands = ft_calloc(head->cmds_size + 1, sizeof(t_cmd));
	if (!commands)
		return (NULL);
	j = 0;
	i = 0;
	while (i < ac)
	{
		if (i == 0 && !ft_strncmp(av[i], here_doc, ft_strlen(here_doc)))
			head->is_heredoc = TRUE;
		else if (head->is_heredoc && i == 1)
			head->limiter = av[i];
		else if (!access(av[i], F_OK) || (access(av[i], F_OK) && i == ac - 1))
			set_file(head, av[i], i);
		else
			commands[j++] = get_cmd(head, av[i], paths);
		i++;
	}
	return (commands);
}

void	parse(t_head **head, int ac, char *av[], char *ev[])
{
	char	**paths;
	int		i;

	if (ac < MIN_ARGS || ac > MAX_ARGS)
		end(NULL, 4, NULL);
	(*head) = ft_calloc(1, sizeof(t_head));
	if (!(*head))
		end(*head, 1, "head struct");
	paths = get_paths(ev);
	if (!paths)
		end(*head, 3, "PATH");
	(*head)->cmds = get_handle_cmds(*head, ac, av, paths);
	if (!(*head)->cmds)
		end(*head, 1, "head->cmds");
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
}
