/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:18:20 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/11 11:26:05 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clear_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i] != NULL)
		free(cmd->args[i++]);
	if (cmd->args)
		free(cmd->args);
	if (cmd->path)
		free(cmd->path);
}

static void	show_error_msg(int error_code, char *description)
{
	if (error_code == 1)
		ft_printf("Malloc error on %s\n", description);
	if (error_code == 2)
		ft_printf("Command not found: %s\n", description);
}

void	end(t_head *head, int status, char *description)
{
	int	i;

	i = 0;
	while (head->cmds && i < head->cmds_size)
		clear_cmd(&head->cmds[i++]);
	if (head->cmds)
		free(head->cmds);
	if(head->file.in)
		free(head->file.in);
	if(head->file.out)
		free(head->file.out);
	free(head);
	if (status != 0)
		show_error_msg(status, description);
	exit(status);
}