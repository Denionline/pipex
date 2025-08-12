/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:38 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/12 12:17:47 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/include/ft_printf.h"
# include "ft_printf/include/libft/include/libft.h"
# include "get_next_line/include/get_next_line.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# ifndef MAX_ARGS
#  define MAX_ARGS 4
# endif

# ifndef MIN_ARGS
#  define MIN_ARGS 4
# endif

# define OUT 1
# define IN 0

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_file
{
	char	*in;
	char	*out;
	int		outflag;
}	t_file;

typedef struct s_head
{
	t_file	file;
	t_cmd	*cmds;
	int		cmds_size;
	int		is_heredoc;
	char	*limiter;
}	t_head;

// parse.c
void	parse(t_head **head, int ac, char *av[], char *ev[]);

// commands.c
void	commands(t_head *head, char *envp[]);

// end.c
void	end(t_head *head, int status, char *description);

t_fd	get_fdfile(t_head *head);
char	*get_valid_path(char **paths, char *command);
char	**get_paths(char *env[]);
int		get_cmds_amount(int ac, char *av[]);
t_cmd	get_cmd(t_head *head, char *command, char **paths);

#endif