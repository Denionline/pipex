/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bonus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:03:32 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/14 17:47:07 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	readinputs(int out, char *limiter)
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

int	get_and_handle_heredoc(t_head *head, int std_return)
{
	int	here_docfd[2];

	if (head->is_heredoc)
	{
		pipe(here_docfd);
		readinputs(here_docfd[OUT], head->limiter);
		close(here_docfd[OUT]);
		return (here_docfd[IN]);
	}
	return (std_return);
}
