
Red=\033[31m
Green=\033[32m
Cyan=\033[36m
End=\033[0m

TARGET = cluster

SRC_PATH = ./srcs
SRC_FILE = main.c error.c ip_validity.c send.c string_helper.c recv.c
SRC_FILE += server/server_process.c server/server_select.c server/server_cmd.c \
			server/server_helper.c
SRC_FILE += client/socket.c client/client_socket.c
SRC_FILE += protocols/read_file.c protocols/naive.c protocols/commands.c \
			protocols/commands_helper.c protocols/set.c protocols/run.c \
			protocols/close.c protocols/status.c protocols/return.c
SRC_FILE += identification/get_name_base.c identification/colors_helper.c

OBJ_PATH = ./objs
OBJ_FILE = $(SRC_FILE:.c=.o)
DEP_FILE = $(SRC_FILE:.c=.d)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILE))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILE))
DEP = $(addprefix $(OBJ_PATH)/,$(DEP_FILE))

CFLAGS = -Wall -Wextra -g -I./includes -fsanitize=address -g
CPPFLAGS = -MMD -MP
LIB = libft.a

ifndef VERBOSE
.SILENT:
VERBOSE=0
endif

all: $(TARGET)

$(TARGET): $(OBJ) 
	#@$(MAKE) -C libft/ VERBOSE=$(VERBOSE)
	@gcc $(CFLAGS) -lpthread -o $(TARGET) $(OBJ) $(LIB)
	@printf "Compilation of $(Cyan)$(TARGET)$(End) : ${Green}Done${End}\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)/protocols 2> /dev/null || true
	@mkdir $(OBJ_PATH)/identification 2> /dev/null || true
	@mkdir $(OBJ_PATH)/client 2> /dev/null || true
	@mkdir $(OBJ_PATH)/server 2> /dev/null || true
	@gcc $(CFLAGS) -c $< $(CPPFLAGS) -o $@
	@printf "[${Green}Compiled${End}] : $<\n"

.PHONY: clean fclean re

clean:
	@rm -f $(OBJ)
	#@$(MAKE) -C libft/ clean
	@rm -f $(DEP)
	@rmdir $(OBJ_PATH)/server 2> /dev/null || (true && if [ -d "$(OBJ_PATH)/server" ]; then\
		printf"$(Red)ERROR$(End)	: $(OBJ_PATH)/server is not empty.\n"; fi)
	@rmdir $(OBJ_PATH)/client 2> /dev/null || (true && if [ -d "$(OBJ_PATH)/client" ]; then\
		printf "$(Red)ERROR$(End)	: $(OBJ_PATH)/client is not empty.\n"; fi)
	@rmdir $(OBJ_PATH)/protocols 2> /dev/null || (true && if [ -d "$(OBJ_PATH)/protocols" ]; then\
		printf "$(Red)ERROR$(End)	: $(OBJ_PATH)/protocols is not empty.\n"; fi)
	@rmdir $(OBJ_PATH)/identification 2> /dev/null || (true && if [ -d "$(OBJ_PATH)/identification" ]; then\
		printf "$(Red)ERROR$(End)	: $(OBJ_PATH)/identification is not empty.\n"; fi)
	@rmdir $(OBJ_PATH) 2> /dev/null || (true && if [ -d "$(OBJ_PATH)" ]; then\
		printf "$(Red)ERROR$(End)	: $(OBJ_PATH) is not empty.\n"; fi)
	@printf "$(Red)$(TARGET)$(End) : Removing objects\n"

fclean: clean
	@rm -f $(TARGET)
	#@$(MAKE) -C libft/ clean
	@printf "$(Red)$(TARGET)$(End) : Removing $(TARGET)\n"

re: fclean all

-include $(DEP)
