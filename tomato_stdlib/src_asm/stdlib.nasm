default rel

section .text

global _exit
_exit:
            mov rax, 0x3C
            xor rdi, rdi
            syscall

global _write
_write:
            
            mov rax, 1
