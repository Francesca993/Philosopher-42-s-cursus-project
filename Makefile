# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francesca <francesca@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 14:23:25 by francesca         #+#    #+#              #
#    Updated: 2025/04/07 16:37:55 by francesca        ###   ########.fr        #
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