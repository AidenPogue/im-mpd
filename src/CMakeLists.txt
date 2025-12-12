project(IM-MPD)

target_sources(im-mpd
    PUBLIC 
        main.cpp
        MpdClientWrapper.cpp
        Utils.cpp
        stb_image.cpp
)

add_subdirectory(panels)
add_subdirectory(TitleFormatting)