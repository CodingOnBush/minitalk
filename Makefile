# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momrane <momrane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/07 15:20:43 by momrane           #+#    #+#              #
#    Updated: 2024/01/10 15:15:07 by momrane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =			cc
CFLAGS =		-Wall -Wextra -Werror

BINDIR = 		./bin
INCDIR = 		./inc
SRCDIR = 		./src

CLIENTDIR =		$(SRCDIR)/client
SERVERDIR =		$(SRCDIR)/server

SERVER =		server
CLIENT =		client
NAME = 			$(SERVER) $(CLIENT)

PRINTF =		./lib/ft_printf/libftprintf.a
LIBFT =			./lib/libft/libft.a
LIBS =			$(PRINTF) $(LIBFT)

CLIENTSRC = 	$(CLIENTDIR)/client.c $(CLIENTDIR)/parsing.c

SERVERSRC =		$(SERVERDIR)/server.c $(SERVERDIR)/manage_data.c \
				$(SERVERDIR)/manage_errors.c $(SERVERDIR)/manage_msg.c

CLIENTOBJ = 	$(CLIENTSRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)
SERVEROBJ = 	$(SERVERSRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: $(NAME)

$(NAME): $(LIBS) $(SERVEROBJ) $(CLIENTOBJ)
	@echo "SERVER compiling..."
	@$(CC) $(CFLAGS) -I$(INCDIR) $(SERVEROBJ) $(LIBS) -o $(SERVER)
	@echo "CLIENT compiling..."
	@$(CC) $(CFLAGS) -I$(INCDIR) $(CLIENTOBJ) $(LIBS) -o $(CLIENT)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(LIBS):
	@echo "LIBS compiling..."
	@make -sC ./lib/ft_printf all
	@make -sC ./lib/libft all

clean:
	@echo "Remove object files..."
	@rm -rf $(BINDIR)
	@make -sC ./lib/ft_printf clean
	@make -sC ./lib/libft clean

fclean: clean
	@echo "Remove SERVER and CLIENT files..."
	@rm -f $(SERVER) $(CLIENT)
	@make -sC ./lib/ft_printf fclean
	@make -sC ./lib/libft fclean

re: fclean all

.PHONY: all clean fclean re