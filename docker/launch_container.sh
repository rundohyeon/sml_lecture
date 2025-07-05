# Xauthority 준비 (호스트에서 1회만 하면 됨)
XAUTH=/tmp/.docker.xauth
touch $XAUTH
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

docker run -it --rm \
    --hostname=$USER \
    --runtime=nvidia \
    --privileged $gpu\
    --network=host \
    --name="sml_lecture" \
    -v /dev:/dev \
    -e XAUTHORITY=$XAUTH \
    -e QT_X11_NO_MITSHM=1 \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.docker.xauth:/tmp/.docker.xauth:rw \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
 -v $(pwd):/root/sml \
    idim:v1

