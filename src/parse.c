/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:52:13 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/19 10:28:39 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_file(t_head *head, char *name, int pos, int len)
{
	if (!head->is_heredoc && pos == 0)
	{
		if (!access(name, R_OK))
			head->file.in = ft_strdup(name);
		else
			end(head, errno, name);
	}
	else if (pos == len - 1)
	{
		if (!access(name, F_OK) && access(name, W_OK))
			end(head, errno, name);
		head->file.out = ft_strdup(name);
		if (head->is_heredoc)
			head->file.outflag = O_WRONLY | O_CREAT | O_APPEND;
		else
			head->file.outflag = O_WRONLY | O_CREAT | O_TRUNC;
	}
}

static t_cmd	*realloc_newcmds(t_head *head, t_cmd *old)
{
	t_cmd	*new_commands;
	int		i;

	new_commands = ft_calloc(head->cmds_size + 1, sizeof(t_cmd));
	if (!new_commands)
		return (NULL);
	i = 0;
	while (old && i < head->cmds_size)
	{
		new_commands[i] = old[i];
		i++;
	}
	if (old)
		free(old);
	return (new_commands);
}

static void	get_handle_cmds(t_head *head, int ac, char *av[], char **paths)
{
	const char	*here_doc = "here_doc";
	const int	lhere_doc = ft_strlen(here_doc);
	int			i;

	i = 0;
	while (i < ac)
	{
		if (i == 0 && !ft_strncmp(av[i], here_doc, lhere_doc) && MAX_ARGS > 4)
		{
			head->is_heredoc = TRUE;
			head->limiter = av[++i];
		}
		else if (i == 0 || !access(av[i], F_OK) || i == ac - 1)
			set_file(head, av[i], i, ac);
		else
		{
			head->cmds = realloc_newcmds(head, head->cmds);
			if (!head->cmds)
				end(head, ENOMEM, "head->cmds");
			head->cmds[head->cmds_size++] = get_cmd(head, av[i], paths);
		}
		i++;
	}
}

void	parse(t_head **head, int ac, char *av[], char *ev[])
{
	if (ac < MIN_ARGS || ac > MAX_ARGS)
		end(NULL, 4, NULL);
	(*head) = ft_calloc(1, sizeof(t_head));
	if (!(*head))
		end(*head, ENOMEM, "head");
	(*head)->paths = get_paths(ev);
	if (!(*head)->paths)
		end(*head, 3, "head->paths");
	get_handle_cmds(*head, ac, av, (*head)->paths);
	if (!(*head)->cmds)
		end(*head, ENOMEM, "head->cmds");
}
