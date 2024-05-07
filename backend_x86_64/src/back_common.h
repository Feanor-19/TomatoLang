#ifndef BACK_COMMON_H
#define BACK_COMMON_H

#include "common.h"


typedef size_t cnt_t;
#define SPECF_CNT_T "%lu"

#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "back_statuses.h"
};
#undef DEF_STATUS



enum IRBlockType
{
    IR_BLOCK_TYPE_DUMMY,
    
};

struct IRBlockData
{
    IRBlockType type = IR_BLOCK_TYPE_DUMMY;
};

//! @brief Block of IR (see below).
struct IRBlock
{
    IRBlockData data = {};

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


#endif /* BACK_COMMON_H */