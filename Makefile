# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 15:31:19 by cmarrued          #+#    #+#              #
#    Updated: 2025/05/20 17:53:08 by cmarrued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

HEADERN	= src/philo.h

SRCS = src/main.c src/utils.c src/init.c src/atol.c src/simulation.c

OBJS = ${SRCS:.c=.o}

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -rf
			
all:			${NAME} 

%.o: %.c 		${HEADERN} Makefile
			${CC} ${CFLAGS} -c $< -o $(<:.c=.o)

${NAME}:		${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			
							
clean:			
			${RM} ${OBJS}

fclean:			clean
			${RM} ${NAME}
			

re:		fclean all

.PHONY:			all clean fclean re
