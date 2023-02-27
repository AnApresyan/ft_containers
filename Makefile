NAME = containers
SRCS = $(wildcard *.cpp)
#SRCS = rb_tree.hpp
OBJS = ${SRCS:.cpp=.o}
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${CXXFLAGS} -o ${NAME}

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re .c.o