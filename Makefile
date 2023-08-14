# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmagalha <pmagalha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 10:35:12 by pmagalha          #+#    #+#              #
#    Updated: 2023/06/05 13:38:47 by pmagalha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_S = server.c \

SRC_C = client.c \

SRC_SB = server_bonus.c \

SRC_CB = client_bonus.c \

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)
OBJ_SB = $(SRC_SB:.c=.o)
OBJ_CB = $(SRC_CB:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
NAME = minitalk


LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ_S) $(OBJ_C)
	$(MAKE) -C ./libft
	@$(CC) $(OBJ_S) $(LIBFT) -o server
	@$(CC) $(OBJ_C) $(LIBFT) -o client

bonus: $(OBJ_SB) $(OBJ_CB)
	$(MAKE) -C ./libft
	@$(CC) $(OBJ_SB) $(LIBFT) -o server_bonus
	@$(CC) $(OBJ_CB) $(LIBFT) -o client_bonus

clean:
		$(MAKE) clean -C ./libft
		@$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_SB) $(OBJ_CB)
fclean: clean
		@$(RM) $(LIBFT) $(NAME) server client server_bonus client_bonus
re: fclean $(NAME)
