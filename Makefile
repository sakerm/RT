# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:09:20 by lvasseur          #+#    #+#              #
#    Updated: 2017/05/03 13:31:18 by lomeress         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
SRC = src/main.c \
	  src/vector.c \
	  src/create_lights.c \
	  src/create_objects.c \
	  src/intersects.c \
	  src/normals.c \
	  src/texture.c \
	  src/color.c \
	  src/matrice.c
OBJ = $(SRC:.c=.o)
	FLAGS = #-Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	gcc -c $^ -o $@ -I ./Users/lomeress/.brew/opt/sdl2/include/SDL2 -lSDL2 -lm

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L /Users/lomeress/.brew/opt/sdl2/lib libft/libft.a -lm -lSDL2

c clean:
	rm -f $(OBJ)

f fclean: clean
	rm -f $(NAME)

r re: fclean all

g good: $(NAME) clean
