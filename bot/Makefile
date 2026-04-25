.PHONY : init all re clean fclean debug
CXX = c++
FLAGS = -Wall -Wextra  -MMD -MP -g3 -std=c++98 -Iinc -I../inc
NAME = bot
FILES =  main Bot Bot_exceptions
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

debug: FLAGS += -DDEBUG=1
debug : re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all