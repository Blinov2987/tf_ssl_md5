FT_SSL_NAME = ft_ssl

CC = gcc
FLAGS = -Wall -Wextra -Werror

FT_SSL_LIBRARIES = -lftprintf -L$(FT_PRINTF_DIRECTORY)

FT_SSL_INCLUDES = \
	-I$(HEADERS_DIRECTORY)\
	-I$(LIBFT_HEADERS)\
	-I$(FT_PRINTF_HEADERS)

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./ft_lftprintf/includes/libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)

FT_PRINTF = $(FT_PRINTF_DIRECTORY)libftprintf.a
FT_PRINTF_DIRECTORY = ./ft_lftprintf/
FT_PRINTF_HEADERS = $(FT_PRINTF_DIRECTORY)includes/

HEADERS_DIRECTORY = ./includes/

FT_SSL_HEADERS_LIST =		\
	args.h					\
	constants.h				\
	errors.h				\
	ft_ssl.h				\
	md5.h					\
	sha256.h				\
	sha512.h

FT_SSL_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(FT_SSL_HEADERS_LIST))

FT_SSL_SOURCES_DIRECTORY = ./srcs/

FT_SSL_SOURCES_LIST =		\
	args_finder.c			\
	args_helper_00.c		\
	errors_00.c				\
	errors_01.c				\
	errors_02.c				\
	free_utils.c			\
	ft_lstadd_back.c		\
	ft_safe_memalloc.c		\
	hashing_utils.c			\
	main.c					\
	md5_00.c				\
	md5_01.c				\
	md5_02.c				\
	md5_03.c				\
	print_output_00.c		\
	print_output_01.c		\
	print_output_02.c		\
	reader_helper.c			\
	sha256_00.c				\
	sha256_01.c				\
	sha256_02.c				\
	sha256_03.c				\
	sha256_04.c				\
	sha512_00.c				\
	sha512_01.c				\
	sha512_02.c				\
	sha512_03.c				\
	split_by_command.c

FT_SSL_SOURCES = $(addprefix $(FT_SSL_SOURCES_DIRECTORY), $(FT_SSL_SOURCES_LIST))

OBJECTS_DIRECTORY = ./objects/

FT_SSL_OBJECTS_DIRECTORY = $(OBJECTS_DIRECTORY)FT_SSL/
FT_SSL_OBJECTS_LIST = $(patsubst %.c, %.o, $(FT_SSL_SOURCES_LIST))
FT_SSL_OBJECTS	= $(addprefix $(FT_SSL_OBJECTS_DIRECTORY), $(FT_SSL_OBJECTS_LIST))

.PHONY: all clean fclean re

CREAT = \033[0;32m
IMPORTANT =\033[1;36m
DELETE = \033[0;31m
EOC = \033[0m

all: $(FT_SSL_NAME)

$(FT_SSL_NAME): $(FT_PRINTF) $(FT_SSL_OBJECTS_DIRECTORY) $(FT_SSL_OBJECTS)
	@$(CC) $(FLAGS) $(FT_SSL_INCLUDES) $(FT_SSL_OBJECTS) -o $(FT_SSL_NAME) $(FT_SSL_LIBRARIES)
	@echo "$(CREAT)objects were created! >>>$(EOC)"
	@echo "$(IMPORTANT)FT_SSL was created! >>>$(EOC)"

$(FT_SSL_OBJECTS_DIRECTORY):
	@mkdir -p $(FT_SSL_OBJECTS_DIRECTORY)
	@echo "$(CREAT)$(FT_SSL_OBJECTS_DIRECTORY) was created! >>>$(EOC)"

$(FT_SSL_OBJECTS_DIRECTORY)%.o : $(FT_SSL_SOURCES_DIRECTORY)%.c $(FT_SSL_HEADERS)
	@$(CC) $(FLAGS) -c $(FT_SSL_INCLUDES) $< -o $@
	@echo "$(CREAT)>.. please wait ... objects creating..>>$(EOC)"

$(FT_PRINTF):
	@echo "$(CREAT)Creating $(FT_PRINTF) >>>$(EOC)"
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY)

clean:
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(DELETE)>>> $(OBJECTS_DIRECTORY) was deleted ..............   >>>$(EOC)"
	@echo "$(DELETE)>>> object files were deleted ............. >>>$(EOC)"

fclean: clean
	@$(MAKE) -sC $(FT_PRINTF_DIRECTORY) fclean
	@echo "$(DELETE)>>> $(FT_PRINTF) was deleted >>$(EOC)"
	@rm -f $(FT_SSL_NAME)
	@echo "$(DELETE)>>> $(FT_SSL_NAME) was deleted ................    >>>$(EOC)"

re:
	@$(MAKE) fclean
	@$(MAKE) all
