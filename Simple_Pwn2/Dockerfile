FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y gcc-multilib
RUN apt-get install -y ncat

RUN useradd -m ctf

# ENV HOME /home/ctf

WORKDIR /home/ctf

RUN git clone https://github.com/wzray07/1112_LSA-Simply_Pwn_ROP

USER ctf

WORKDIR /home/ctf/1112_LSA-Simply_Pwn_ROP/Simple_Pwn2

CMD ["ncat", "-vc", "./pwn", "-kl", "0.0.0.0", "8787"]

EXPOSE 8787
