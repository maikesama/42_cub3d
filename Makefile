SRCS			= get_next_line_utils_bonus.c get_next_line_bonus.c \
					parsing.c parsing_main.c parsing_main_ut.c \
					utils.c utils2.c utils3.c utils4.c\
					engine_utils.c engine_utils2.c engine_utils3.c \
					engine_utils4.c engine_utils5.c \
					cub3d.c
OBJS			= $(SRCS:.c=.o)

ifeq '$(findstring ;,$(PATH))' ';'
    detected_OS := Windows
else
    detected_OS := $(shell uname 2>/dev/null || echo Unknown)
    detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
    detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
    detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
endif


MV_CMD			= 

ifeq ($(detected_OS),Darwin)        # Mac OS X
    CC				= gcc
	RM				= rm -f
	LFLAGS			=
	LIBS			= -Lmlx -lmlx -Imlx -framework OpenGL -framework AppKit -lm
	MLX				= libmlx.dylib
	MLX_PATH		= ./mlx
	CFLAGS			= -Wall -Wextra -Werror -I$(MLX_PATH)
	# MV_CMD			= @mv $(MLX_PATH)/$(MLX) .
endif

ifeq ($(detected_OS),Linux)
    CC				= gcc
	RM				= rm -f
	LFLAGS			= 
	LIBS			= -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
	MLX				= libmlx.a
	MLX_PATH		= ./minilibx-linux
	CFLAGS			= -Wall -Wextra -Werror -I/usr/include -I$(MLX_PATH) -O3
endif

ifeq ($(detected_OS),Windows)
@echo "Sorry, Windows is not supported\n"
else

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				$(CC) ${LFLAGS} ${OBJS} ${LIBS} -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
				@$(MAKE) -C $(MLX_PATH)
				$(MV_CMD)

clean:
				@$(MAKE) -C mlx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

endif