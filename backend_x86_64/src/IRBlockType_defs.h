DEF_IRBLOCK_TYPE(DUMMY) // e.g. for comments or unnamed labels, which aren't at any instructions
DEF_IRBLOCK_TYPE(EXTERN_KW) // represents line in asm 'extern func_name'.
DEF_IRBLOCK_TYPE(GLOBAL_KW) // represents line in asm 'global func_name'.

DEF_IRBLOCK_TYPE(LBL_FUNC_NAME) // represents 'func_name:'

DEF_IRBLOCK_TYPE(NUM_CONST) // const of type num_t (label with DQ in .rodata).
DEF_IRBLOCK_TYPE(STR_CONST) // string const (label with DB in .rodata).

DEF_IRBLOCK_TYPE(PUSH) // Imagining it is universal (including XMM and 'mem to mem')
DEF_IRBLOCK_TYPE(POP) // Imagining it is universal (including XMM and 'mem to mem')
DEF_IRBLOCK_TYPE(MOV)

DEF_IRBLOCK_TYPE(ADD)
DEF_IRBLOCK_TYPE(SUB)

DEF_IRBLOCK_TYPE(ADDSD)
DEF_IRBLOCK_TYPE(SUBSD)
DEF_IRBLOCK_TYPE(MULSD)
DEF_IRBLOCK_TYPE(DIVSD)

DEF_IRBLOCK_TYPE(COMISD)

DEF_IRBLOCK_TYPE(JMP)
DEF_IRBLOCK_TYPE(JE)
DEF_IRBLOCK_TYPE(JNE)
DEF_IRBLOCK_TYPE(JA)
DEF_IRBLOCK_TYPE(JAE)
DEF_IRBLOCK_TYPE(JB)
DEF_IRBLOCK_TYPE(JBE)

DEF_IRBLOCK_TYPE(CALL)
DEF_IRBLOCK_TYPE(LEAVE)
DEF_IRBLOCK_TYPE(RET)

DEF_IRBLOCK_TYPE(SQRTSD)