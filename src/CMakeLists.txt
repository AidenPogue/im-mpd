project(IM-MPD)

target_sources(im-mpd
    PUBLIC 
        main.cpp
        MpdClientWrapper.cpp
)

add_subdirectory(panels)