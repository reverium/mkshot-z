# Get Ruby dependency
mkxp_dependencies += dependency('ruby-3.1')
if cxx.get_id() == 'clang'
    mkxp_cflags += '-fdeclspec'
endif

mkxp_binding_sources = files(
    'module_rpg.cpp',
    'binding-mri.cpp',
    'binding-util.cpp',
    'etc-binding.cpp',
    'table-binding.cpp',
    'graphics-binding.cpp',
    'input-binding.cpp',
    'audio-binding.cpp',
    'bitmap-binding.cpp',
    'sprite-binding.cpp',
    'plane-binding.cpp',
    'viewport-binding.cpp',
    'font-binding.cpp',
    'window-binding.cpp',
    'windowvx-binding.cpp',
    'tilemap-binding.cpp',
    'tilemapvx-binding.cpp',
    'filesystem-binding.cpp',
    'http-binding.cpp',
    'steam-binding.cpp',

    'oneshot/oneshot-binding.cpp',
    'oneshot/journal-binding.cpp',
    'oneshot/niko-binding.cpp',
    'oneshot/wallpaper-binding.cpp'
)

# TODO (why is it commented out?)
#if mkxp_steam
#    mkxp_binding_sources += files(
#        'cusl-binding.cpp'
#    )
#endif

if mkxp_miniffi
    mkxp_binding_sources += files(
        'miniffi.cpp',
        'miniffi-binding.cpp'
    )
endif

mkxp_sources += mkxp_binding_sources
mkxp_includes += include_directories('.')
