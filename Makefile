
Red=\033[31m
Green=\033[32m
Cyan=\033[36m
End=\033[0m

TARGET = cluster

SRC_PATH = ./srcs
SRC_FILE = main.c error.c client_socket.c ip_validity.c server_select.c \
		   socket.c send.c

OBJ_PATH = ./objs
OBJ_FILE = $(SRC_FILE:.c=.o)
DEP_FILE = $(SRC_FILE:.c=.d)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILE))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILE))
DEP = $(addprefix $(OBJ_PATH)/,$(DEP_FILE))

CFLAGS = -Wall -Wextra -g -I./includes -fsanitize=address -g
CPPFLAGS = -MMD -MP

ifndef VERBOSE
.SILENT:
VERBOSE=0
endif

all: $(TARGET)

$(TARGET): $(OBJ) 
	#@$(MAKE) -C libft/ VERBOSE=$(VERBOSE)
	@gcc $(CFLAGS) -o $(TARGET) $(OBJ) $(LIB)
	@echo -e "Compilation of $(Cyan)$(TARGET)$(End) : ${Green}Done${End}"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@gcc $(CFLAGS) -c $< $(CPPFLAGS) -o $@
	@echo -e "[${Green}Compiled${End}] : $<"

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)
	#@$(MAKE) -C libft/ clean
	@rm -f $(DEP)
	@rmdir $(OBJ_PATH) 2> /dev/null || (true && if [ -d "$(OBJ_PATH)" ]; then\
		echo -e "$(Red)ERROR$(End)	: $(OBJ_PATH) is not empty."; fi)
	@echo -e "$(Red)$(TARGET)$(End) : Removing objects"

fclean: clean
	@rm -f $(TARGET)
	#@$(MAKE) -C libft/ clean
	@echo -e "$(Red)$(TARGET)$(End) : Removing $(TARGET)"

re: fclean all

-include $(DEP)