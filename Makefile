# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/28 17:48:11 by dximenes          #+#    #+#              #
#    Updated: 2025/08/11 11:43:39 by dximenes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    Colors                                    #
# **************************************************************************** #

C_STD = \033[0;39m
C_GRAY = \033[0;90m
C_RED = \033[0;91m
C_GREEN = \033[0;92m
C_YELLOW = \033[0;93m
C_BLUE = \033[0;94m
C_MAGENTA = \033[0;95m
C_CYAN = \033[0;96m
C_WHITE = \033[0;97m

# **************************************************************************** #
#                                    Files                                     #
# **************************************************************************** #

NAME				= pipex
FTPRINTF			= $(FTPRINTF_PATH)libftprintf.a
LIBFT				= $(LIBFT_PATH)libft.a
GNL					= $(GNL_PATH)get_next_line.a

# **************************************************************************** #
#                                   Path's                                     #
# **************************************************************************** #

INC_PATH			= include/
SRC_PATH			= src/
BUILD_PATH			= .build/

FTPRINTF_PATH				= $(INC_PATH)/ft_printf/
LIBFT_PATH					= $(FTPRINTF_PATH)$(INC_PATH)/libft/
GNL_PATH					= $(INC_PATH)/get_next_line/

# **************************************************************************** #
#                                   Files                                      #
# **************************************************************************** #

MAIN				= main

FILES				+= parse
FILES				+= get
FILES				+= commands
FILES				+= end

SRC_FILES			+= $(MAIN)
SRC_FILES			+= $(addprefix $(SRC_PATH), $(FILES))

OBJ_FILES			+= $(MAIN)
OBJ_FILES			+= $(FILES)

SRCS				= $(addprefix ./, $(addsuffix .c, $(SRC_FILES)))
OBJS				= $(addprefix $(BUILD_PATH), $(addsuffix .o, $(OBJ_FILES)))

# **************************************************************************** #
#                                    Git                                       #
# **************************************************************************** #

FTPRINTF_URL		= https://github.com/Denionline/ft_printf.git
GNL_URL				= https://github.com/Denionline/get_next_line.git

# **************************************************************************** #
#                                  Compiler                                    #
# **************************************************************************** #

CC							= cc
LIBS						= $(FTPRINTF) $(LIBFT) $(GNL)
CFLAGS						= -Werror -Wextra -Wall
MAKE						= make --no-print-directory

# **************************************************************************** #
#                                  Commands                                    #
# **************************************************************************** #

all: start check_libraries $(NAME)
	@printf "$(C_MAGENTA)===========End [$(NAME)]===========$(C_STD)\n"

start:
	@printf "$(C_MAGENTA)===========Program [$(NAME)]===========$(C_STD)\n"

$(NAME): $(BUILD_PATH)
	@printf "\n$(C_YELLOW)Compile $(NAME) files:$(C_STD)\n"
	@TOTAL=$$(echo $(SRCS) | wc -w);\
	CUR=1;\
	for SRC in $(SRCS); do\
		OBJ=$(BUILD_PATH)$$(basename $$SRC .c).o;\
		$(CC) $(CFLAGS) -I$(INC_PATH) -c $$SRC -o $$OBJ;\
		PERC=$$(printf "%d" $$((100 * CUR / TOTAL)));\
		FILLED=$$(printf "%0.f" $$((20 * PERC / 100)));\
		EMPTY=$$((20 - FILLED));\
		BAR=$$(printf "$(C_GREEN)%*s$(C_STD)" $$FILLED "" | tr " " "#")$$(\
		printf "%*s" $$EMPTY "" | tr " " ".");\
		printf "\rCompiling [%s] %3d%%" $$BAR $$PERC;\
		CUR=$$((CUR + 1)); \
	done;\
	printf "\n";
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJS) $(LIBS) -o $(NAME)

$(BUILD_PATH):
	@mkdir $(BUILD_PATH)

clean:
	@rm -rf $(BUILD_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

check_libraries: verify_ftprintf verify_gnl

# libft processes
verify_ftprintf:
	@if test ! -d "$(FTPRINTF_PATH)"; then $(MAKE) get_ftprintf; \
		else printf "ft_printf: $(C_GREEN)✅$(C_STD)\n"; fi
	@$(MAKE) -C $(FTPRINTF_PATH)

get_ftprintf:
	@echo "Cloning ft_printf"
	@git clone $(FTPRINTF_URL) $(FTPRINTF_PATH)
	@printf "$(C_GREEN)ft_printf$(C_STD) successfully downloaded\n"

# get_next_line processes
verify_gnl:
	@if test ! -d "$(GNL_PATH)"; then $(MAKE) get_gnl; \
		else printf "get_next_line: $(C_GREEN)✅$(C_STD)\n"; fi
	@$(MAKE) -C $(GNL_PATH)

get_gnl:
	@printf "Cloning get_next_line\n"
	@git clone $(GNL_URL) $(GNL_PATH)
	@printf "$(C_GREEN)get_next_line$(C_STD) successfully downloaded\n"