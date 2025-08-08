/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:25 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/08 11:55:28 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_head *head;
	
	if (argc < 2)
		return (1);
	head = ft_calloc(1, sizeof(t_head));
	if (!head)
		return (1);
	parse(head, argc - 1, argv + 1, envp);

	int	fd_infile = open(head->file.in, O_RDONLY);
	int	fd_outfile = open(head->file.out, O_WRONLY | O_CREAT, 0777);
	int	pipefd[2];

	pipe(pipefd);
	int	id = fork();

	dup2(fd_outfile, 1);
	if (id == 0)
	{
		dup2(fd_infile, 0);
		execve(head->cmds[0].path, head->cmds[0].args, NULL);
	}
}

// ./pipex infile "grep M" "wc -l" outfile