/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:33:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/15 17:37:02 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	execute_command(int in, int out, t_cmd command, char **envp)
{
	const pid_t	pid = fork();

	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_fds();
		execve(command.path, command.args, envp);
		return (pid);
	}
	return (pid);
}

static void	running_commands(t_head *head, int fd, t_fd filefd, char *envp[])
{
	int	pipefd[2];
	int	i;

	i = 0;
	while (i < head->cmds_size - 1)
	{
		pipe(pipefd);
		if (!execute_command(fd, pipefd[OUT], head->cmds[i], envp))
			end(head, errno, head->cmds[i].args[0]);
		close(pipefd[OUT]);
		if (fd != filefd.in)
			close(fd);
		fd = pipefd[IN];
		i++;
	}
	execute_command(fd, filefd.out, head->cmds[i], envp);
	if (fd != filefd.in)
		close(fd);
	close_fds();
}

void	commands(t_head *head, char *envp[])
{
	const t_fd	filefd = get_fdfile(head);
	int			to_wait;
	int			fd;

	fd = get_and_handle_heredoc(head, filefd.in);
	running_commands(head, fd, filefd, envp);
	to_wait = 1;
	while (to_wait > 0)
		to_wait = wait(NULL);
}
