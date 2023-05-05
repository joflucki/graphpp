############################################
##              Base install              ##
############################################
FROM ubuntu:22.04
ENTRYPOINT ["tail", "-f", "/dev/null"]

# Add universe repository
RUN apt update
RUN apt install -y software-properties-common
RUN add-apt-repository universe
RUN apt update


############################################
##                 Ninja                  ##
############################################
# Install Doxygen
RUN apt install -y ninja-build


############################################
##                Doxygen                 ##
############################################
# Install Doxygen
RUN apt install -y doxygen


############################################
##                   Qt                   ##
############################################
# Install Qt dependencies
RUN apt install -y \
    build-essential \
    libgl1-mesa-dev \
    libfontconfig1-dev \
    libfreetype6-dev \
    libx11-dev \
    libx11-xcb-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrender-dev \
    libxcb1-dev \
    libxcb-cursor-dev \
    libxcb-glx0-dev \
    libxcb-keysyms1-dev \
    libxcb-image0-dev \
    libxcb-shm0-dev \
    libxcb-icccm4-dev \
    libxcb-sync-dev \
    libxcb-xfixes0-dev \
    libxcb-shape0-dev \
    libxcb-randr0-dev \
    libxcb-render-util0-dev \
    libxcb-util-dev \
    libxcb-xinerama0-dev \
    libxcb-xkb-dev \
    libxkbcommon-dev \
    libxkbcommon-x11-dev

# Install Qt package
RUN apt install -y \
    qt6-base-dev

RUN qtchooser -install qt6 $(which qmake6)
RUN mv /usr/lib/x86_64-linux-gnu/qt6/qt6.conf /usr/share/qtchooser/
RUN mkdir -p /usr/lib/$(uname -p)-linux-gnu/qt-default/qtchooser
RUN ln -n /usr/share/qtchooser/qt6.conf /usr/lib/$(uname -p)-linux-gnu/qt-default/qtchooser/default.conf
RUN export QT_SELECT=qt6