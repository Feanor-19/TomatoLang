default rel
section .text
global Discriminant
Discriminant:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 40 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
			movsd QWORD [rbp + -16] , xmm1 
			movsd QWORD [rbp + -24] , xmm2 
; func prologue end
; assign_start
; assign_expr
section .rodata
LNC_0 	dq 0.000000
section .text
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -32] , r8 
; assign_end
; assign_start
; assign_expr
; sub start
; computing left expr
; mul start
; computing left expr
			push QWORD [rbp + -16] 
; computing right expr
			push QWORD [rbp + -16] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
; computing right expr
; mul start
; computing left expr
; mul start
; computing left expr
section .rodata
LNC_1 	dq 4.000000
section .text
			push QWORD [LNC_1] 
; computing right expr
			push QWORD [rbp + -8] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
; computing right expr
			push QWORD [rbp + -24] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			subsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sub end
			pop QWORD [rbp + -32] 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -32] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; return start
			leave
			ret
; return end
global LinearRoot
LinearRoot:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 32 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
			movsd QWORD [rbp + -16] , xmm1 
; func prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -24] , r8 
; assign_end
; assign_start
; assign_expr
; div start
; computing left expr
; minus start, computing sub-expr:
			push QWORD [rbp + -16] 
; pop result to reg_xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
; mulsd reg_xmm_tmp_1, [num_const_which_is_minus_one]
; the mentioned const:
section .rodata
LNC_2 	dq -1.000000
section .text
; the mentioned mulsd:
			mulsd xmm8 , QWORD [LNC_2] 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sqrt end
; computing right expr
			push QWORD [rbp + -8] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			divsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; div end
			pop QWORD [rbp + -24] 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -24] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; return start
			leave
			ret
; return end
global SolvationOfLinear
SolvationOfLinear:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 40 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
			movsd QWORD [rbp + -16] , xmm1 
; func prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -24] , r8 
; assign_end
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -8] 
; computing right expr
			push QWORD [rbp + -24] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_0
; else branch:
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -32] , r8 
; assign_end
; assign_start
; assign_expr
; call func recipe start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -16] 
; another arg expression:
			push QWORD [rbp + -8] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm1 , QWORD [rsp + 0] 
			add rsp , 8 
			call LinearRoot
; pushing result of the func on stack:
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; call func recipe end
			pop QWORD [rbp + -32] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_0 	db "Here is the only linear root:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_0 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -32] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; jump if_end:
			jmp LCC_1
; label if_yes:
LCC_0:
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -16] 
; computing right expr
			push QWORD [rbp + -24] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_2
; else branch:
; print_str start
extern print_str
section .rodata
LSC_1 	db "Quite interesting, that's also not a linear equation.", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_1 
			call print_str
; print_str start
extern print_str
section .rodata
LSC_2 	db "It's not an equation at all: there are simply no roots, even imaginary ones!", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_2 
			call print_str
; jump if_end:
			jmp LCC_3
; label if_yes:
LCC_2:
; print_str start
extern print_str
section .rodata
LSC_3 	db "Well, there is kinda the whole infinity and a small carriage of roots...", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_3 
			call print_str
; label if_end:
LCC_3:
; label if_end:
LCC_1:
; return start
			leave
			ret
; return end
global QuadraticFirstRoot
QuadraticFirstRoot:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 48 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
			movsd QWORD [rbp + -16] , xmm1 
			movsd QWORD [rbp + -24] , xmm2 
; func prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -32] , r8 
; assign_end
; assign_start
; assign_expr
; div start
; computing left expr
; add start
; computing left expr
; minus start, computing sub-expr:
			push QWORD [rbp + -16] 
; pop result to reg_xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
; mulsd reg_xmm_tmp_1, [num_const_which_is_minus_one]
; the mentioned const:
section .rodata
LNC_3 	dq -1.000000
section .text
; the mentioned mulsd:
			mulsd xmm8 , QWORD [LNC_3] 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sqrt end
; computing right expr
; sqrt start, computing sub-expr:
			push QWORD [rbp + -24] 
; pop result to reg_xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			sqrtsd xmm8 , xmm8 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sqrt end
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			addsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; add end
; computing right expr
; mul start
; computing left expr
section .rodata
LNC_4 	dq 2.000000
section .text
			push QWORD [LNC_4] 
; computing right expr
			push QWORD [rbp + -8] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			divsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; div end
			pop QWORD [rbp + -32] 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -32] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; return start
			leave
			ret
