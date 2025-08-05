/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:36:38 by dximenes          #+#    #+#             */
/*   Updated: 2025/08/04 11:01:42 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FH_PIPEX
# define FH_PIPEX

#include "ft_printf/include/ft_printf.h"
#include "ft_printf/include/libft/include/libft.h"
#include "get_next_line/include/get_next_line.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

typedef struct s_commands
{
	int		amount;
	char	**cmds;
}	t_commands;

typedef struct s_path
{
	char	*in;
	char	*out;
}	t_path;

typedef struct s_head
{
	t_path		file;
	t_commands	commands;
}	t_head;

// parse.c
void	parse(t_head *head, int ac, char *av[]);

// files.c
void	get_files(t_head *head, int ac, char *av[]);

// commands.c
int		get_amount(int ac, char *av[]);
char	**get_commands(t_head *head, int ac, char *av[]);

#endif