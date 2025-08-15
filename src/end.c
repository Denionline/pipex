/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:18:20 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/15 17:36:39 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clear_cmd(t_cmd *cmd)
{
	if (cmd->args)
		clear_args(cmd->args);
	if (cmd->path)
		free(cmd->path);
}

static void	show_error_msg(int error_code, char *description)
{
	if (error_code == 1)
		ft_printf("malloc error: %s\n", description);
	else if (error_code == 2)
		ft_printf("zsh: command not found: %s\n", description);
	else if (error_code == 3)
		ft_printf("enviroment variable not found: %s\n", description);
	else if (error_code == 4)
		ft_printf("pipex: number of arguments invalid\n");
	else if (error_code == 5)
		ft_printf("zsh: permission denied: %s\n", description);
	else
		ft_printf("zsh: %s\n", strerror(error_code));
}

void	end(t_head *head, int status, char *description)
{
	int	i;

	if (status != 0)
		show_error_msg(status, description);
	if (head)
	{
		if (head->paths)
			clear_args(head->paths);
		i = 0;
		while (head->cmds && i < head->cmds_size)
			clear_cmd(&head->cmds[i++]);
		if (head->cmds)
			free(head->cmds);
		if (head->file.in)
			free(head->file.in);
		if (head->file.out)
			free(head->file.out);
		free(head);
	}
	exit(status);
}
