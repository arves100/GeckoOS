C:\devkitPro\devkitPPC\bin\powerpc-gekko-gcc.exe -nostartfiles -nodefaultlibs -Wl,-Ttext,0x80001800 -o codehandlerslota.elf codehandlerslota.s
C:\devkitPro\devkitPPC\bin\powerpc-gekko-strip.exe --strip-debug --strip-all --discard-all -o codehandlerslotas.elf -F elf32-powerpc codehandlerslota.elf
C:\devkitPro\devkitPPC\bin\powerpc-gekko-objcopy.exe -I elf32-powerpc -O binary codehandlerslotas.elf codehandlerslota.bin
raw2c codehandlerslota.bin
del *.elf
pause 