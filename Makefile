# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/01/04 21:45:05 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CLIENT = client

SERVER = server

FLAGS = -Werror -Wall -Wextra -I libft/head -I ./head

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SERVER_SRC = minitalk_server.c
CLIENT_SRC = minitalk_client.c

BONUS_SERVER_SRC = minitalk_server_bonus.c
BONUS_CLIENT_SRC = minitalk_client_bonus.c

SERVER_OBJ = $(addprefix obj/,$(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix obj/,$(CLIENT_SRC:.c=.o))

DEPENDS	:=	$(addprefix obj/,$(SERVER_SRC:.c=.d)) $(addprefix obj/,${CLIENT_SRC:.c=.d})

BONUS_OBJ = $(addprefix obj/,$(BONUS_SRC:.c=.o))

all :
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

.main :
	touch .main
	$(RM) .bonus

$(CLIENT) : create_obj_folder $(CLIENT_OBJ) lib .main
	$(CC) $(CLIENT_OBJ) $(LIBFT) $(FLAGS) -o $(CLIENT)

$(SERVER) : create_obj_folder $(SERVER_OBJ) lib .main
	$(CC) $(SERVER_OBJ) $(LIBFT) $(FLAGS) -o $(SERVER)


bonus :  lib .bonus

.bonus : $(OBJ) $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LIBFT) $(FLAGS) -o $(NAME)
	touch .bonus
	$(RM) .mandatory

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	$(CC) $(FLAGS) -c $< -MD -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

lib : $(LIBFT)

$(LIBFT) : libft
	$(MAKE) -C libft

libft :
	git clone git@github.com:fan2bolide/libft.git
	rm -rf libft/.git

run : all
	./a.out

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	
fclean : clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all lib run re clean fclean bonus rm_lib

-include $(DEPENDS)