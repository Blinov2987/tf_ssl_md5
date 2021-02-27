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
	sha512.h                \
	base64.h                \
    des.h                   \
    output.h

FT_SSL_HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(FT_SSL_HEADERS_LIST))

FT_SSL_SOURCES_DIRECTORY = ./srcs/

FT_SSL_SOURCES_LIST =                    \
	main.c                               \
	utils/args_finder.c                  \
    utils/args_helper_00.c               \
    utils/errors_00.c                    \
    utils/errors_01.c                    \
    utils/free_utils.c                   \
    utils/ft_safe_memalloc.c             \
    utils/ft_lstadd_back.c               \
    utils/errors_02.c                    \
    utils/reader_helper.c                \
    utils/hashing_utils.c                \
    utils/print_output_00.c              \
    utils/print_output_01.c              \
    utils/print_output_02.c              \
    utils/entrance_to_hash_commands.c    \
    utils/fill_commands_00.c             \
    utils/base64_args_00.c               \
    utils/entrance_to_base64.c           \
    utils/base64_in_prism.c              \
    utils/print_output_cipher_00.c       \
    utils/des_args.c                     \
    utils/validate_pass_00.c             \
    utils/errors_03.c                    \
    utils/entrance_to_des.c              \
    utils/print_output_cipher_01.c       \
    utils/des_args_01.c                  \
    utils/entrance_to_des_01.c           \
    utils/split_by_command.c             \
    key_utils/generate_utils_00.c        \
    key_utils/generate_key.c             \
    key_utils/pass_reader.c              \
    hash_func/md5_00.c                   \
    hash_func/sha256_00.c                \
    hash_func/md5_01.c                   \
    hash_func/md5_02.c                   \
    hash_func/sha256_01.c                \
    hash_func/sha256_02.c                \
    hash_func/sha256_03.c                \
    hash_func/sha256_04.c                \
    hash_func/sha512_00.c                \
    hash_func/sha512_01.c                \
    hash_func/sha512_02.c                \
    hash_func/sha512_03.c                \
    hash_func/sha256_00.c                \
    hash_func/md5_03.c                   \
    cipher_func/base64.c                 \
    cipher_func/base64_enc_00.c          \
    cipher_func/base64_dec_00.c          \
    cipher_func/des_starter.c            \
    cipher_func/des.c                    \
    cipher_func/ecb.c                    \
    cipher_func/cbc.c                    \
    cipher_func/des3.c                   \
    cipher_func/pcbc.c                   \
    cipher_func/cfb.c                    \
    cipher_func/ofb.c                    \
    cipher_func/ctr.c                    \
    cipher_func/divide_by_des_mode.c     \
    cipher_func/des_utils_00.c           \
    cipher_func/des_utils_01.c


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
