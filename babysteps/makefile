bin/boot.bin: boot.asm
	nasm -f bin boot.asm -o bin/boot.bin

bin/stage2.o: stage2.asm
	nasm -f elf32 stage2.asm -o bin/stage2.o

bin/kernel.o: kernel/kernel.c
	i686-elf-gcc -c kernel/kernel.c -o bin/kernel.o -ffreestanding -O2 -m32 -Wa,--32

bin/stage2.bin: bin/stage2.o bin/kernel.o
	ld -m elf_i386 -T kernel/linker.ld -o bin/stage2.bin bin/stage2.o bin/kernel.o --oformat binary

bin/image.bin: bin/boot.bin bin/stage2.bin
	cat bin/boot.bin bin/stage2.bin > bin/image.bin

run: bin/image.bin
	qemu-system-x86_64 -drive format=raw,file=bin/image.bin,index=0,if=floppy -monitor stdio

debug: bin/image.bin
	qemu-system-x86_64 -drive format=raw,file=bin/image.bin -s -S &
	gdb -q -x ~/dotfiles/gdb/x_og.cfg \
			-ex "target remote :1234" \
			-ex "break *0x7c00" \
			-ex "break *0x8000" \
			-ex "continue"

clean:
	rm -f bin/*
