# TODO

- SDL2 -> SDL3
- Meson/Xcode + Makefiles -> CMake + Conan
    - Embed assets without involving xxd
    - Steam support
    - macOS support
    - Setup autobuilds
- Create a "build configuration" header
- JSON5 -> TOML
    - Add toggles for different configuration modes (which can be combined)
        1. Embed the values parsed build-time
        2. Parse the config at CWD (Current Workdir)
        3. Config overrides through providing exec flags (with --help for all the values)
- Use Dear IMGUI for internal GUI and fallback system pop-ups
- Ruby 3.4 -> 4.x
    - Extend YJIT support
    - Add support for ZJIT
- SDL_ttf -> Freetype/HarfBuzz + msdf-atlas-gen
- SDL_image -> libvips
    - Add support for JPEG-XL, WEBP, APNG
- SDL_sound + OpenAL -> Miniaudio
    - Add support for OGG/Opus, WAV, FLAC, WEBM/Vorbis, WEBM/Opus
    - FMOD/SoLoud-like dynamic audio manupulation through bindings
- Theora -> WEBM/VP8, WEBM/VP9
- Better animated custscenes/movies implementation
- Reimplementation of the Journal program
