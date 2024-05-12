default rel

section .text

global _exit
_exit:
            mov rax, 0x3C
            xor rdi, rdi
            syscall

global _mywrite
; void _mywrite(long unsigned str_len, const char *str_ptr)
; rdi - str_len
; rsi - str_ptr
_mywrite:
            push rdi ; str_len

            mov rax, 1 ; syscall num
            mov rdi, 1 ; stdout
            ; rsi already in place
            pop rdx
            syscall

            ret

