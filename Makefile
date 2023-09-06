NAME		=	computor_v2

CC			=	g++
CFLAGS		=	#-Wall -Werror -Wextra
DRAW_FLAG	=	-lm -lglfw -lGL -ldl
GLFW_LIB	=	-I./external/glfw

HEADER_DIR	=	./include
SRC_DIR		=	./src
OBJ_DIR		=	./obj

HEADER		=	main_library.hpp \
				Computor_v2.hpp \
				Lexer.hpp \
				Token.hpp \
				enum.hpp \
				Value.hpp \
				Rational.hpp \
				Complex.hpp \
				Matrix.hpp \
				Function.hpp \
				Computation.hpp \
				math_function.hpp \
				Computor_v1.hpp \
				draw_curve.hpp

SRC			=	main.cpp \
				Computor_v2.cpp \
				Lexer.cpp \
				Token.cpp \
				Rational.cpp \
				Complex.cpp \
				Matrix.cpp \
				Function.cpp \
				Computation.cpp \
				math_function.cpp \
				Computor_v1.cpp \
				draw_curve.cpp

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[32m"
C_GOOD		=	"\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all			:	$(NAME)

bonus		:	$(NAME)

$(OBJ)		: 	| $(OBJ_DIR)	

$(OBJ_DIR)	:
				@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.cpp ${HEADER_DIR}/*.hpp Makefile
					$(CC) $(CFLAGS) -c $< -o $@ $(GLFW_LIB)

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(DRAW_FLAG) $(GLFW_LIB)
				@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean		:
				@$(RM_DIR) $(OBJ_DIR)
				@echo "\tCleaning...\t" [ $(OBJ_DIR) ] $(OK)

fclean		:	clean
				@$(RM_FILE) $(NAME)
				@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re			:	fclean all

.PHONY		:	all, clean, fclean, re
