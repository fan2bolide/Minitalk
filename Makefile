# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/01/05 07:07:14 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

BONUS_CLIENT = bonusclient
BONUS_SERVER = bonusserver

FLAGS = -Werror -Wall -Wextra -I libft/head -I ./head

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SERVER_SRC = minitalk_server.c
CLIENT_SRC = minitalk_client.c

SERVER_COMPIL_NAME = mt_server.c
CLIENT_COMPIL_NAME = mt_client.c

BONUS_SERVER_SRC = minitalk_server_bonus.c
BONUS_CLIENT_SRC = minitalk_client_bonus.c

SERVER_OBJ = $(addprefix obj/,$(SERVER_COMPIL_NAME:.c=.o))
CLIENT_OBJ = $(addprefix obj/,$(CLIENT_COMPIL_NAME:.c=.o))

DEPENDS	:=	$(addprefix obj/,$(SERVER_COMPIL_NAME:.c=.d)) $(addprefix obj/,${CLIENT_COMPIL_NAME:.c=.d})

all : .main cp_mandatory_files
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

cp_mandatory_files : src/$(SERVER_SRC) src/$(CLIENT_SRC)
	cp src/$(SERVER_SRC) src/$(SERVER_COMPIL_NAME)
	cp src/$(CLIENT_SRC) src/$(CLIENT_COMPIL_NAME)

.main :
	$(RM) $(CLIENT) $(SERVER) $(SERVER_OBJ) $(CLIENT_OBJ)
	touch .main
	$(RM) .bonus

$(SERVER) : $(SERVER_OBJ) $(LIBFT)
	$(CC) $(SERVER_OBJ) $(LIBFT) $(FLAGS) -o $(SERVER)
	$(RM) src/$(SERVER_COMPIL_NAME)
	
$(CLIENT) : $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CLIENT_OBJ) $(LIBFT) $(FLAGS) -o $(CLIENT)
	$(RM) src/$(CLIENT_COMPIL_NAME)

bonus : create_obj_dir .bonus
	cp src/$(BONUS_SERVER_SRC) src/$(SERVER_COMPIL_NAME)
	cp src/$(BONUS_CLIENT_SRC) src/$(CLIENT_COMPIL_NAME)
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

.bonus :
	$(RM) $(CLIENT) $(SERVER) $(BONUS_CLIENT_OBJ) $(BONUS_SERVER_OBJ)
	touch .bonus
	$(RM) .main

create_obj_dir : obj

obj :
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
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(BONUS_SERVER_OBJ) $(BONUS_CLIENT_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	
fclean : clean
	$(RM) $(SERVER_COMPIL_NAME) $(CLIENT_COMPIL_NAME)
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all lib run re clean fclean bonus rm_lib create_obj_dir

-include $(DEPENDS)