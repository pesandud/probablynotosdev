boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

stage_two.bin: stage_two.asm
	nasm -f bin stage_two.asm -o stage_two.bin

run: image.bin
	qemu-system-x86_64 -drive format=raw,file=image.bin,index=0,if=floppy

image.bin: boot.bin stage_two.bin
	cat boot.bin stage_two.bin > image.bin

debug: boot.bin stage_two.bin
	qemu-system-x86_64 -drive format=raw,file=image.bin -s -S &
	gdb -q -x ~/dotfiles/gdb/x_og.cfg \
			-ex "target remote :1234" \
			-ex "break *0x7c00" \
			-ex "continue"
