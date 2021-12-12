FROM ubuntu:18.04
ARG USER=user
ARG UID=1000
ARG GID=1000
# You can change your apt mirror if necessary.
# RUN sed -i 's/http:\/\/.*.ubuntu.com/http:\/\/mirror.sjtu.edu.cn/g' /etc/apt/sources.list
RUN apt-get update
RUN apt-get -y install wget curl unzip p7zip gcc-7-multilib g++-7-multilib gcc-4.8-multilib g++-4.8-multilib
RUN groupadd -g $GID -o $USER
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $USER

RUN apt-get -y install git make dpkg-dev libreadline-dev ccache
USER $USER
RUN bash -c "bash <(curl -fsSL https://xmake.io/shget.text)"
