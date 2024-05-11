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
    IR_BLOCK_TYPE_DUMMY,    // e.g. for comments or labels, which aren't at any instructions
    
    IR_BLOCK_TYPE_PUSH,     // Imagining it is universal (including XMM and 'mem to mem')
    IR_BLOCK_TYPE_POP,      // Imagining it is universal (including XMM and 'mem to mem')
    IR_BLOCK_TYPE_MOV,      

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

enum IRBlockDataType
{
    IR_BLOCK_NO_DATA,
    IR_BLOCK_DATA_INSTR_PTR,
    IR_BLOCK_DATA_FUNC_NAME,
    IR_BLOCK_DATA_ARGS_DIR, // arg_src, arg_dst
    IR_BLOCK_DATA_ARGS_NUM, // arg1, arg2
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


enum IRBlockArgType
{
    IRB_ARG_TYPE_REG,
    IRB_ARG_TYPE_REG_XMM,
    IRB_ARG_TYPE_MEM,
    IRB_ARG_TYPE_IMM_CONST,
};

struct arg_t
{
    IRBlockArgType type;
    union 
    {
        reg_t reg;
        reg_xmm_t reg_xmm;
        mem_t mem;
        num_t imm_const; 
    };
};


struct IRBlockData
{
    IRBlockType     type      = IR_BLOCK_TYPE_DUMMY;

    //! @note If just a comment is needed (not appended to some instruction), 
    //! use 'IR_BLOCK_TYPE_DUMMY' and 'IR_BLOCK_NO_DATA'.
    const char* comment = NULL;

    //! @note 'type' (see above) defines which one of the below union members is used.
    union 
    {
        IRBlock *instr_ptr; // plays role of a label (e.g. 'jmp') 
        
        const char *func_name; //!< @attention Points to memory, allocated by AST

        struct 
        {
            arg_t arg_src;
            arg_t arg_dst;
        };

        struct
        {
            arg_t arg1;
            arg_t arg2;
        };
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

struct Context
{
    uint args_num     = 0;
    uint loc_vars_num = 0;
};


#define DEF_REG( reg__ ) REG_##reg__,
enum Regs
{
    #include "regs_defs.h"
    REG_DUMMY
};
#undef DEF_REG

#define DEF_REG( reg__ ) #reg__,
const char * const REGS[] = 
{
    #include "regs_defs.h"
    "REG_DUMMY"
};
#undef DEF_REG


#define DEF_REG_XMM( reg__ ) REG_##reg__,
enum RegsXMM
{
    #include "regs_xmm_def.h"
    REG_XMM_DUMMY
};
#undef DEF_REG_XMM

#define DEF_REG_XMM( reg__ ) #reg__,
const char * const REGS_XMM[] = 
{
    #include "regs_xmm_def.h"
    "REG_XMM_DUMMY"
};
#undef DEF_REG_XMM

//! @brief Number of XMM registers used to pass arguments to functions.
const size_t NUM_OF_XMM_REGS_TO_PASS_ARGS = 8;

const reg_xmm_t REG_XMM_TMP_1 = REG_xmm8;
const reg_xmm_t REG_XMM_TMP_2 = REG_xmm9;

enum 
{
    BYTE  = 1,
    WORD  = 2,
    DWORD = 4,
    QWORD = 8,
};

#endif /* BACK_COMMON_H */