# This thing only runs when executed via: cmake -P EmbedAssets.cmake
IF(NOT "${__mkshot_embed_input}" STREQUAL "")
    file(READ "${__mkshot_embed_input}" __mkshot_embed_hex HEX)
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, " __mkshot_embed_array "${__mkshot_embed_hex}")
    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" __mkshot_embed_varname "${__mkshot_embed_input}")
    set(__mkshot_embed_htext "#pragma once
#include <cstddef>
namespace EmbeddedAssets {
 inline const unsigned char ${__mkshot_embed_varname}[] = { $ {__mkshot_embed_array} };
 inline const size_t ${__mkshot_embed_varname}_size = sizeof($ {__mkshot_embed_varname});
}
")
    file(WRITE " ${__mkshot_embed_output}" "$ {__mkshot_embed_htext}")
ENDIF()
