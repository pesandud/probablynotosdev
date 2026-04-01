boot.bin: boot.asm
	nasm -f bin boot.asm -o bin/boot.bin

stage_2.bin: stage_2.asm
	nasm -f bin stage_2.asm -o bin/stage_2.bin

run: image.bin
	qemu-system-x86_64 -drive format=raw,file=bin/image.bin,index=0,if=floppy

image.bin: boot.bin stage_2.bin
	cat bin/boot.bin bin/stage_2.bin > bin/image.bin

debug: boot.bin stage_2.bin
	qemu-system-x86_64 -drive format=raw,file=bin/image.bin -s -S &
	gdb -q -x ~/dotfiles/gdb/x_og.cfg \
			-ex "target remote :1234" \
			-ex "break *0x7c00" \
			-ex "continue"

clean:
	rm -f bin/*
