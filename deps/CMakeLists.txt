# include(FetchContent)

## Dependencies ##
find_package(PkgConfig QUIET REQUIRED)
find_package(Ruby REQUIRED)

set(MKSHOT_PC
    vorbisfile
    theoradec
    pixman-1
    physfs
    uchardet
    sdl3
    sdl3-image
    sdl3-ttf
    sdl3-sound
    openal
)

set(MKSHOT_LIBS ${RUBY_LIBRARIES})

FOREACH(__pc ${MKSHOT_PC})
    pkg_check_modules(MKSHOT_${__pc} REQUIRED IMPORTED_TARGET GLOBAL ${__pc})
    list(APPEND MKSHOT_LIBS PkgConfig::MKSHOT_${__pc})
ENDFOREACH()

set(MKSHOT_LINKLIBS ${MKSHOT_LIBS} PARENT_SCOPE)

## Steamworks SDK ##
IF(MKSHOT_STEAMWORKS_PATH)
    message(STATUS "Searching for Steamworks SDK in '${MKSHOT_STEAMWORKS_PATH}'...")

    # look for the actual header to verify the path
    find_path(MKSHOT_STEAMWORKS_PATH steam/steam_api.h
        PATHS "${MKSHOT_STEAMWORKS_PATH}/public"
        NO_DEFAULT_PATH
    )

    IF(STEAM_INCLUDE_DIR)
        set(MKSHOT_STEAM ON)
        message(STATUS "The Steamworks SDK has been found and validated, enabling Steam features.")
    ELSE()
        message(FATAL_ERROR "MKSHOT_STEAMWORKS_PATH was set, but steam/steam_api.h was not found!")
    ENDIF()
ENDIF()
