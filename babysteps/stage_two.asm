bits 16
[ORG 0x8000]
jmp main

main:
mov si, msg
call bios_print
bios_print:
  lodsb
  or al, al
  jz .done

  mov ah, 0x0e
  mov bh, 0
  int 0x10
  jmp bios_print
.done:
  ret

msg: db "[i] stage two let's fucking go", 0x0d, 0x0a, 0
