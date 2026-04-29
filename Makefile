.PHONY : init all re clean fclean debug bot
CXX = c++
FLAGS = -Wall -Wextra  -MMD -MP -g3 -std=c++98 -Iinc
NAME = IrcServer
FILES =  src/main src/Channel/Channel src/MessageParsing/Message src/Server/Server src/Commands/JOIN \
       src/Commands/USER src/Commands/NICK src/User/User src/MessageParsing/parser src/Commands/cmdDispatch src/Commands/LIST \
       src/Server/Server_init src/Commands/PASS src/Commands/MODE_utils \
       src/Commands/QUIT src/Commands/TOPIC src/Commands/PART src/Commands/PONG src/Commands/WHO \
       src/Commands/MODE src/Commands/PRIVMSG src/Commands/NOTICE src/Commands/INVITE src/Commands/KICK

BOT_NAME = IrcBot
BOT_FILES = main Bot Bot_exceptions
BOT_SRCS = $(addprefix bot/, $(addsuffix .cpp, $(BOT_FILES)))
BOT_OBJS = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(BOT_SRCS))
BOT_DEPS = $(patsubst %.cpp, $(OBJ_DIR)%.d, $(BOT_SRCS))

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

bot: $(BOT_NAME)
$(BOT_NAME): $(BOT_OBJS)
	$(CXX) $(FLAGS) $(BOT_OBJS) -o $(BOT_NAME)

-include $(DEPS)
-include $(BOT_DEPS)

debug: FLAGS += -DDEBUG=1
debug : re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BOT_NAME)

re: fclean all