; return end
global QuadraticNumberOfRoots
QuadraticNumberOfRoots:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 40 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
; func prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -16] , r8 
; assign_end
; assign_start
; assign_expr
section .rodata
LNC_5 	dq 1.000000
section .text
			mov r8 , QWORD [LNC_5] 
			mov QWORD [rbp + -24] , r8 
; assign_end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -32] , r8 
; assign_end
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -8] 
; computing right expr
			push QWORD [rbp + -32] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			ja LCC_4
; jump if_end:
			jmp LCC_5
; label if_yes:
LCC_4:
; assign_start
; assign_expr
; mul start
; computing left expr
			push QWORD [LNC_4] 
; computing right expr
			push QWORD [rbp + -24] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
			pop QWORD [rbp + -16] 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -16] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; label if_end:
LCC_5:
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -8] 
; computing right expr
			push QWORD [rbp + -32] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_6
; jump if_end:
			jmp LCC_7
; label if_yes:
LCC_6:
; assign_start
; assign_expr
; mul start
; computing left expr
			push QWORD [LNC_5] 
; computing right expr
			push QWORD [rbp + -24] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
			pop QWORD [rbp + -16] 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -16] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; label if_end:
LCC_7:
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -8] 
; computing right expr
			push QWORD [rbp + -32] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			jb LCC_8
; jump if_end:
			jmp LCC_9
; label if_yes:
LCC_8:
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -16] , r8 
; assign_end
; return start
; computing the expression to return:
			push QWORD [rbp + -16] 
; pop the result into xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			leave
			ret
; return end
; label if_end:
LCC_9:
; return start
			leave
			ret
; return end
global SolvationOfQuadratic
SolvationOfQuadratic:
; func prologue start
			push rbp 
			mov rbp , rsp 
			sub rsp , 80 
; Laying out func args into stack:
			movsd QWORD [rbp + -8] , xmm0 
			movsd QWORD [rbp + -16] , xmm1 
			movsd QWORD [rbp + -24] , xmm2 
; func prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -32] , r8 
; assign_end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_5] 
			mov QWORD [rbp + -40] , r8 
; assign_end
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -8] 
; computing right expr
			push QWORD [rbp + -32] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_10
; else branch:
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -48] , r8 
; assign_end
; assign_start
; assign_expr
; call func recipe start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -24] 
; another arg expression:
			push QWORD [rbp + -16] 
; another arg expression:
			push QWORD [rbp + -8] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm1 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm2 , QWORD [rsp + 0] 
			add rsp , 8 
			call Discriminant
; pushing result of the func on stack:
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; call func recipe end
			pop QWORD [rbp + -48] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_4 	db "Here is the discriminant of your equation:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_4 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -48] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -56] , r8 
; assign_end
; assign_start
; assign_expr
; call func recipe start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -48] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call QuadraticNumberOfRoots
; pushing result of the func on stack:
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; call func recipe end
			pop QWORD [rbp + -56] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_5 	db "The number of roots is:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_5 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -56] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -56] 
; computing right expr
			push QWORD [rbp + -32] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_11
; else branch:
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -64] , r8 
; assign_end
; assign_start
; assign_expr
; call func recipe start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -48] 
; another arg expression:
			push QWORD [rbp + -16] 
; another arg expression:
			push QWORD [rbp + -8] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm1 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm2 , QWORD [rsp + 0] 
			add rsp , 8 
			call QuadraticFirstRoot
; pushing result of the func on stack:
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; call func recipe end
			pop QWORD [rbp + -64] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_6 	db "Aaaand here is the first root:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_6 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -64] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; if_start
; cmp helper start
; computing left expr
			push QWORD [rbp + -56] 
; computing right expr
; mul start
; computing left expr
			push QWORD [LNC_4] 
; computing right expr
			push QWORD [rbp + -40] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jump if_yes
			je LCC_12
; jump if_end:
			jmp LCC_13
; label if_yes:
LCC_12:
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -72] , r8 
; assign_end
; assign_start
; assign_expr
; sub start
; computing left expr
; div start
; computing left expr
; minus start, computing sub-expr:
			push QWORD [rbp + -16] 
; pop result to reg_xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
; mulsd reg_xmm_tmp_1, [num_const_which_is_minus_one]
; the mentioned const:
section .rodata
LNC_6 	dq -1.000000
section .text
; the mentioned mulsd:
			mulsd xmm8 , QWORD [LNC_6] 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sqrt end
