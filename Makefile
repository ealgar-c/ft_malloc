# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 20:11:11 by ealgar-c          #+#    #+#              #
#    Updated: 2025/07/05 15:56:03 by ealgar-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC_FLAGS		=	-Wall -Wextra -Werror -fPIC
RM				=	rm -rf

DIR_HEADERS		=	./include/
DIR_SRCS		=	./srcs/
DIR_TESTS		=	./tests/
LIBFT_PATH		=	./include/libft
LIBFT_LIB		=	$(LIBFT_PATH)/libft.a
NAME			=	libft_malloc.so
HOSTTYPE		=	$(shell uname)
DYNAMIC_LIB		=	libft_malloc_$(HOSTTYPE).so
LOCALLIB_PATH	=	$$HOME/.locallibs/libft_malloc

all: $(DYNAMIC_LIB) setup

$(DYNAMIC_LIB): libft $(wildcard $(DIR_SRCS)*.c)
	@$(CC) $(CC_FLAGS) -shared $(wildcard $(DIR_SRCS)*.c) -Wl,--whole-archive $(LIBFT_LIB) -Wl,--no-whole-archive -o $(DYNAMIC_LIB)
	@echo "Dynamic Library '$(DYNAMIC_LIB)' created. ✅"

setup:
	@mkdir -p $(LOCALLIB_PATH)/libft
	@ln -sf $(abspath $(DYNAMIC_LIB)) $(LOCALLIB_PATH)/$(NAME)
	@cp $(DIR_HEADERS)/ft_malloc.h $(LOCALLIB_PATH)
	@cp $(LIBFT_PATH)/libft.h $(LOCALLIB_PATH)/libft

	@echo "Setup done: library and headers copied to $(LOCALLIB_PATH)"
	@echo "Remember to add this to your shell environment:"
	@echo "  export LD_LIBRARY_PATH=$(LOCALLIB_PATH):\$$LD_LIBRARY_PATH"
	@echo "  export LIBRARY_PATH=$HOME/.locallibs/libft_malloc:$LIBRARY_PATH"
	@echo "  export export C_INCLUDE_PATH=$HOME/.locallibs:$C_INCLUDE_PATH"

libft:
	@ make -s -C $(LIBFT_PATH)

tests: $(wildcard $(DIR_TESTS)*.c)
	@$(CC) $(CC_FLAGS) $(wildcard $(DIR_TESTS)*.c) -o run_tests -L. -lft_malloc -Wl,-rpath=.
	@echo "Tests compiled. Running tests... 🚀"
	@./run_tests

clean:
	@$(RM) run_tests
	@echo "'run_tests' has been deleted. 🗑️"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(DYNAMIC_LIB)
	@echo "'$(NAME)' has been deleted. 🗑️"
	@echo "'$(DYNAMIC_LIB)' has been deleted. 🗑️"

re: fclean all

re-tests: re tests

.PHONY:			all setup libft clean fclean re tests re-tests