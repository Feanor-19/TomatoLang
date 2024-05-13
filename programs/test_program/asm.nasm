default rel
section .text
global _start
_start:
; main prologue start
			mov rbp , rsp 
			sub rsp , 16 
; main prologue end
; assign_start
; assign_expr
; input start
extern input
			call input
; push from xmm0, in which func result is located
			sub rsp , 8 
			movsd QWORD [rsp + 0] , xmm0 
; input end
			pop QWORD [rbp + -8] 
; assign_end
; main epilogue start
extern _exit
			call _exit
; main epilogue end
