## Cool info ##
cmake_minimum_required(VERSION 3.25)

project(mkshot-z
    DESCRIPTION "OneShot (2016) engine reimplementation for modders"
    LANGUAGES "CXX"
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## Environment checks ##
IF(WIN32)
    string(TOLOWER "${CMAKE_CXX_COMPILER}" _msyscheck_CXX_COMPILER_PATH)

    # and no, msvc isn't supported
    # (never will be)
    IF(NOT DEFINED ENV{MSYSTEM})
        message(FATAL_ERROR
        "Building on Windows requires you to use MSYS2: <https://www.msys2.org>.\n"
        "Please consult the documentation before proceeding.")
    ENDIF()
ELSEIF(APPLE)
    # having bad support is worse than having none
    # macos will be supported at some point later tho
    message(FATAL_ERROR "macOS isn't supported at the moment.")
ELSEIF(NOT LINUX)
    message(FATAL_ERROR "This operating system isn't supported. 'Detected: ${CMAKE_SYSTEM_NAME}'.")
ENDIF()

set(MKSHOT_GCC $<CXX_COMPILER_ID:GNU>)
set(MKSHOT_CLANG $<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>)
if(NOT MKSHOT_GCC And NOT MKSHOT_CLANG)
    message(FATAL_ERROR "mkshot-z only supports GCC or Clang. Detected: ${CMAKE_CXX_COMPILER_ID}")
endif()


## Options ##
option(MKSHOT_DYNAMIC "Build and link mkshot-z dependencies dynamically." OFF)
option(MKSHOT_FORCE_32BIT "Force the compiler to build in 32-bit mode." OFF)
option(MKSHOT_GLES2 "Use OpenGL ES 2.0 instead of OpenGL." OFF)
option(MKSHOT_KEEP_CWD "Keep Current Working Directory on startup." OFF)

set(MKSHOT_STEAMWORKS_PATH "" CACHE PATH "Path to Steamworks SDK. Provide this to enable the Steam features.")
set(MKSHOT_STEAM_APPID "" CACHE STRING "Steam AppID value. Set this to use 'SteamAPI_RestartAppIfNecessary()'.")
option(MKSHOT_STEAMSHIM_DEBUG "Whether to show Steamshim debug output console." OFF)


## Prerequisites ##
# get short git hash (we use that instead of versioning)
find_package(Git QUIET)
set(MKSHOT_VER_HASH "no git hash found :p")

IF(GIT_EXECUTABLE)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" log -1 --format=%h
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE _mkshot_verhash_output
        RESULT_VARIABLE _mkshot_verhash_exitcode
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    IF(_mkshot_verhash_exitcode EQUAL 0)
        set(MKSHOT_VER_HASH "${_mkshot_verhash_output}")
        message(STATUS "Git hash: ${_mkshot_verhash_output}")
    ELSE()
        message(WARNING "Failed getting the Git hash. Exit code: ${_mkshot_verhash_exitcode}")
        message(WARNING "Hash value will fallback to '${MKSHOT_VER_HASH}'.")
    ENDIF()
ELSE()
    message(WARNING "Git executable not found. Hash value will fallback to '${MKSHOT_VER_HASH}'.")
ENDIF()
