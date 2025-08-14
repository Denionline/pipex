/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:33:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/14 17:57:09 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_both(int fdin, int fdout)
{
	close(fdin);
	close(fdout);
}

static int	exec_cmd(int in, int out, t_cmd command, char **envp)
{
	const pid_t	pid = fork();

	if (pid == 0)
	{
		// ft_printf("Execucao do comando %s no STDIN=%d & STDOUT=%d\n", command.args[0], in, out);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_both(in, out);
		execve(command.path, command.args, envp);
		return (1);
	}
	return (0);
}

void	commands(t_head *head, char *envp[])
{
	const t_fd	filefd = get_fdfile(head);
	int			pipefd[2];
	int			in_fd;
	int			i;

	in_fd = get_and_handle_heredoc(head, filefd.in);
	i = 0;
	while (i < head->cmds_size - 1)
	{
		pipe(pipefd);
		if (exec_cmd(in_fd, pipefd[OUT], head->cmds[i], envp))
		{
			ft_printf("Errado\n");
			end(head, 2, head->cmds[i].path);
		}
		close(pipefd[OUT]);
		if (in_fd != filefd.in)
			close(in_fd);
		in_fd = pipefd[IN];
		i++;
	}
	exec_cmd(in_fd, filefd.out, head->cmds[i], envp);
	if (in_fd != filefd.in)
		close(in_fd);
	close_both(filefd.in, filefd.out);
	while (i > 0)
		i = wait(NULL);
}
