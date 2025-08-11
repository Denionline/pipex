/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:33:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/11 14:35:41 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_both(int fdin, int fdout)
{
	close(fdin);
	close(fdout);
}

static void	readinputs(int out, char *limiter)
{
	const char	*prefix = "\n\0";
	const char	*limiter_complete = ft_strjoin(limiter, prefix);
	const int	limiter_size = ft_strlen(limiter_complete);
	char		*str;

	while (TRUE)
	{
		ft_printf("heredoc> ");
		str = get_next_line(STDIN_FILENO);
		if (!str || !ft_strncmp(str, limiter_complete, limiter_size))
			break ;
		write(out, str, ft_strlen(str));
		free(str);
	}
	free((char *)limiter_complete);
	free(str);
}

static int	get_and_handle_heredoc(t_head *head)
{
	int	here_docfd[2];

	pipe(here_docfd);
	readinputs(here_docfd[OUT], head->limiter);
	close(here_docfd[OUT]);
	return (here_docfd[IN]);
}

static void	exec_cmd(int in, int out, t_cmd command, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_both(in, out);
		execve(command.path, command.args, envp);
	}
}

void	commands(t_head *head, char *envp[])
{
	t_fd	filefd = get_fdfile(head);
	int		pipefd[2];
	int		in_fd;
	int		i;

	in_fd = filefd.in;
	if (head->is_heredoc)
		in_fd = get_and_handle_heredoc(head);
	i = 0;
	while (head->cmds[i + 1].path)
	{
		pipe(pipefd);
		exec_cmd(in_fd, pipefd[OUT], head->cmds[i], envp);
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
	while (wait(NULL) > 0);
}
