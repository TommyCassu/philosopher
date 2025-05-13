# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 17:43:09 by marvin            #+#    #+#              #
#    Updated: 2025/05/13 08:44:16 by tcassu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= philo.c init.c manager.c threads.c actions.c utils.c

SRCS 		= ${SRC}

OBJS		= ${SRCS:.c=.o}

INCLUDES	= ./includes


NAME		= philo

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

all: ${NAME}

.c.o:
	@${GCC} ${CFLAGS} -c -I ${INCLUDES} $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@${GCC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "\033[0;32mCompilation terminée ! ✓\033[0m"

clean:
	@${RM} ${OBJS}
	@echo "\033[0;32mSuppression des fichiers objets ! ✓\033[0m"

fclean: clean
	@${RM} ${NAME}
	@echo "\033[0;32mSuppression des fichiers objets et l'exécutable ! ✓\033[0m"

re: fclean all

.PHONY: all clean fclean re