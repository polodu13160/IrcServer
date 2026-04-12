.PHONY: clean fclean all re

FLAGS = -Wall -Wextra -Werror -std=c++98 -g3
CPP = c++
NAME = msgParser
HEADERS = cmd.hpp Message.hpp cmdPars.hpp
OBJDIR = ./obj

SRC = main.cpp Message.cpp cmd.cpp cmdPars.cpp

OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.cpp=.o)))

all : $(OBJDIR) $(NAME)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(NAME) : $(OBJ)
	$(CPP) $(FLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : %.cpp Makefile $(HEADERS)
	$(CPP) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJDIR)
fclean : clean
	rm -f $(NAME)
re : fclean all
