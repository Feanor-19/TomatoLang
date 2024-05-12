default rel
section .text
global _start
_start:
; main prologue start
			mov rbp , rsp 
			sub rsp , 8 
; main prologue end
; print_str start
extern print_str
section .rodata
LSC_0 	db "Well, that's not quite a quadratic equation!", 0x0a, 0x0
section .text
; mov *first common reg used to pass params*, str_ptr
			mov rdi , LSC_0 
			call print_str
; main epilogue start
extern _exit
			call _exit
; main epilogue end
