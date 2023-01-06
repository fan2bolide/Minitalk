# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/01/06 06:05:46 by bajeanno         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = .main
NAMEBONUS = .bonus

CLIENT = client
SERVER = server

BONUS_CLIENT = client_bonus
BONUS_SERVER = server_bonus

FLAGS = -Werror -Wall -Wextra -I libft/head -I ./head

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SERVER_SRC = minitalk_server.c
CLIENT_SRC = minitalk_client.c

BONUS_SERVER_SRC = minitalk_server_bonus.c
BONUS_CLIENT_SRC = minitalk_client_bonus.c

SERVER_OBJ = $(addprefix obj/,$(SERVER_SRC:.c=.o))
CLIENT_OBJ = $(addprefix obj/,$(CLIENT_SRC:.c=.o))

BONUS_SERVER_OBJ = $(addprefix obj/,$(BONUS_SERVER_SRC:.c=.o))
BONUS_CLIENT_OBJ = $(addprefix obj/,$(BONUS_CLIENT_SRC:.c=.o))

DEPENDS	:=	$(addprefix obj/,$(SERVER_SRC:.c=.d)) $(addprefix obj/,$(CLIENT_SRC:.c=.d))
BONUS_DEPENDS := $(addprefix obj/,$(BONUS_SERVER_SRC:.c=.d)) $(addprefix obj/,$(BONUS_CLIENT_SRC:.c=.d))

all : create_obj_dir
	$(MAKE) $(NAME)
	
$(NAME) :  $(CLIENT) $(SERVER)
	@$(RM) $(BONUS_CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT_OBJ) $(BONUS_SERVER_OBJ) $(BONUS_DEPENDS)
	@touch $(NAME)
	@$(RM) $(NAMEBONUS)

$(CLIENT) : $(LIBFT) $(CLIENT_OBJ)
	$(CC) $(CLIENT_OBJ) $(LIBFT) $(FLAGS) -o $(CLIENT)

$(SERVER) : $(LIBFT) $(SERVER_OBJ)
	$(CC) $(SERVER_OBJ) $(LIBFT) $(FLAGS) -o $(SERVER)

bonus : create_obj_dir
	$(MAKE) $(NAMEBONUS)

$(NAMEBONUS) : $(LIBFT) $(BONUS_CLIENT) $(BONUS_SERVER)
	@$(RM) $(CLIENT) $(SERVER) $(SERVER_OBJ) $(CLIENT_OBJ) $(DEPENDS)
	@touch $(NAMEBONUS)
	@$(RM) $(NAME)

$(BONUS_CLIENT) : $(BONUS_CLIENT_OBJ)
	$(CC) $(BONUS_CLIENT_OBJ) $(LIBFT) $(FLAGS) -o $(BONUS_CLIENT)

$(BONUS_SERVER) : $(BONUS_SERVER_OBJ)
	$(CC) $(BONUS_SERVER_OBJ) $(LIBFT) $(FLAGS) -o $(BONUS_SERVER)

create_obj_dir : obj
	@mkdir -p obj

obj/%.o : src/%.c Makefile
	$(CC) $(FLAGS) -c $< -MD -o $@

$(LIBFT) : libft
	$(MAKE) -C libft

libft :
	git clone git@github.com:fan2bolide/libft.git
	rm -rf libft/.git

run : all
	./a.out

clean :
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(BONUS_SERVER_OBJ) $(BONUS_CLIENT_OBJ) $(DEPENDS) $(BONUS_DEPENDS) $(NAME) $(NAMEBONUS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	
fclean : clean
	$(RM) $(SERVER) $(CLIENT) $(BONUS_SERVER) $(BONUS_CLIENT)
	$(RM) $(NAME) $(NAMEBONUS)
	$(MAKE) fclean -C libft

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all run re clean fclean bonus rm_lib create_obj_dir

-include $(DEPENDS)