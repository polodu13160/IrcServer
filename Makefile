.PHONY : init all re clean fclean debug
CXX = c++
FLAGS = -Wall -Wextra  -MMD -MP -g3 -std=c++98 -Iinc
NAME = IrcServer
FILES =  src/main src/Channel/Channel src/MessageParsing/Message src/Server/Server src/Commands/JOIN \
 		src/Commands/USER src/Commands/NICK src/User/User src/MessageParsing/main src/Commands/cmdPars src/Commands/LIST
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