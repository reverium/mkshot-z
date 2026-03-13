from conan import ConanFile
from conan.tools.cmake import cmake_layout


class mkshot-z(ConanFile):
    name = "mkshot-z"
    license = "GPL-3.0-or-later"
    url = "https://github.com/reverium/mkshot-z"
    description = "Experimental OneShot (2016) engine reimplementation for modders"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    exports_sources = "*"

    if self.settings.os == "Windows" and self.settings.os.subsystem != "msys2":

    if self.settings.compiler != "gcc" and self.settings.compiler != "clang"

    # sdl_sound, ruby
    requires = (
        "vorbis/v1.3.7",
        "physfs/3.2.0",
        "uchardet/0.0.8",
        "pixman/0.46.2",
        "sdl/2.32.10",
        "sdl_image/2.8.8",
        "sdl_ttf/2.24.0",
        "openal-soft/1.23.1"
    )

    if self.settings.os == "Windows":
        requires += ("libiconv/1.18")

    build_requires = (
        "cmake",
        "ninja",
        "meson",
        "automake",
        "autoconf",
        "libtool",
        "bison",
        "ruby"
    )

    options = {
        "dynamic": [True, False],
        "force_32bit": [True, False],
        "gles": [True, False],
        "keep_cwd": [True, False],
        "steamworks_path": ["ANY"],
        "steam_appid": ["ANY"]
        "steamshim_debug": [True, False]
    }

    default_options = {
        "dynamic": False,
        "force_32bit": False,
        "gles": False,
        "keep_cwd": False,
        "steamworks_path": "",
        "steam_appid": "",
        "steamshim_debug": False
    }
