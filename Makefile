.PHONY : init all re clean fclean
CXX = c++
FLAGS = -Wall -Wextra -Werror -MMD -MP -g3 -std=c++98 -I.
NAME = IRC
CLASSES = class/irc
FILES = src/main
OBJ_DIR = .build/
SRCS = $(addsuffix .cpp, $(CLASSES)) $(addsuffix .cpp,$(FILES))
OBJS = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(patsubst %.cpp, $(OBJ_DIR)%.d, $(SRCS))

all: $(NAME)
$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME) 
-include $(DEPS)

create_files:
	@for file in $(SRCS) $(addsuffix .hpp, $(CLASSES)) ; do \
		if [ ! -f $$file ]; then \
		mkdir -p $$(dirname $$file); \
		touch $$file; \
		fi \
	done

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all