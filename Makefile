# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/28 14:35:07 by tpierre           #+#    #+#              #
#    Updated: 2021/08/18 13:00:34 by tpierre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

##################################### DIRS #####################################

INC_DIR		=	./includes

SRC_DIR		=	./srcs

OBJ_DIR		=	./objs

##################################### SRCS #####################################

# **************************************************************************** #
# pilosophers :

PS_FILES	= check_death.c main.c parse.c thread.c utils_lib.c utils_philo.c

##################################### OBJS #####################################

PS_OBJS		=	$(PS_FILES:.c=.o)

PS_OBJ		=	$(addprefix $(OBJ_DIR)/, $(PS_OBJS))

##################################### INCS #####################################

PS_INC		=	$(addprefix $(INC_DIR)/, philo.h)

HEADERS		=	$(PS_INC)

INCS		=	$(addprefix -I,$(INC_DIR))

##################################### COMP #####################################

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror -pthread
# CFLAGS		=	-Wall -Wextra -Werror -pthread -g -fsanitize=thread

##################################### RULE #####################################

all:			$(NAME)

$(NAME):		$(PS_OBJ)
				@$(CC) $(CFLAGS) -o $(NAME) $(PS_OBJ) $(INCS)
				@$(IF_CMP)
				@echo $(BG)[$(BLB)PHILOSOPHERS $(BG)COMPILED$(BG)]$(X)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS)
				@$(CMP)
				@$(MKOBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)
				@$(CLR)
				@echo -n $@

clean:
				@/bin/rm -rf $(OBJ_DIR)
				@echo $(BG)[$(BLB)PHILOSOPHERS $(BG)CLEANED$(BG)]$(X)

fclean:			clean
				@/bin/rm -f $(NAME)

re:
				@$(MAKE) fclean
				@$(MAKE) all

##################################### UTIL #####################################

MKOBJ_DIR 		=	if [ ! -d $(OBJ_DIR) ]; then \
			/bin/mkdir -p $(OBJ_DIR); fi

CMP			=	if [ ! -e .cmp ]; then \
				echo $(BY)Compiling $(B)Project $(X)files...$(BY); \
				touch .cmp; fi

IF_CMP		=	if [ -e .cmp ]; then \
				$(CLR); \
				echo $(UP) $(CUT) $(UP); \
				/bin/rm -f .cmp; fi

################################### DISPLAY ####################################

BY			=	"\033[1;33m"
BR			=	"\033[1;31m"
BG			=	"\033[1;32m"
BLB			=	"\033[1;36m"
BP			=	"\033[1;35m"
Y			=	"\033[33m"
R			=	"\033[31m"
G			=	"\033[0;32m"
B			=	"\033[34m"
P			=	"\033[35m"
X			=	"\033[0m"
UP			=	"\033[A"
CUT			=	"\033[K"
CLR			=	printf "\r%40c\r" " "
CUT_UP		=	$(UP)$(CUT)$(UP)

#################################### OTHER #####################################

.PHONY:			all clean fclean re
