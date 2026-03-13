include(FetchContent)

## Dependencies ##
find_package(Vorbis REQUIRED CONFIG)
find_package(PhysFS REQUIRED CONFIG)
find_package(uchardet REQUIRED CONFIG)
find_package(pixman REQUIRED CONFIG)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_sound REQUIRED CONFIG)
find_package(OpenAL REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Vorbis::vorbisfile
    uchardet::uchardet
    physfs::physfs
)

## Options / Defines ##
target_compile_definitions(${PROJECT_NAME} PRIVATE MKSHOT_VER_HASH="${MKSHOT_VER_HASH}")

IF(MKSHOT_FORCE_32BIT)
    add_compile_options("-m32")
    add_link_options("-m32")
ENDIF()

IF(MKSHOT_KEEP_CWD)
    target_compile_definitions(${PROJECT_NAME} PRIVATE KEEP_CWD)
ENDIF()

IF(MKSHOT_GLES)
    target_compile_options(${PROJECT_NAME} PRIVATE GLES2)
ENDIF()

## Sources / Includes ##
include_directories("${CMAKE_SOURCE_DIR}/deps")
list(APPEND MKSHOT_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}")

set(MKSHOT_SOURCES
    main.cpp

    binding/oneshot/journal.cpp
    binding/oneshot/niko.cpp
    binding/oneshot/oneshot.cpp
    binding/oneshot/wallpaper.cpp

    core/oneshot/i18n.cpp
    core/oneshot/journal.cpp
    core/oneshot/oneshot.cpp
    core/oneshot/wallpaper.cpp

    binding/audio.cpp
    binding/bitmap.cpp
    binding/etc.cpp
    binding/font.cpp
    binding/fs.cpp
    binding/gfx.cpp
    binding/http.cpp
    binding/input.cpp
    binding/mri.cpp
    binding/plane.cpp
    binding/rgss.cpp
    binding/sprite.cpp
    binding/table.cpp
    binding/tilemap-vx.cpp
    binding/tilemap.cpp
    binding/util.cpp
    binding/viewport.cpp
    binding/window-vx.cpp
    binding/window.cpp

    core/audio/al-stream.cpp
    core/audio/audio.cpp
    core/audio/sdl_sound-source.cpp
    core/audio/sound-emitter.cpp
    core/audio/stream.cpp
    core/audio/vorbis-source.cpp

    core/etc/etc.cpp
    core/etc/table.cpp

    core/fs/fs-impl.cpp
    core/fs/fs.cpp

    core/gfx/autotiles-vx.cpp
    core/gfx/autotiles.cpp
    core/gfx/bitmap.cpp
    core/gfx/font.cpp
    core/gfx/gfx.cpp
    core/gfx/gl-debug.cpp
    core/gfx/gl-fun.cpp
    core/gfx/gl-meta.cpp
    core/gfx/gl-scene.cpp
    core/gfx/gl-shader.cpp
    core/gfx/gl-state.cpp
    core/gfx/gl-texpool.cpp
    core/gfx/gl-tileatlas-vx.cpp
    core/gfx/gl-tileatlas.cpp
    core/gfx/gl-tilequad.cpp
    core/gfx/gl-vertex.cpp
    core/gfx/plane.cpp
    core/gfx/sprite.cpp
    core/gfx/tilemap-vx.cpp
    core/gfx/tilemap.cpp
    core/gfx/viewport.cpp
    core/gfx/window-vx.cpp
    core/gfx/window.cpp

    core/input/input.cpp
    core/input/keybinds.cpp

    core/net/net.cpp

    core/sys/sys-impl.cpp

    core/config.cpp
    core/event-thread.cpp
    core/settings-menu.cpp
    core/shared-state.cpp

    util/ini-config.cpp
    util/xdg-user-dirs.cpp
)

set(MKSHOT_SHADER
    shader/bicubic.frag
    shader/bitmap-blit.frag
    shader/blur-h.vert
    shader/blur-v.vert
    shader/blur.frag
    shader/common.hpp
    shader/flash-map.frag
    shader/flat-color.frag
    shader/gray.frag
    shader/hue.frag
    shader/lanczos3.frag
    shader/minimal.vert
    shader/obscured.frag
    shader/plane.frag
    shader/simple-alpha-uni.frag
    shader/simple-alpha.frag
    shader/simple-color.frag
    shader/simple-color.vert
    shader/simple-matrix.vert
    shader/simple.frag
    shader/simple.vert
    shader/sprite.frag
    shader/sprite.vert
    shader/tilemap-vx.vert
    shader/tilemap.frag
    shader/tilemap.vert
    shader/trans-simple.frag
    shader/trans.frag
    shader/xbrz.frag
)

IF(WIN32)
    list(APPEND MKSHOT_SOURCES util/win-console.cpp)
ELSEIF(LINUX)
    list(APPEND MKSHOT_SOURCES core/oneshot/gnome-fun.cpp core/oneshot/xfconf-fun.cpp)
ENDIF()

IF(MKSHOT_HTTP)
    list(APPEND MKSHOT_SOURCES binding/http.cpp core/net/net.cpp)
ENDIF()

IF(MKSHOT_STEAM)
    list(APPEND MKSHOT_SOURCES binding/steam.cpp core/steam/steam.cpp)
ENDIF()
