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

global _myread
; void _myread(long unsigned cnt, char *buf)
; rdi - cnt
; rsi - buf
_myread:
            push rdi ; cnt

            xor rax, rax ; syscall num
            mov rdi, 0 ; stdin
            ; rsi already in place
            pop rdx
            syscall

            ret

global print_int
; void print_int(long unsigned x)
; rdi - x
print_int:
            push rbp
            mov rbp, rsp
            sub rsp, 8

            push r12
            push rbx

            xor rdx, rdx
            mov rax, rdi
            mov rbx, 10 ; because div doesn't support immc
            xor rcx, rcx

loop_fw:    div rbx
            push rdx
            inc rcx
            xor rdx, rdx
            cmp rax, 0
            jne loop_fw

loop_bw:    pop rsi
            add rsi, '0'
            mov [rbp-8], rsi
            mov r12, rcx    ; saving
            
            mov rax, 1 ; syscall num
            mov rdi, 1 ; stdout
            lea rsi, [rbp - 8]
            mov rdx, 1
            syscall

            mov rcx, r12
            loop loop_bw

            pop rbx
            pop r12

            leave
            ret
