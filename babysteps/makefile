boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

run: boot.bin
	qemu-system-i386 -cpu 486 -drive format=raw,file=boot.bin

debug: boot.bin
	qemu-system-x86_64 -drive format=raw,file=boot.bin -s -S &
	gdb -q -x ~/dotfiles/gdb/x_og.cfg \
			-ex "target remote :1234" \
			-ex "break *0x7c00" \
			-ex "continue"
