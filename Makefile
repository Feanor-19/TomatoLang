all: front middle back

clean: clean_front clean_middle clean_back

PROG_DIR = programs/test_program/

PROG_TEXT = prog.txt
PROG_AST  = compiler_tree.txt
PROG_NASM = asm.nasm
PROG_OBJ  = obj.o
PROG_PROG = prog

TOMATO_LIB = tomato_stdlib

ifdef IMG_DIR
DO_DUMP = --img-dumps $(IMG_DIR)
else
DO_DUMP = 
endif

.PHONY: tomato
tomato: $(PROG_DIR)/$(PROG_PROG)


$(PROG_DIR)/$(PROG_AST): $(PROG_DIR)/$(PROG_TEXT)
	./frontend/bin/frontend -i $(PROG_DIR)/$(PROG_TEXT) -o $(PROG_DIR)/$(PROG_AST) $(DO_DUMP)

$(PROG_DIR)/$(PROG_NASM): $(PROG_DIR)/$(PROG_AST)
	./backend_x86_64/bin/backend -i $(PROG_DIR)/$(PROG_AST) -o $(PROG_DIR)/$(PROG_NASM)

$(PROG_DIR)/$(PROG_OBJ): $(PROG_DIR)/$(PROG_NASM)
	nasm -f elf64 -o $(PROG_DIR)/$(PROG_OBJ) $(PROG_DIR)/$(PROG_NASM)

$(PROG_DIR)/$(PROG_PROG): $(PROG_DIR)/$(PROG_OBJ) 
	ld $(PROG_DIR)/$(PROG_OBJ) -o $(PROG_DIR)/$(PROG_PROG) -ltomato -L $(TOMATO_LIB)/bin

#-lc -I /lib64/ld-linux-x86-64.so.2

.PHONY: cook
cook:
	./$(PROG_DIR)/$(PROG_PROG)

.PHONY: middle
middle:
	@make -C middleend

.PHONY: run_middle
run_middle:
	@make run -C middleend

.PHONY: clean_middle
clean_middle:
	@make clean -C middleend

.PHONY: back
back:
	@make -C backend_x86_64

.PHONY: run_back
run_back:
	@make run -C backend_x86_64

.PHONY: clean_back
clean_back:
	@make clean -C backend_x86_64

.PHONY: front
front:
	@make -C frontend

.PHONY: run_front
run_front:
	@make run -C frontend

.PHONY: clean_front
clean_front:
	@make clean -C frontend
