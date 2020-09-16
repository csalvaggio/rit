FROM fedora:31
MAINTAINER salvaggio@cis.rit.edu
ARG USER=1000
ARG GROUP=1000
RUN export uid=$USER && \
    export gid=$GROUP && \
    mkdir -p /home/developer && \
    echo "developer:x:${uid}:${gid}:Developer,,,:/home/developer:/bin/bash" >> \
         /etc/passwd && \
    echo "developer:x:${uid}:" >> /etc/group && \
    echo "developer ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/developer && \
    chmod 0440 /etc/sudoers.d/developer && \
    chown ${uid}:${gid} -R /home/developer && \
    dnf update -y && \
    dnf install -y \
      boost-devel \
      ccache \
      cmake \
      gcc-c++ \
      gdb \
      gnuplot \
      make \
      ninja-build \
      qt5-qtbase-devel \
      opencv-devel \
      vim-enhanced \
      eigen3-devel \
    && \
    strip -R .note.ABI-tag /lib64/libQt5Core.so
USER developer
ENV HOME /home/developer
COPY entrypoint.sh /
ENTRYPOINT ["/entrypoint.sh"]
