/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:05:31 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/15 17:08:28 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_both(int fdin, int fdout)
{
	close(fdin);
	close(fdout);
}

void	clear_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}
