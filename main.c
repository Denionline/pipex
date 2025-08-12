/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:25 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/12 12:17:02 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_head	*head;

	parse(&head, argc - 1, argv + 1, envp);
	commands(head, envp);
	end(head, 0, "SUCESS");
}
