# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbeaujou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/01 20:43:29 by hbeaujou          #+#    #+#              #
#    Updated: 2016/01/31 19:07:58 by hbeaujou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

all:
	make -C ./assembleur
	make -C ./vm

clean:
	make clean -C ./assembleur
	make clean -C ./vm

fclean: clean
	make fclean -C ./assembleur
	make fclean -C ./vm

re: fclean all

.PHONY: re fclean clean all
