# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 17:43:09 by marvin            #+#    #+#              #
#    Updated: 2025/05/09 22:02:59 by tcassu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= philo.c init.c manager.c threads.c forks.c utils.c

SRCS 		= ${SRC}

OBJS		= ${SRCS:.c=.o}

INCLUDES	= ./includes


NAME		= philo

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

all:		${NAME}

.c.o:
			${GCC} ${CFLAGS} -c -I ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${GCC} ${CFLAGS} -o ${NAME} ${OBJS} 

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all
			
.PHONY:		all clean fclean re
