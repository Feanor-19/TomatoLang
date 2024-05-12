default rel
section .text
global Factorial
Factorial:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 24 
; func prologue end
; assign_start
; assign_expr
section .rodata
LNC_0 	dq 1
section .text
			push [LNC_0] 
			pop [rbp + -16] 
; assign_end
; if_start
; cmp helper start
; computing left expr
			push [rbp + -8] 
; pop result to xmm_tmp_1
			pop xmm8 
; computing right expr
			push [rbp + -16] 
; pop result to xmm_tmp_2
			pop xmm9 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_0
; jump if_end:
			jmp LCC_1
; label if_yes:
LCC_0:
; return start
; computing the expression to return:
			push [rbp + -16] 
; pop the result into xmm0
			pop xmm0 
			leave
			ret
; return end
; label if_end:
LCC_1:
; return start
; computing the expression to return:
; mul start
; computing left expr
			push [rbp + -8] 
; pop result to xmm_tmp_1
			pop xmm8 
; computing right expr
; call func recipe start
; moving args into regs:
; computing arg expr:
; sub start
; computing left expr
			push [rbp + -8] 
; pop result to xmm_tmp_1
			pop xmm8 
; computing right expr
			push [rbp + -16] 
; pop result to xmm_tmp_2
			pop xmm9 
			subsd xmm8 , xmm9 
; push back onto comp. sub-stack
			push xmm8 
; sub end
; pop result into arg:
			pop xmm0 
			call Factorial
; pushing result of the func on stack:
			push xmm0 
; call func recipe end
; pop result to xmm_tmp_2
			pop xmm9 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			push xmm8 
; mul end
; pop the result into xmm0
			pop xmm0 
			leave
			ret
; return end
; return start
			leave
			ret
; return end
global _start
_start:
; main prologue start
			mov rbp , rsp 
			sub rsp , 24 
; main prologue end
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			push xmm0 
; input end
			pop [rbp + -8] 
; assign_end
; assign_start
; assign_expr
section .rodata
LNC_1 	dq 0
section .text
			push [LNC_1] 
			pop [rbp + -16] 
; assign_end
; assign_start
; assign_expr
; call func recipe start
; moving args into regs:
; computing arg expr:
			push [rbp + -8] 
; pop result into arg:
			pop xmm0 
			call Factorial
; pushing result of the func on stack:
			push xmm0 
; call func recipe end
			pop [rbp + -16] 
; assign_end
; print num start
extern print_num
; compute the argument:
			push [rbp + -16] 
; pop to xmm0
			pop xmm0 
			call print_num
; main epilogue start
			call _exit
; main epilogue end
