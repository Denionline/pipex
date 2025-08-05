/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:33:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/04 14:02:10 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_amount(int ac, char *av[])
{
	int	amount;
	int	fd;
	int	i;

	amount = 0;
	i = 0;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
			amount += 1;
		else
			close(fd);
		i++;
	}
	return (amount);
}

char	**get_commands(t_head *head, int ac, char *av[])
{
	char	**commands;
	int		fd;
	int		j;
	int		i;

	commands = ft_calloc(head->commands.amount + 1, sizeof(char *));
	if (!commands)
		return (NULL);
	j = 0;
	i = 0;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
			commands[j++] = ft_strdup(av[i]);
		else
			close(fd);
		i++;
	}
	commands[j] = NULL;
	return (commands);
}

// void	execute(t_head *head)
// {
// 	execve()
// }