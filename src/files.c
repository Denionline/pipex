/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:37:46 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/04 13:53:07 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_files(t_head *head, int ac, char *av[])
{
	int	fd;
	int	i;

	i = 0;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd >= 3)
		{
			close(fd);
			if (!head->file.in)
				head->file.in = ft_strdup(av[i]);
			else
				head->file.out = ft_strdup(av[i]);
		}
		i++;
	}
}
