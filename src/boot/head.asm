; declare constants for the MULTIBOOT HEADER
;
;	RAZZLE FREE OPEN SOURCE OPERATING SYSTEM HEADER
;
;
;					LICENSE GPL
;
;				COPYRIGHT JAD 2025 - 2026 (c) Jad
;
;					a multiboot header
;				For Razzle Operating system
;
;


; here, we declare constants

%define ALIGN     1<<0             ; align loaded shit
%define MEMINFO   1<<1             ; provide memory map
%define FLAGS     ALIGN | MEMINFO  ; this is the Multiboot 'flag' fucker
%define MAGIC     0x1BADB002       ; 'magic number' lets bootloader find the header
%define CHECKSUM  -(MAGIC + FLAGS) ; checksum to prove to grub, now shut up nasm!

;
; DECLARE A MULTIBOOT HEADER, that marks the program as a kernel
; this is required for GRUB BOOTLOADER to see the Operating System!
;
;	The bootloader will search for this signature as seen on top in the first 8KB of
;	the kernel file!
;
;
; nasm is annoying, at least i did not use i686-elf-as!
;	anyway:

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

;
;
; The stupid multiboot standard do not define the value of the stack pointer register
; (ESP) and it the kernel job to provide a stack!
;

section .bss
align 16
stack_bottom:
	resb 16384			; 16384 Bytes (16 KiB)
stack_top:

;
; NOW the linker script in src/required/linker.ld will specifies _start as the entry
; of the kernel! and the bootloader will jump to this bullshit!
; and thanks god This shit wor-

; ignore my last words, i had been debugging for 54mins

section .text
global _start
_start:
	; the bootloader load this garbage kernel into 32bit protected mode
	; and that give us a fucking big improvement

	;anyway
	move esp, stack_top

; To set up a stack, we set the esp register to point to the top of the stack
; (as it grows downwards on x86 systems). This is necessarily done in assembly
; as languages such as C cannot function without a stack.


    mov esp, stack_top


	; call kernel MAIN

	call kernel_main
;
; if the system have nothing to do, we should put the computer into a infinite loop
; because it will fuck itself without that loop

cli
1:
	hlt
	jmp 1b

.size _start, . - _start