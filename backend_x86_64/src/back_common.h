#ifndef BACK_COMMON_H
#define BACK_COMMON_H

#include "common.h"


typedef size_t cnt_t;
#define SPECF_CNT_T "%lu"

typedef uint8_t reg_t;
typedef uint8_t reg_xmm_t;

#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "back_statuses.h"
};
#undef DEF_STATUS



enum IRBlockType
{
    IR_BLOCK_TYPE_DUMMY,
    
    IR_BLOCK_TYPE_PUSH,     
    IR_BLOCK_TYPE_POP,      
    IR_BLOCK_TYPE_MOV,      // imagining it is universal (including XMM and 'mem to mem')

    IR_BLOCK_TYPE_PUSH_XMM, // uses REG_PUSH_POP_XMM (r8?) instead of rsp
    IR_BLOCK_TYPE_POP_XMM,

    IR_BLOCK_TYPE_ADDSD,
    IR_BLOCK_TYPE_SUBSD,
    IR_BLOCK_TYPE_MULSD,
    IR_BLOCK_TYPE_DIVSD,

    IR_BLOCK_TYPE_COMISD,
    
    IR_BLOCK_TYPE_JMP,
    IR_BLOCK_TYPE_JE,
    IR_BLOCK_TYPE_JNE,
    IR_BLOCK_TYPE_JA,
    IR_BLOCK_TYPE_JAE,
    IR_BLOCK_TYPE_JB,
    IR_BLOCK_TYPE_JBE,

    IR_BLOCK_TYPE_CALL,

    IR_BLOCK_TYPE_SQRTSD,
};

enum MemScaleFactor
{
    SCALE_FACTOR_0 = 0,
    SCALE_FACTOR_1 = 1,
    SCALE_FACTOR_2 = 2,
    SCALE_FACTOR_4 = 4,
    SCALE_FACTOR_8 = 8,
};

//! @note Basereg + IndexReg * Scalefactor + Disp
struct mem_t
{
    reg_t base_reg;
    reg_t index_reg;
    MemScaleFactor scale;
    int16_t disp;
};

union arg
{
    reg_t reg;
    reg_xmm_t reg_xmm;
    mem_t mem;
};


struct IRBlockData
{
    IRBlockType type = IR_BLOCK_TYPE_DUMMY;

    union 
    {
        IRBlock *instr_ptr = NULL; // plays role of a label (e.g. 'jmp' or 'call')

        arg arg1;
        arg arg2;
        arg arg3;
    };
};

//! @brief Block of IR (see below).
struct IRBlock
{
    IRBlockData data;

    IRBlock *next = NULL;
    IRBlock *prev = NULL;
};

//! @brief Intermediate representation.
//! @details Double-linked list of blocks, each of them represents
//! an instruction from 'abstract assembler'.
struct IR
{
    IRBlock *head = NULL;
    IRBlock *tail = NULL;

    size_t blocks_count = 0;
};

struct Counters
{
    cnt_t cmp_c   = 0;
    cnt_t if_c    = 0;
    cnt_t while_c = 0;
    cnt_t and_c   = 0;
    cnt_t or_c    = 0;
    cnt_t not_c   = 0;
};


// TODO fill
const char * const REGS[] = 
{

};

const char * const REGS_XMM[] = 
{

};

#endif /* BACK_COMMON_H */