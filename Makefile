.PHONY : init all re clean fclean
CXX = c++
FLAGS = -Wall -Wextra -Werror -MMD -MP -g3 -std=c++98 -Iinc
NAME = IrcServer
FILES =  src/main src/Channel/channel
OBJ_DIR = .build/
SRCS = $(addsuffix .cpp,$(FILES))
OBJS = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(patsubst %.cpp, $(OBJ_DIR)%.d, $(SRCS))

all: $(NAME)
$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME) 
-include $(DEPS)



clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all