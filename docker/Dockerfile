FROM arm64v8/ros:humble-ros-base

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Seoul

RUN echo 'export PS1="\[\e[0;33m\]idim \W \$ \[\e[0m\]"' >> /root/.bashrc

RUN apt update && apt install -y \
    locales curl gnupg2 lsb-release sudo wget \
    build-essential git cmake unzip vim \
    x11-xserver-utils libx11-dev \
    && locale-gen en_US en_US.UTF-8 \
    && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 \
    && export LANG=en_US.UTF-8


RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

RUN apt update && apt install -y \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtchooser \
    libqt5gui5 \
    libqt5widgets5 \
    libqt5core5a \
    libxcb1 \
    libx11-xcb1 \
    libxcb-render0 \
    libxcb-shape0 \
    libxcb-xfixes0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-xinerama0 \
    libxcb-util1 \
    libxcb-xkb1 \
    libxrender1 \
    libgl1-mesa-glx \
    libxext6 \
    libxkbcommon-x11-0

ENV QT_QPA_PLATFORM=xcb

RUN apt update && apt install -y ros-humble-turtlesim

