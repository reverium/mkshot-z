##  General Sources / Includes ##
set(MKSHOT_INCDIRS
    "${CMAKE_SOURCE_DIR}/deps"
    "${CMAKE_SOURCE_DIR}/embed/include"
    "${CMAKE_SOURCE_DIR}/src"
)

set(MKSHOT_SOURCES
    main.cpp

    oneshot/bind/bind-journal.cpp
    oneshot/bind/bind-niko.cpp
    oneshot/bind/bind-oneshot.cpp
    oneshot/bind/bind-wallpaper.cpp

    oneshot/i18n.cpp
    oneshot/journal.cpp
    oneshot/oneshot.cpp
    oneshot/wallpaper.cpp

    core/audio/al-stream.cpp
    core/audio/audio.cpp
    core/audio/sdl-sound-source.cpp
    core/audio/sound-emitter.cpp
    core/audio/stream.cpp
    core/audio/vorbis-source.cpp

    core/bind/bind.cpp
    core/bind/bind-rgss.cpp
    core/bind/bind-audio.cpp
    core/bind/bind-bitmap.cpp
    core/bind/bind-etc.cpp
    core/bind/bind-font.cpp
    core/bind/bind-fs.cpp
    core/bind/bind-gfx.cpp
    core/bind/bind-input.cpp
    core/bind/bind-plane.cpp
    core/bind/bind-sprite.cpp
    core/bind/bind-table.cpp
    core/bind/bind-tilemap-vx.cpp
    core/bind/bind-tilemap.cpp
    core/bind/bind-util.cpp
    core/bind/bind-viewport.cpp
    core/bind/bind-window-vx.cpp
    core/bind/bind-window.cpp

    core/fs/fs.cpp

    core/gfx/gl/debug.cpp
    core/gfx/gl/fun.cpp
    core/gfx/gl/meta.cpp
    core/gfx/gl/scene.cpp
    core/gfx/gl/shader.cpp
    core/gfx/gl/state.cpp
    core/gfx/gl/texpool.cpp
    core/gfx/gl/tileatlas-vx.cpp
    core/gfx/gl/tileatlas.cpp
    core/gfx/gl/tilequad.cpp
    core/gfx/gl/vertex.cpp

    core/gfx/autotiles-vx.cpp
    core/gfx/autotiles.cpp
    core/gfx/bitmap.cpp
    core/gfx/etc.cpp
    core/gfx/font.cpp
    core/gfx/gfx.cpp
    core/gfx/plane.cpp
    core/gfx/sprite.cpp
    core/gfx/table.cpp
    core/gfx/tilemap-vx.cpp
    core/gfx/tilemap.cpp
    core/gfx/viewport.cpp
    core/gfx/window-vx.cpp
    core/gfx/window.cpp

    core/input/input.cpp
    core/input/keybinds.cpp

    core/sys/sys.cpp

    core/config.cpp
    core/event-thread.cpp
    core/settings-menu.cpp
    core/shared-state.cpp

    util/ini-config.cpp

    ${CMAKE_SOURCE_DIR}/deps/libnsgif/gif.c
    ${CMAKE_SOURCE_DIR}/deps/libnsgif/lzw.c

    ${CMAKE_SOURCE_DIR}/deps/theoraplay/play.c
)

IF(WIN32)
    list(APPEND MKSHOT_SOURCES util/win/console.cpp)
ELSEIF(LINUX)
    list(APPEND MKSHOT_SOURCES
        oneshot/plat/linux-gtk.cpp
        oneshot/plat/linux-xdg-user-dirs.cpp
        oneshot/plat/linux-xfconf.cpp
    )
ELSEIF(APPLE)
    list(APPEND MKSHOT_SOURCES
        oneshot/plat/mac-oneshot.mm
        core/fs/plat/mac-fs.mm
        core/sys/plat/mac-sys.mm
    )
ENDIF()

IF(MKSHOT_HTTP)
    list(APPEND MKSHOT_SOURCES
        core/bind/bind-http.cpp
        core/http/http.cpp
    )
ENDIF()


## Compiler flags / defines ##
set(MKSHOT_DEFINES MKSHOT_VER_HASH="${MKSHOT_VER_HASH}" PARENT_SCOPE)
set(MKSHOT_CFLAGS "" PARENT_SCOPE)
set(MKSHOT_LDFLAGS "" PARENT_SCOPE)

IF(MKSHOT_GLES2)
    list(APPEND MKSHOT_DEFINES "GLES2")
ENDIF()

IF(MKSHOT_KEEP_CWD)
    list(APPEND MKSHOT_DEFINES "KEEP_CWD")
ENDIF()

IF(MKSHOT_SDL_STATIC)
    list(APPEND MKSHOT_DEFINES "SDL_STATIC_LIB")
ENDIF()

IF(MKSHOT_STEAM)
    list(APPEND MKSHOT_SOURCES
        core/bind/steam.cpp
        core/steam/steam.cpp
    )
    list(APPEND MKSHOT_DEFINES MKSHOT_STEAM)

    set(STEAMSHIM_MM "" PATH PARENT_SCOPE)
    IF(APPLE)
        set(STEAMSHIM_MM "${CMAKE_SOURCE_DIR}/deps/steamshim/mac_helpers.mm")
    ENDIF()

    set(STEAMSHIM_DEFINES "")
    set(STEAMSHIM_CFLAGS "")
    set(STEAMSHIM_LDFLAGS "")

    add_executable("steamshim" "${CMAKE_SOURCE_DIR}/deps/steamshim/parent.cpp" "${CMAKE_SOURCE_DIR}/deps/steamshim/child.h" "${STEAMSHIM_MM}")
    target_include_directories("steamshim" PRIVATE "${CMAKE_SOURCE_DIR}/deps/steamshim")
ENDIF()

add_executable("${PROJECT_NAME}" ${MKSHOT_SOURCES})
target_compile_definitions("${PROJECT_NAME}" PRIVATE ${MKSHOT_DEFINES})
target_include_directories("${PROJECT_NAME}" PRIVATE ${MKSHOT_INCDIRS})
target_compile_options("${PROJECT_NAME}" PRIVATE ${MKSHOT_CFLAGS})
target_link_libraries("${PROJECT_NAME}" PRIVATE ${MKSHOT_LINKLIBS})
target_link_options("${PROJECT_NAME}" PRIVATE ${MKSHOT_LDFLAGS})