; computing right expr
			push QWORD [rbp + -8] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			divsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; div end
; computing right expr
			push QWORD [rbp + -64] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			subsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; sub end
			pop QWORD [rbp + -72] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_7 	db "And the second root is:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_7 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -72] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; label if_end:
LCC_13:
; jump if_end:
			jmp LCC_14
; label if_yes:
LCC_11:
; print_str start
extern print_str
section .rodata
LSC_8 	db "No real roots!", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_8 
			call print_str
; label if_end:
LCC_14:
; jump if_end:
			jmp LCC_15
; label if_yes:
LCC_10:
; print_str start
extern print_str
section .rodata
LSC_9 	db "Well, that's not quite a quadratic equation, ", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_9 
			call print_str
; print_str start
extern print_str
section .rodata
LSC_10 	db "smells more like a linear one. Anyway...", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_10 
			call print_str
; call func action start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -24] 
; another arg expression:
			push QWORD [rbp + -16] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm1 , QWORD [rsp + 0] 
			add rsp , 8 
			call SolvationOfLinear
; call func action end
; label if_end:
LCC_15:
; return start
			leave
			ret
; return end
global _start
_start:
; main prologue start
			mov rbp , rsp 
			sub rsp , 56 
; main prologue end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_5] 
			mov QWORD [rbp + -8] , r8 
; assign_end
; assign_start
; assign_expr
			mov r8 , QWORD [LNC_0] 
			mov QWORD [rbp + -16] , r8 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_11 	db "Hi, I can solve quadratic equations, like ax^2 + bx + c = 0!", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_11 
			call print_str
; print_str start
extern print_str
section .rodata
LSC_12 	db "Do you want to make a try? [1/0]", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_12 
			call print_str
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
			pop QWORD [rbp + -24] 
; assign_end
; label while_start:
LCC_18:
; cmp helper start
; computing left expr
			push QWORD [rbp + -24] 
; computing right expr
			push QWORD [rbp + -16] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			comisd xmm8 , xmm9 
; cmp helper end
; jmp while_body
			jne LCC_16
; jmp while_end
			jmp LCC_17
; label while_body:
LCC_16:
; while body:
; print_str start
extern print_str
section .rodata
LSC_13 	db "Please, enter coefficient a:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_13 
			call print_str
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
			pop QWORD [rbp + -32] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_14 	db "Please, enter coefficient b:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_14 
			call print_str
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
			pop QWORD [rbp + -40] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_15 	db "Please, enter coefficient c:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_15 
			call print_str
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
			pop QWORD [rbp + -48] 
; assign_end
; print_str start
extern print_str
section .rodata
LSC_16 	db "Here are the entered coefficients:", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_16 
			call print_str
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -32] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -40] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; print num start
extern print_num
; compute the argument:
			push QWORD [rbp + -48] 
; pop to xmm0
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
			call print_num
; call func action start
; computing on sub-stack all args (in reverse order):
; another arg expression:
			push QWORD [rbp + -48] 
; another arg expression:
			push QWORD [rbp + -40] 
; another arg expression:
			push QWORD [rbp + -32] 
; pop result into arg:
			movsd xmm0 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm1 , QWORD [rsp + 0] 
			add rsp , 8 
; pop result into arg:
			movsd xmm2 , QWORD [rsp + 0] 
			add rsp , 8 
			call SolvationOfQuadratic
; call func action end
; print_str start
extern print_str
section .rodata
LSC_17 	db "Done! Do you want to solve another equation? [1/0]", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_17 
			call print_str
; assign_start
; assign_expr
; mul start
; computing left expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
; computing right expr
			push QWORD [rbp + -8] 
; pop right expr result to xmm_tmp_2
			movsd xmm9 , QWORD [rsp + 0] 
			add rsp , 8 
; pop left expr result to xmm_tmp_1
			movsd xmm8 , QWORD [rsp + 0] 
			add rsp , 8 
			mulsd xmm8 , xmm9 
; push back onto comp. sub-stack
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm8 
; mul end
			pop QWORD [rbp + -24] 
; assign_end
; jmp while_start
			jmp LCC_18
; label while_end:
LCC_17:
; print_str start
extern print_str
section .rodata
LSC_18 	db "Goodbye!", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_18 
			call print_str
; main epilogue start
extern _exit
			call _exit
; main epilogue end
