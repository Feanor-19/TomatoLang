#ifndef TR_IR_TO_NASM_FUNCS_H
#define TR_IR_TO_NASM_FUNCS_H

#include "back_common.h"
#include "IR_interface.h"

#define FORMAL_TR_IR_NASM_ARGS const IRBlock* block, FILE *stream 

#define DEF_IRBLOCK_TYPE(name__) Status tr_IR_to_NASM_##name__ (FORMAL_TR_IR_NASM_ARGS);
#include "IRBlockType_defs.h"
#undef DEF_IRBLOCK_TYPE

#define PRINT( format__, ... ) do{fprintf(stream, format__, ##__VA_ARGS__); putc('\n', stream);}while(0)

#define PRINT_INSTR( format__, ... ) PRINT( "\t\t\t"##format__, ##__VA_ARGS__ )

#endif /* TR_IR_TO_NASM_FUNCS_H */