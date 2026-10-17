; boot.asm - Multiboot загрузчик для Notepad OS
; Компилируется NASM в 32-битный ELF

MAGIC    equ 0x1BADB002
FLAGS    equ 0x0
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384      ; 16 KB стек
stack_top:

section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top   ; настроить стек
    push ebx             ; указатель на Multiboot info
    push eax             ; магическое число Multiboot
    call kernel_main     ; вызвать C-функцию

.hang:
    cli
    hlt
    jmp .hang
