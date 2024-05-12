#ifndef BACK_COMMON_H
#define BACK_COMMON_H

#include "common.h"


typedef size_t cnt_t;
#define SPECF_CNT_T "%lu"

typedef uint8_t reg_t;
typedef uint8_t reg_xmm_t;
typedef int64_t disp_t;
typedef int64_t imm_const_t;

#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "back_statuses.h"
};
#undef DEF_STATUS


#define DEF_IRBLOCK_TYPE(name__) IR_BLOCK_TYPE_##name__,
enum IRBlockType
{
    #include "IRBlockType_defs.h"
};
#undef DEF_IRBLOCK_TYPE

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
    disp_t disp;
};


enum IRBlockArgType
{
    IRB_ARG_TYPE_REG,
    IRB_ARG_TYPE_REG_XMM,
    IRB_ARG_TYPE_MEM,
    IRB_ARG_TYPE_IMM_CONST,
    IRB_ARG_TYPE_MEM_VAR,
    IRB_ARG_TYPE_CONST_STR_ADDR,
};

struct arg_t
{
    IRBlockArgType type;
    union 
    {
        reg_t reg;
        reg_xmm_t reg_xmm;
        mem_t mem;
        imm_const_t imm_const; // if num_t is needed, IRBlock of type 'NUM_CONST' must be formed
        void *mem_var; // must be ptr to IRBlock of type 'NUM_CONST', translates as VALUE
        void *addr;    // must be ptr to IRBlock of type 'STR_CONST', translates as ADDRESS
    };
};


struct IRBlockData
{
    IRBlockType type = IR_BLOCK_TYPE_DUMMY;
    
    //! @brief plays role of a label (e.g. 'jmp')
    //! @attention MUST BE A PTR TO IRBlock
    void *instr_ptr = NULL;  

    //! @note 'type' (see above) defines which one of the below union members is used.
    union 
    {
        //! @note Comment blocks have type 'DUMMY'.
        const char* comment = NULL;
        
        //! @brief label with DQ in .rodata
        num_t num_const;

        //! @brief label with DB in .rodata.
        //! @note It's a pointer to memory, allocated by AST!
        const char *str_const;
        
        //!< @attention Either points to memory, allocated by AST, or to const string.
        const char *func_name;

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

    // Used in translation from IR to NASM
    bool lbl_cmn_set = false;
    size_t lbl_cmn       = (size_t)-1;
    size_t lbl_str_const = (size_t)-1;
    size_t lbl_num_const = (size_t)-1; 

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
    size_t lbl_cmn = 0;         //!< Some common label (in 'if', 'while', etc.)
    size_t lbl_num_const = 0;   //!< Label, naming const of type num_t
    size_t lbl_str_const = 0;   //!< Label, naming string const
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

const reg_xmm_t REG_XMM_TMP_1 = REG_xmm8;
const reg_xmm_t REG_XMM_TMP_2 = REG_xmm9;

const char * const STDLIB_INPUT     = "input";
const char * const STDLIB_PRINT_NUM = "print_num";
const char * const STDLIB_PRINT_STR = "print_str";
const char * const STDLIB_EXIT      = "_exit";

const char * const LBL_START = "_start";

//! @brief Common registers, used to pass parametres to funcs, listed in the right order.
Regs const REGS_TO_PASS_PARAMS_TO_FUNCS[] = 
{
    REG_rdi,
    REG_rsi,
    REG_rdx,
    REG_rcx,
    REG_r8,
    REG_r9
};

//! @brief XMM registers, used to pass parametres to funcs, listed in the right order.
RegsXMM const REGS_XMM_TO_PASS_PARAMS_TO_FUNCS[] = 
{
    REG_xmm0,
    REG_xmm1,
    REG_xmm2,
    REG_xmm3,
    REG_xmm4,
    REG_xmm5,
    REG_xmm6,
    REG_xmm7
};

//! @brief Number of XMM registers used to pass arguments to functions.
const size_t NUM_OF_XMM_REGS_TO_PASS_ARGS = SIZEARR(REGS_XMM_TO_PASS_PARAMS_TO_FUNCS);

enum 
{
    BYTE  = 1,
    WORD  = 2,
    DWORD = 4,
    QWORD = 8,
};

#endif /* BACK_COMMON_H */