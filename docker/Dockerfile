FROM arm64v8/ros:humble-ros-base




RUN curl -fsSL https://packages.cloud.google.com/apt/doc/apt-key.gpg | \
        gpg --dearmor -o /usr/share/keyrings/coral-edgetpu-keyring.gpg && \
    echo "deb [signed-by=/usr/share/keyrings/coral-edgetpu-keyring.gpg] https://packages.cloud.google.com/apt coral-edgetpu-stable main" \
        > /etc/apt/sources.list.d/coral-edgetpu.list


ARG ROS_DISTRO='humble'

ENV DEBIAN_FRONTEND noninteractive
ENV DEBCONF_NOWARNINGS yes

# Conda 디렉토리를 삭제합니다.
RUN rm -rf /opt/conda

# [Install dependencies via apt]
RUN set -x
RUN apt-get update -y
RUN apt-get install -y
RUN apt-get update && apt-get install -y \
    software-properties-common \
    locales \
    gedit \
    bash-completion \
    gnupg \
    lsb-release \
    git \
    vim \
    v4l-utils \
    exfat-fuse \
    openssh-server \
    terminator \
    dbus-x11 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN locale-gen en_US en_US.UTF-8
RUN update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
RUN export LANG=en_US.UTF-8


# [Install realsense sdk 2.0]
RUN mkdir -p /etc/apt/keyrings
RUN curl -sSf https://librealsense.intel.com/Debian/librealsense.pgp | tee /etc/apt/keyrings/librealsense.pgp > /dev/null
RUN echo "deb [signed-by=/etc/apt/keyrings/librealsense.pgp] https://librealsense.intel.com/Debian/apt-repo `lsb_release -cs` main" | \
    tee /etc/apt/sources.list.d/librealsense.list
RUN apt-get update
RUN apt-get install -y -qq \
    librealsense2-utils \
    librealsense2-dev \
    librealsense2-dbg


# [Install Cmake]
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
    apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" && \
    apt update && \
    apt install -y -qq cmake


# [Install ROS2 Humble]
# RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg && \
#    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(lsb_release -cs) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null
# RUN apt update && \
#     apt upgrade -y && \
#     apt install -q -y \
#     build-essential \
#     libasio-dev \
#     libtinyxml2-dev \
#     python3-colcon-common-extensions \
#     python3-rosdep \
#     python3-vcstool \
#     python3-flake8-docstrings \
#     python3-pytest-cov \
#     ros-dev-tools \
#     ros-${ROS_DISTRO}-desktop \
#     ros-${ROS_DISTRO}-*-msgs \
#     ros-${ROS_DISTRO}-control* \
#     ros-${ROS_DISTRO}-usb-cam \
#     ros-${ROS_DISTRO}-realsense2-camera \
#     ros-${ROS_DISTRO}-realsense2-description \
#     ros-${ROS_DISTRO}-robot-localization \
#    ros-${ROS_DISTRO}-ur* \
#    ros-${ROS_DISTRO}-librealsense2* \
#    ros-${ROS_DISTRO}-diagnostic-updater \
#    ros-${ROS_DISTRO}-vision-msgs*


RUN apt update && \
    apt install -q -y \
    ros-${ROS_DISTRO}-ros2-control \
    ros-${ROS_DISTRO}-ros2-controllers \
    ros-${ROS_DISTRO}-tf2-tools \
    ros-${ROS_DISTRO}-rqt-tf-tree \
    ros-${ROS_DISTRO}-nav* \
    ros-${ROS_DISTRO}-slam-toolbox* \
    ros-${ROS_DISTRO}-tf* \
    ros-${ROS_DISTRO}-serial* \
    ros-${ROS_DISTRO}-asio-cmake-module




RUN python3 -m pip install -U \
    flake8-blind-except \
    flake8-builtins \
    flake8-class-newline \
    flake8-comprehensions \
    flake8-deprecated \
    flake8-import-order \
    flake8-quotes \
    "pytest>=5.3" \
    pytest-repeat \
    pytest-rerunfailures
RUN apt update && \
    apt install -q -y \
    libfmt-dev librange-v3-dev
RUN pip install -U pip && \
    pip install -U jinja2 typeguard

RUN pip install neuromeka
RUN pip install --upgrade neuromeka


RUN mkdir -p ~/ros2_ws/src && \
    cd ~/ros2_ws && \
    rosdep update && \
    # rosdep init && \
    rosdep install --from-paths src --ignore-src -y --skip-keys "fastcdr rti-connext-dds-6.0.1 urdfdom_headers" && \
    colcon build --symlink-install

RUN apt install -q -y \
    rospack-tools \
    python3-colcon-mixin
    
#RUN colcon mixin add default https://raw.githubusercontent.com/colcon/colcon-mixin-repository/master/index.yaml
RUN colcon mixin update default
RUN apt install python3-vcstool

RUN apt update
RUN apt install -q -y \
    ros-humble-xacro \
    ros-humble-moveit \
    ros-humble-moveit-servo \
    ros-humble-ros2-control \
    ros-humble-ros2-controllers \
    ros-humble-moveit-ros-move-group \
    ros-humble-moveit-planners-ompl \
    ros-humble-moveit-kinematics \
    ros-humble-controller-manager \
    ros-humble-joint-state-broadcaster \
    ros-humble-joint-state-publisher-gui \
    ros-humble-joint-trajectory-controller \
    ros-humble-moveit-ros-perception \
    ros-humble-rviz-visual-tools \
    ros-humble-moveit-visual-tools \
    ros-humble-moveit-resources

#
#    ros-humble-gazebo-ros \
#    ros-humble-gazebo-ros2-control \

RUN apt install -y ros-humble-rmw-cyclonedds-cpp


RUN echo 'source /root/ros2_ws/install/setup.bash' >> ~/.bashrc
RUN apt install -y net-tools


RUN /bin/bash -c "source /etc/bash.bashrc" && \
    rm /etc/apt/apt.conf.d/docker-clean && \
    apt update -y

WORKDIR /root/ros2_ws/src

RUN apt update

RUN apt install -y python-is-python3
RUN pip install squaternion
RUN pip install transforms3d


RUN echo 'export PS1="\[\e[0;33m\]idim \W \$ \[\e[0m\]"' >> /root/.bashrc
RUN echo 'export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp'
# RUN apt update && apt install -y ros-humble-turtlesim

ENTRYPOINT ["/bin/bash"]
