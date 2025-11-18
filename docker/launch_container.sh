# Xauthority 준비 (호스트에서 1회만 하면 됨)
XAUTH=/tmp/.docker.xauth
touch $XAUTH
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

docker run -it --rm \
    --hostname=$USER \
    --runtime=nvidia \
    --privileged $gpu\
    --network=host \
    -v "$PWD":/app -w /app \
    --name="sml_lecture" \
    -v /dev:/dev \
    -v /run/udev:/run/udev \
    -e LIBUVC_BACKEND=libusb \
    -e XAUTHORITY=$XAUTH \
    -e QT_X11_NO_MITSHM=1 \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.docker.xauth:/tmp/.docker.xauth:rw \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $(pwd)/ros2_ws:/root/ros2_ws \
    -v $(pwd)/common:/root/common \
    idim:v1

