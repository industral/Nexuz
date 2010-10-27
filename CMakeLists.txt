cmake_minimum_required(VERSION 2.6)

PROJECT (Nexuz)

SET(SourcePath src)

SET(Nexuz_src

    ${SourcePath}/Client/Media/SoundSystem/AbstractDSP.hpp
    ${SourcePath}/Client/Media/SoundSystem/ALSA/DSP/DSP.cpp
    ${SourcePath}/Client/Media/SoundSystem/ALSA/Mic/mic.cpp
    
    ${SourcePath}/Client/Media/SoundSystem/ALSA/Capture/Capture.cpp

    #${SourcePath}/Client/Media/Video/v4l2/camera.cpp

    #${SourcePath}/Client/Network/client.cpp
)

SET(SilentMedia_LINKED_LIBRARY
    asound
)

INCLUDE_DIRECTORIES(
    /usr/include
    /usr/local/include
    /usr/include/c++/4.4
    ${SilentMedia_SOURCE_DIR}/src
    ${SilentMedia_SOURCE_DIR}/${SourcePath}
)


ADD_EXECUTABLE (bin/client ${SourcePath}/Client/main.cpp)
TARGET_LINK_LIBRARIES (bin/client ${SilentMedia_LINKED_LIBRARY})
