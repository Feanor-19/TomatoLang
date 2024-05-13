#include "tr_IR_to_NASM_funcs.h"

// DSL

#define UNUSED(var) do{var = var;}while(0)

#define ASSERT_ALL() \
do{                  \
    assert(block);   \
    assert(stream);  \
    assert(counters);\
} while (0)

#define WRP(func__) do                      \
{                                           \
    Status stat__ = func__;                 \
    if (stat__ != STATUS_OK) return stat__; \
} while(0)

#define FACT_TR_IR_NASM_ARGS block, stream, counters

#define SECTION_TEXT() PRINT("section .text")
#define SECTION_RODATA() PRINT("section .rodata")

#define NEWLINE() putc('\n', stream)
#define COMMA() putc(',', stream)

inline void print_arg(arg_t arg, FILE *stream)
{
    switch (arg.type)
    {
    case IRB_ARG_TYPE_CONST_STR_ADDR:
    {
        IRBlock *target = (IRBlock*) arg.addr;
        PRINT_WO_NEWLINE(" LSC_%lu ", target->lbl_str_const );
        break;
    }
    case IRB_ARG_TYPE_IMM_CONST:
    {
        PRINT_WO_NEWLINE(" %ld ", arg.imm_const);
        break;
    }
    case IRB_ARG_TYPE_MEM:
    {
        const char *base_reg = REGS[ arg.mem.base_reg ];
        const char *index_reg = REGS[ arg.mem.index_reg ];
        if (arg.mem.scale != 0)
            PRINT_WO_NEWLINE(" QWORD [%s + %s * %d + %ld] ", base_reg, index_reg, arg.mem.scale, arg.mem.disp);
        else
            PRINT_WO_NEWLINE(" QWORD [%s + %ld] ", base_reg, arg.mem.disp);
        break;
    }
    case IRB_ARG_TYPE_MEM_NUM_CNST:
    {
        IRBlock *target = (IRBlock*) arg.mem_num_cnst;
        PRINT_WO_NEWLINE(" QWORD [LNC_%lu] ", target->lbl_num_const);
        break;
    }
    case IRB_ARG_TYPE_REG:
    {
        PRINT_WO_NEWLINE(" %s ", REGS[arg.reg]);
        break;
    }
    case IRB_ARG_TYPE_REG_XMM:
    {
        PRINT_WO_NEWLINE(" %s ", REGS_XMM[arg.reg_xmm]);
        break;
    }
    default:
        ASSERT_UNREACHEABLE();
        break;
    }
}

#define PRINT_ARG(arg__) print_arg(arg__, stream)

#define ARG_SRC block->data.arg_src
#define ARG_DST block->data.arg_dst

#define ARG_1 block->data.arg1
#define ARG_2 block->data.arg2

// --------------------------------------------------------

Status tr_IR_to_NASM_DUMMY (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();
    
    if (block->data.comment)
        PRINT("; %s", block->data.comment);

    return STATUS_OK;
}

Status tr_IR_to_NASM_EXTERN_KW (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("extern %s", block->data.func_name);

    return STATUS_OK;
}

Status tr_IR_to_NASM_GLOBAL_KW (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("global %s", block->data.func_name);

    return STATUS_OK;
}


Status tr_IR_to_NASM_LBL_FUNC_NAME (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT("%s:", block->data.func_name);

    return STATUS_OK;
}


Status tr_IR_to_NASM_NUM_CONST (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    SECTION_RODATA();
    block->lbl_num_const = counters->lbl_num_const++;
    PRINT("LNC_%lu \tdq %#lf", block->lbl_num_const, block->data.num_const);
    SECTION_TEXT();

    return STATUS_OK;
}

Status tr_IR_to_NASM_STR_CONST (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    SECTION_RODATA();
    block->lbl_str_const = counters->lbl_str_const++;
    PRINT("LSC_%lu \tdb \"%s\", 0x0a, 0x0", block->lbl_str_const, block->data.str_const);
    SECTION_TEXT();

    return STATUS_OK;
}


Status tr_IR_to_NASM_PUSH (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("push");
    PRINT_ARG( ARG_SRC );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_POP (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("pop");
    PRINT_ARG( ARG_DST );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_MOV (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    if ( (ARG_DST.type == IRB_ARG_TYPE_REG_XMM && ARG_SRC.type == IRB_ARG_TYPE_MEM)
     ||  (ARG_DST.type == IRB_ARG_TYPE_MEM     && ARG_SRC.type == IRB_ARG_TYPE_REG_XMM) )
    {
        PRINT_INSTR_WO_NEWLINE("movsd");
    }
    else
    {
        PRINT_INSTR_WO_NEWLINE("mov");
    }

    PRINT_ARG( ARG_DST );
    COMMA();
    PRINT_ARG( ARG_SRC );
    NEWLINE();

    return STATUS_OK;
}


Status tr_IR_to_NASM_ADD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("add");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_SUB (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("sub");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}


Status tr_IR_to_NASM_ADDSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("addsd");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_SUBSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("subsd");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_MULSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("mulsd");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}

Status tr_IR_to_NASM_DIVSD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("divsd");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}


Status tr_IR_to_NASM_COMISD (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR_WO_NEWLINE("comisd");
    PRINT_ARG( ARG_1 );
    COMMA();
    PRINT_ARG( ARG_2 );
    NEWLINE();

    return STATUS_OK;
}


inline Status jmp_helper( const char *jmp_type, FORMAL_TR_IR_NASM_ARGS )
{
    UNUSED(counters);

    IRBlock *target = (IRBlock*) block->data.instr_ptr;
    assert(target->lbl_cmn_set);
    PRINT_INSTR("%s LCC_%lu", jmp_type, target->lbl_cmn);

    return STATUS_OK;
}

Status tr_IR_to_NASM_JMP (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "jmp", FACT_TR_IR_NASM_ARGS ));    

    return STATUS_OK;
}

Status tr_IR_to_NASM_JE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "je", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}

Status tr_IR_to_NASM_JNE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "jne", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}

Status tr_IR_to_NASM_JA (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "ja", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}

Status tr_IR_to_NASM_JAE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "jae", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}

Status tr_IR_to_NASM_JB (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "jb", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}

Status tr_IR_to_NASM_JBE (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    WRP(jmp_helper( "jbe", FACT_TR_IR_NASM_ARGS ));

    return STATUS_OK;
}


Status tr_IR_to_NASM_CALL (FORMAL_TR_IR_NASM_ARGS)
{
    ASSERT_ALL();

    PRINT_INSTR("call %s", block->data.func_name);

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

    PRINT_INSTR_WO_NEWLINE("sqrtsd");
    PRINT_ARG( ARG_DST );
    COMMA();
    PRINT_ARG( ARG_SRC );
    NEWLINE();

    return STATUS_OK;
}
