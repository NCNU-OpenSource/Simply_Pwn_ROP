# LSA2 Final Project README <br> 咻 ~ PWN 幾勒安餒金 ㄉㄨㄚˋ 蝦

## 相關連結 Link
- [報告投影片](https://hackmd.io/@qfqdw/BkqIEnvv2#/)
- [含解題的完整共筆](https://hackmd.io/suyvT3seQN24DwHgmZ-qOg?view)
- [README](https://hackmd.io/LmBm2bVwQ3CEKMnMAJtdjg?view)

## Setting
- 安裝 docker
```CMD=
sudo apt-get update -y
sudo apt-get install -y curl
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get install -y docker-ce
```
:::info
### 執行 Docker 前面不用加 sudo 的方法
- 創建 docker group: `sudo groupadd docker`
- 將 $USER(輸入自己的名子) 加入到 docker group 裡面: `sudo usermod -aG docker $USER`
- 啟動對 group 的更改: `newgrp docker`
:::
- 安裝 git: `sudo apt install git`
- clone 專案: `git clone https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP/`
- pwn1
    - 建立 pwn1_i images: `docker build -t pwn1_i .`
    - 開啟 pwn1_c container: `docker run -d -p $(主機 port):$(docker port) --name pwn1_c pwn1_i`
- pwn2
    - 建立 pwn2_i images: `docker build -t pwn2_i .`
    - 開啟 pwn2_c container: `docker run -d -p $(主機 port):$(docker port) --name pwn2_c pwn2_i`
- 在另一台電腦上: `nc $(ip) $(port>)`

## PWN Requirement
- python-pip3
- pwntools
- ROPgadget
- gdb
- objdump

## Simply_PWN 說明
- Just PWN it and take the flag
- Be patient to check the address
- format: `NCNU_LSA{FLAG}`
## Simply_PWN2 說明
- 與第一題差不多，但有些為的差異，你知道問題在哪嘛？
## Job Assignment
- `109213017 吳梓睿`
    - 負責 BOF 解說
    - 實際製作簡單題目及實作
- `109213068 李亞軒`
    - 環境架設、文件 
## Difficulty and Future Work
- 目前我們只針對 影響程式正常運作 作為攻擊方式，希望未來可以將 Shell Code 宮及實作完成
- 在練習上有發現編譯後的結果可能會跟我們所學的有點不同，畢竟在系統架構上相對比較不同，所以在學習上相對有難度
## Special Thanks
- @tommygood 緊急協助處理環境
- @我的蜜罐「密」我，說你在壞壞 跟我們換報告順序
