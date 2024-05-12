CC=g++

CFLAGS = -std=c++17 -Wall -Wextra -Weffc++ 													\
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
		-Wstack-protector -pie -fPIE -Werror=vla

SRC_ASM_EXT = .nasm
SRC_C_EXT   = .cpp

SRC_ASM = src_asm
SRC_C   = src_c
OBJ_ASM = obj_asm
OBJ_C   = obj_c
BIN     = bin
LST     = lst
OUT     = $(BIN)/libtomato.a

SOURCES_ASM 	= $(wildcard $(SRC_ASM)/*$(SRC_ASM_EXT))
OBJFILES_ASM    = $(patsubst $(SRC_ASM)/%,$(OBJ_ASM)/%,$(SOURCES_ASM:$(SRC_ASM_EXT)=.o))

SOURCES_C 		= $(wildcard $(SRC_C)/*$(SRC_C_EXT))
OBJFILES_C    	= $(patsubst $(SRC_C)/%,$(OBJ_C)/%,$(SOURCES_C:$(SRC_C_EXT)=.o))

.PHONY: make_lib
make_lib: $(OBJFILES_C) $(OBJFILES_ASM)
	rm -rf $(OUT)/*
	ar -cvq $(OUT) $^

$(OBJ_ASM)/%.o : $(SRC_ASM)/%$(SRC_ASM_EXT)
	@nasm -f elf64 -o $@ $<

$(OBJ_C)/%.o : $(SRC_C)/%$(SRC_C_EXT)
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJFILES_ASM) $(OBJFILES_C) $(OUT)

