CC=g++

SAN = -fsanitize=alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr,leak,address
CFLAGS  =	-D _DEBUG -ggdb3 -std=c++17 -Wall -Wextra -Weffc++ 									\
			-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations 				\
			-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported 				\
			-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal 						\
			-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 				\
			-Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual 		\
			-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow 					\
			-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 			\
			-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types 			\
			-Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef 				\
			-Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 	\
			-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs 	\
			-Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector 				\
			-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer					\
			-Wstack-usage=8192 -pie -fPIE -Werror=vla $(SAN)

OBJ 	= obj
SRC 	= src
BIN 	= bin
CMN 	= ./../common
LOGS 	= ./logs
CURR_PROG = ./../programs/test_program

COMMON_LIB_DIR = /usr/lib/feanor
COMMON_INC_DIR = /usr/include/feanor

LIB_NAMES 			= tree
LIB_SUBST 			= -L$(COMMON_LIB_DIR)/$(lib_name) -l$(lib_name)
LIB_HEADERS_SUBST 	= -I $(COMMON_INC_DIR)/$(lib_name)

LIBS 			= $(foreach lib_name,$(LIB_NAMES),$(LIB_SUBST))
LIB_HEADERS		= $(foreach lib_name,$(LIB_NAMES),$(LIB_HEADERS_SUBST))
SOURCES 		= $(wildcard $(SRC)/*.cpp)
OBJFILES 		= $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.cpp=.o))
CMN_SOURCES		= $(wildcard $(CMN)/$(SRC)/*.cpp)
CMN_OBJFILES	= $(patsubst $(CMN)/$(SRC)/%,$(CMN)/$(OBJ)/%,$(CMN_SOURCES:.cpp=.o))
OUT 			= ./$(BIN)/backend
DUMP_FOLDER 	= dumps

$(OUT) : $(OBJFILES) $(CMN_OBJFILES)
	$(CC) -o $@ $(CFLAGS) $^ $(LIB_HEADERS) $(LIBS) -I $(CMN)/$(SRC)

$(OBJ)/%.o : $(SRC)/%.cpp
	@$(CC) -c $(CFLAGS) -o $@ $< -I $(CMN)/$(SRC)

$(CMN)/$(OBJ)/%.o : $(CMN)/$(SRC)/%.cpp
	@$(CC) -c $(CFLAGS) -o $@ $<

.PHONY: run
run:
	$(OUT) -i $(CURR_PROG)/compiler_tree.txt -o $(CURR_PROG)/asm.txt --img-dumps $(DUMP_FOLDER)/image_dumps/

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(CMN_OBJFILES) $(OUT)

.PHONY: clean_dumps
clean_dumps:
	rm -r -f $(DUMP_FOLDER)/*

.PHONY: clean_logs
clean_logs:
	rm -r -f $(LOGS)/*
