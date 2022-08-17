# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 00:46:25 by bgoncalv          #+#    #+#              #
#    Updated: 2022/08/17 04:49:56 by brunodeoliv      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S		= srcs/
O		= objs/
I		= incs/ -I tests/

NAME	= ft_containers

SRCS	= main.cpp 

CC		= c++-11
# CC		= clang++

CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address 

CFLAGS	+= -I$I 
SRCS	:= $(foreach file,$(SRCS),$S$(file))
OBJS	= $(SRCS:$S%=$O%.o)
DEPS	= $(SRCS:$S%=$D%.d)
RM		= /bin/rm -rf

.PHONY: all clean fclean re test tree_test subject_test vector_test tree_test

all:	$(NAME)
$O:
		@mkdir $@

$(OBJS): | $O

$(OBJS):	$O%.o: $S%
			@echo "Compiling $^: "
			@$(CC) $(CFLAGS) -c $< -o $@
			@echo "✓"

$D:
		@mkdir $@

$(NAME):	$(OBJS)
			@echo "Assembling $(NAME)"
			@$(CC) $(LDFLAGS) -I $I $^ -o $@

clean:
		@echo "Cleaning up..."
		@$(RM) $D $O

fclean: clean
		@echo "Everything!"
		@$(RM) $(NAME) test tree_test minitest subject_test benchmarkmake fclean

vector_test:	fclean
		@$(CC) $(CFLAGS) -I tests/ srcs/main_randVecTest.cpp -o vector_test
		./vector_test

tree_test:
		@$(CC)  $(CFLAGS) -I $I srcs/main_randTreeTest.cpp -g3 -o tree_test -fsanitize=address
		./tree_test

test:	fclean
		@$(CC) $(CFLAGS) -I $I srcs/test.cpp -o test
		./test

subject_test:	fclean
				@$(CC) $(CFLAGS) -I $I srcs/main_subject.cpp -o subject_test
				./subject_test

benchmark:		fclean
				@$(CC) $(CFLAGS) srcs/main_benchmark.cpp -o benchmark
				./benchmark

benchmarkFT:	fclean
				@$(CC) $(CFLAGS) srcs/main_benchmark.cpp -D FT=0 -o benchmark
				./benchmark

benchmarkSTD:	fclean
				@$(CC) $(CFLAGS) srcs/main_benchmark.cpp -D STD=0 -o benchmark
				./benchmark
fullTest:		all
				./$(NAME)
				make benchmark


re:	fclean all
