# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/21 18:47:09 by nuferron          #+#    #+#              #
#    Updated: 2023/10/14 17:05:01 by nuferron         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
RESET = \033[0m

SRCS = philo.c check_errors.c time.c initialize.c actions.c

SRCDIR = src/
OBJDIR = obj/
HEADER = philo.h
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread -g
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
NAME = philo
COLUMNS = $(shell tput cols)

all: ${NAME}

${NAME}: ${OBJS}
	cc ${CFLAGS} ${OBJS} ${LIB} -o $@
	printf "${WHITE}PHILOSOPHERS: ${GREEN}Binary compiled!${RESET}\n"

${OBJDIR}%.o: ${SRCDIR}%.c ${HEADER}
	@printf "${WHITE}PHILOSOPHERS: ${CYAN}Compiling files: ${WHITE}$(notdir $<)...${RESET}\r"
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} -c $< -o $@
	@printf "\r%-${COLUMNS}s\r"

leaks: ${NAME}
	leaks -atExit -- ./${NAME} ${ARGS}

norm:
	printf "${WHITE}PHILOSOPHERS\n${RESET}"
	norminette $(addprefix ${SRCDIR},$(SRCS)) ${HEADER} | grep -v "OK" \
	| awk '{if($$2 == "Error!") print "${RED}"$$1" "$$2; \
	else print "${RESET}"$$0}'

clean:
	if [ -d ${OBJDIR} ] ; then \
		rm -rf ${OBJDIR} ; \
		printf "${WHITE}PHILOSOPHERS: ${RED}Objects have been deleted${RESET}\n"; \
	fi

fclean: 	clean
	if [ -e ${NAME} ] ; then \
		rm -f ${NAME} .do_bonus ; \
		printf "${WHITE}PHILOSOPHERS: ${RED}All existing binaries have been deleted${RESET}\n" ; \
	else printf "${WHITE}PHILOSOPHERS: ${PURPLE}Already cleaned${RESET}\n" ; \
	fi

re:	fclean all

.SILENT: ${NAME} all clean fclean norm do_bonus
.PHONY: all make_libs fclean clean norm leaks re
