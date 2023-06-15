# LSA2 Final Project 咻 ~ PWN 幾勒安餒金 ㄉㄨㄚˋ 蝦

[TOC]

## 主題名稱由來
<iframe width="784" height="577" src="https://www.youtube.com/embed/kJeh8wAzkQs" title="咻蹦一聲很大聲（廢片）" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## What is CTF
- Capture The Flag, CTF
    - 學習資訊安全攻擊與防禦的競賽
    1. Jeopardy
        - 尋找目標主機提供的資訊漏洞取得 Flag
        1. Crypto 密碼學
        2. Reverse 逆向工程
        3. Web 網頁
        4. Forensic 鑑識
        5. PWN
        6. Misc 其他 
    2. Attack & Defense
        - 一組一台提供多種服務的主機
        - 一邊找出自己的漏洞一邊維護，一邊攻擊其他隊伍
    3. King of Hill
        - 多台主機在線上，拿下主機控制權，換上自己的 Flag
- CTF 相關資源
    - [hackersir](https://ctf.hackersir.org/)
    - [ctftime](https://ctftime.org/)
    - [picoctf](https://picoctf.org/)
    - [Hitcon-Ctf](https://hacker.org.tw/zh/projects-Hitcon-Ctf.html)
    - [AIS3](https://ais3.org/)
        - [MyFirstCTF](https://ais3.org/mfctf)
    - [台灣資安 / CTF 學習資源整理](https://github.com/Ice1187/TW-Security-and-CTF-Resource)
### PWN
- (Binary Exploitation)
- 跟 Reverse 相似，參賽者也會拿到一個程式
- 目標在於攻擊執行在對方主機的程式
- 並取得對方的主機控制權
- 種類
    - Flow
        分析 ➔ 找尋漏洞 ➔ 撰寫攻擊程式
    - Vulnerability
        Buffer Overflow、Format String, …etc
    - Exploit
        利用程式漏洞獲得主機控制權 (get shell)
- 常用工具
    - IDA Pro：人稱反組譯的倚天劍
    - gdb：除錯工具


## Setting
## BOF Background Knowledge
### Program in Memory
- OS 將程式 map 到 memory
- **基本內容**
    - text
        - 程式內容
    - data
        - global 變數，寫死的變數 like: #define
    - heap
        - 動態配置的記憶體空間
    - stack
        - 區域變數、reurn address ...etc

- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/f829b66b-9a0f-4d61-acad-7ca564cd4299)

### Stack
- **LIFO (Last In First Out)**
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/b207622d-96e0-46fb-962a-ea70874f52f0)

### Function Call and Stack
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/b16bdd7b-25b7-4c7f-8283-06325d496824)
- Main function 為 Caller
- Func function 為 Callee
#### Some Register info
- ESP register : stack 頂端
- EBP register : stack 底端
- EIP register : CPU 下一個要執行的 address
#### stack frame
- 每一個 func 會給一塊 stack frame

#### Caller Part
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/25d99072-d569-4415-ba71-5620ab36f2da)
- push 參數進 stack
- 由後面的參數開始到前面
- 再 call 進去 Func
    - push ret addr
    - jmp Func
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/a1b40445-aff5-4801-98f4-8b1dd18ce7b9)

#### Callee Part
```clike=
void func(){
    char buf[12];
}
```

```
push ebp
mov ebp, esp
sub esp, 0xc
```

- push ebp
    - 存 main stack frame 起始位址
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/47dc720c-07ba-4007-83d5-3d1cc8dca7bc)

- mov ebp, esp
    - ebp = esp 設定換成 Func stack frame 底端起始位址
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/3e1a085e-d4d9-42d4-9ec8-90956984d22f)

- 切完 stack frame
- 執行 下一個 func 之前 ebp 存的是 main stack frame 的起點
- 所以必須要先記錄 main 的 addr ，這樣之後 ret 之後才能拿回來
- sub esp, 0xc
    - 切空間給 buf
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/c466fc01-7d88-4215-992d-b826065879e0)



#### Back to Main
```
mov esp, ebp
pop ebp
ret
```
- mov esp, ebp
    - 變成 Main Stack Frame 的頂端
    - ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/af976c01-842b-4852-80ec-91ce9ca7b112)
- pop ebp
    - 拿原本紀錄的 ebp 位址 (Main Stack Frame)
    - ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/3e2dbf9a-3b59-4244-b5b1-67b00aa71a05)



- ret (pop eip)
    - Stack 頂端 pop 出來到 eip



## BOF
- **Stack Overflow**
- Heap Overflow 
### Concept Review
- 使用了不安全的函式導致輸入超過界線
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/366f129c-d33c-4cd0-ab1a-973b0a07d0d6)

### Protect Technique
- **Some Protection on GCC Compiler and System**
#### Data Execution Prevention (DEP)
- No eXecute (NX)
- Shellcode on stack can't be executed

#### Address Space Layout Randomization (ASLR)
- Random 分配記憶體

#### Stack Guard (Stack Canary)
- ![image](https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/assets/77890790/f47e1d57-783b-4846-b3d0-7a3e5ca75752)
- Check the canary before function returns



## Protection of BOF (Stack)
- Data Execution Prevention (DEP)
    - Shellcode on data buffer can not be executed.
- Address Space Layout Randomization (ASLR)
    - 隨機記憶體位址
    - 增加 Exploit 的難度
- Stack Canary (Stack Guard)
    - 保護 overflow 的守衛
    - 在 function call 時將亂數放入 Stack 
    - ret 之前檢查亂數
 -->
