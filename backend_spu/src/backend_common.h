#ifndef BACKEND_COMMON_H
#define BACKEND_COMMON_H

#include "common.h"


typedef size_t cnt_t;
#define SPECF_CNT_T "%llu"


#define DEF_STATUS(name, msg) STATUS_##name,
enum Status
{
    #include "back_statuses.h"
};
#undef DEF_STATUS

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
    int curr_func_frame_size = 0;
    int in_while             = 0;
};

#endif /* BACKEND_COMMON_H */
