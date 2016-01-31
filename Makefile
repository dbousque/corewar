# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/01 20:43:29 by hbeaujou          #+#    #+#              #
#    Updated: 2016/01/31 19:13:01 by hbeaujou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM	=	./asm/
COREWAR	=	./corewar/
LIB	=	./libdodo/

MAKE	=	make -C

all:
		$(MAKE)	$(LIB)
		$(MAKE) $(ASM)
		$(MAKE) $(COREWAR)

clean:
		$(MAKE)	$(LIB) clean
		$(MAKE) $(ASM) clean
		$(MAKE) $(COREWAR) clean

fclean:
		$(MAKE)	$(LIB) fclean
		$(MAKE) $(ASM) fclean
		$(MAKE) $(COREWAR) fclean

re:		fclean all

.PHONY:		re all fclean clean
