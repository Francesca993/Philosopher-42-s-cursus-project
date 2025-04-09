# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 14:23:25 by francesca         #+#    #+#              #
#    Updated: 2025/04/09 11:59:47 by fmontini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME	=	philo

# Source files (add your files from src/ here)
SRC	=	philosophers.c \
		ft_init.c \
		ft_atoi.c \
		ft_create_threads.c \
		ft_free_all.c \
		ft_routine.c \
		routine_utils.c \
		monitor_routine.c \
		ft_join.c \

# .c to .o compilation
OBJ	=	$(SRC:.c=.o)

# compilation flags
CFLAGS	=  -Wall -Werror -Wextra -pthread

# Rules
$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ) $(CFLAGS)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all 
	rm -rf $(NAME)
	
.PHONY : all bonus clean fclean re