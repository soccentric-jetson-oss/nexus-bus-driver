savedcmd_nexus-bus.o := ld -m elf_x86_64 -z noexecstack --no-warn-rwx-segments   -r -o nexus-bus.o @nexus-bus.mod  ; /usr/src/linux-headers-7.0.0-28-generic/tools/objtool/objtool --hacks=jump_label --hacks=noinstr --hacks=skylake --retpoline --rethunk --sls --stackval --static-call --uaccess --prefix=16  --link  --module nexus-bus.o

nexus-bus.o: $(wildcard /usr/src/linux-headers-7.0.0-28-generic/tools/objtool/objtool)
