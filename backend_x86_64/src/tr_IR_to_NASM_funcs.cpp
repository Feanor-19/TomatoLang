#include "tr_IR_to_NASM_funcs.h"

// DSL

#define ASSERT_ALL() \
do{                  \
    assert(stream);  \
} while (0)

#define BLOCK block->data

#define SECTION_TEXT() PRINT("section .text")
#define SECTION_RODATA() PRINT("section .rodata")

// --------------------------------------------------------

Status tr_IR_to_NASM_DUMMY (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("; %s", block_data.comment);

    return STATUS_OK;
}

Status tr_IR_to_NASM_EXTERN_KW (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("extern %s", block_data.func_name);

    return STATUS_OK;
}

Status tr_IR_to_NASM_GLOBAL_KW (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("global %s", block_data.func_name);

    return STATUS_OK;
}


Status tr_IR_to_NASM_LBL_FUNC_NAME (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("%s:", block_data.func_name);

    return STATUS_OK;
}


Status tr_IR_to_NASM_NUM_CONST (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    SECTION_RODATA();
    PRINT("LNC_%lu\tdq%g", counters->lbl_num_const++, block_data.num_const);
    SECTION_TEXT();

    return STATUS_OK;
}

Status tr_IR_to_NASM_STR_CONST (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    SECTION_RODATA();
    PRINT("LSC_%lu \tdb \"%s\", 0x0a", counters->lbl_num_const++, block_data.num_const);
    SECTION_TEXT();

    return STATUS_OK;
}


Status tr_IR_to_NASM_PUSH (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_POP (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_MOV (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}


Status tr_IR_to_NASM_ADD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_SUB (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}


Status tr_IR_to_NASM_ADDSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_SUBSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_MULSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_DIVSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}


Status tr_IR_to_NASM_COMISD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}


Status tr_IR_to_NASM_JMP (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    

    return STATUS_OK;
}

Status tr_IR_to_NASM_JE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_JNE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_JA (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_JAE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_JB (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}

Status tr_IR_to_NASM_JBE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}


Status tr_IR_to_NASM_CALL (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR("call %s", block_data.func_name);

    return STATUS_OK;
}

Status tr_IR_to_NASM_LEAVE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR("leave");

    return STATUS_OK;
}

Status tr_IR_to_NASM_RET (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR("ret");

    return STATUS_OK;
}


Status tr_IR_to_NASM_SQRTSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();



    return STATUS_OK;
}
