/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:25 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/04 18:37:12 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	dosomething(t_head *head)
// {
// 	(void)head;
// 	char	buffer[100];
// 	int		pipefd[2];
// 	int		pid;

// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(pipefd[0]);
// 		write(pipefd[1], "World", 6);
// 		close(pipefd[1]);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		read(pipefd[0], buffer, sizeof(buffer));
// 		close(pipefd[0]);
// 	}
// }

int	main(int argc, char *argv[])
{
	t_head *head;

	if (argc < 2)
		return (1);
	head = ft_calloc(1, sizeof(t_head));
	if (!head)
		return (1);
	parse(head, argc - 1, argv + 1);
	// printf("Commands: %d | Infile: %s | Outfile: %s\n", head->commands.amount, head->file.in, head->file.out);
	// for (int i = 0; i < head->commands.amount; i++)
	// 	printf("Command: %s\n", head->commands.cmds[i]);
	// dosomething(head);
}

// ./pipex infile "grep M" "wc -l" outfile