bits 16
[ORG 0x8000]

stage2_entry:
  mov si, msg_load_succ
  call bios_print

  ;; setup stack
  mov ax, 0
  mov ss, ax
  mov sp, 0x7c00

  call check_a20

  ;; we are now sure that a20 is turned on
  mov si, msg_a20_enable_succ
  call bios_print

  ;; protected mode let's fucking go
  cli
  lgdt [gdt_descriptor]

  mov eax, cr0
  or eax, 1
  mov cr0, eax

  jmp 0x08:stage3_entry

[bits 32]
stage3_entry:
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ;; print 'P'
  mov [0xb8000], byte 'P'
  mov [0xb8001], byte 0x0f
  jmp $

%include "bios_print.inc"
%include "a20.inc"
%include "gdt.inc"

msg_load_succ: db "[+] successfully loaded stage 2", 0x0d, 0x0a, 0
msg_a20_enable_succ: db "[+] A20 is now enabled", 0x0d, 0x0a, 0
