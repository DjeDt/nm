#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddinaut <ddinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 11:35:20 by ddinaut           #+#    #+#              #
#    Updated: 2018/10/22 12:29:40 by ddinaut          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Binaries output #
FT_NM		= ft_nm
FT_OTOOL		= ft_otool

# compilation #
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
ADDFLAGS	= #-O1 -g3 -fsanitize=address -fno-omit-frame-pointer -Wpadded

# Directories #
OBJ_PATH	= obj
SRC_PATH	= srcs
LIB_PATH	= libft
INC_PATH	= includes/

# Sub_dirs #
DIR_NM		= ft_nm
LIB_NM		= $(DIR_NM)/parse_macho
DIR_OTOOL	= ft_otool

# Colors #
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
PURPLE		= \033[1;35m
WHITE		= \033[1;37m
END_COL		= \033[0m
COUNT		= 1

# libraries #
LIBFT		= -L $(LIB_PATH)
LIBS		= $(LIBFT) -lft
INCLUDES	= -I./ -I $(LIB_PATH)/$(INC_PATH) -I $(INC_PATH)
LIBPRINTF	= -Ift_printf/includes/ -Lft_printf/ -lftprintf

# Sources #
SRCS_NM 	=								\
			$(DIR_NM)/main.c				\
			$(DIR_NM)/setup_struct.c		\
			$(DIR_NM)/handle_64_binary.c	\
			$(DIR_NM)/handle_32_binary.c	\
			$(DIR_NM)/check_offset.c		\
			$(DIR_NM)/utils.c				\
			$(LIB_NM)/parse_header.c		\
			$(LIB_NM)/parse_load_command.c	\
			$(LIB_NM)/parse_section.c		\
			$(LIB_NM)/parse_symbol_table.c	\
			$(LIB_NM)/parse_segment.c


OBJ_NM = $(SRC_NM:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC_NM = $(addprefix $(SRC_PATH)/,$(SRCS_NM))

SRCS_OTOOL	= \
			$(DIR_OTOOL)/main.c

OBJ_OTOOL = $(SRC_OTOOL:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC_OTOOL = $(addprefix $(SRC_PATH)/,$(SRCS_OTOOL))

# Percent Progress
COUNT_S       	= 1
COUNT_C       	= 1
NB_FILES_SER	= $(words $(SRCS_NM))
NB_FILES_CLI	= $(words $(SRCS_OTOOL))
PERCENT_SER    	= $(shell echo $$(( ($(COUNT_S) * 100) / $(NB_FILES_SER))))
PERCENT_CLI    	= $(shell echo $$(( ($(COUNT_C) * 100) / $(NB_FILES_CLI))))

# Exceptions #
.PHONY: all clean fclean re ft_printf test

# Compilation rules #
all: ft_printf $(FT_NM) $(FT_OTOOL)

ft_printf:
	@printf "\n[Compiling ft_printf] :\n"
	make -C ft_printf/

test:
	gcc test/test0.c -o t0.out

$(FT_NM): $(OBJ_NM)
	@make -sC $(LIB_PATH)
	@$(CC) -o $(FT_NM) $(FLAGS) $(ADDFLAGS) $(OBJ_NM) $(LIBS) $(LIBPRINTF)
	@printf "$(GREEN)\r\033[Kft_nm is ready to works\n$(END_COL)"

$(OBJ_NM): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(FLAGS) $(ADDFLAGS) $(INCLUDES) -c $<
	@printf "\r\033[K$(RED)[%-5.2f%%]  \e[1;38;5;148m[$@] -> [$<]$(END_COL)" $(PERCENT_SER)
	$(eval COUNT_S=$(shell echo $$(($(COUNT_S)+1))))

$(FT_OTOOL): $(OBJ_OTOOL)
	@make -sC $(LIB_PATH)
	@$(CC) -o $@ $(FLAGS) $(ADDFLAGS) $(OBJ_OTOOL) $(LIBS)
	@printf "$(GREEN)\r\033[Kft_otool is ready to works\n$(END_COL)"

$(OBJ_OTOOL): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(FLAGS) $(ADD_FLAGS) $(INCLUDES) -c $<
	@printf "\r\033[K$(RED)[%-5.2f%%]  \e[1;38;5;148m[$@] -> [$<]$(END_COL)" $(PERCENT_CLI)
	$(eval COUNT_C=$(shell echo $$(($(COUNT_C)+1))))

clean:
#	@make -sC $(LIB_PATH) clean
	@/bin/rm -f $(OBJ_NM)
	@/bin/rm -f $(OBJ_OTOOL)

fclean: clean
#	@make -sC $(LIB_PATH) fclean
	@/bin/rm -f $(FT_NM) $(FT_OTOOL)
	@/bin/rm -rf $(OBJ_PATH)

re: fclean all
