set(CLANG "${CMAKE_CURRENT_LIST_DIR}/bin/clang")
set(CLANG_LLD "${CMAKE_CURRENT_LIST_DIR}/bin/ld.lld")

set(NX64_OPT_FLAGS "-O3 -g")
set(NX64_TRIPLE aarch64-linux-elf)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_SYSROOT ${CMAKE_CURRENT_LIST_DIR}/musl)
set(CMAKE_C_COMPILER "${CLANG}")
set(CMAKE_C_COMPILER_TARGET ${NX64_TRIPLE})
set(CMAKE_CXX_COMPILER "${CLANG}")
set(CMAKE_CXX_COMPILER_TARGET ${NX64_TRIPLE})

set(CMAKE_C_FLAGS_RELEASE ${NX64_OPT_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${NX64_OPT_FLAGS})
set(CMAKE_C_FLAGS_RELWITHDEBINFO ${NX64_OPT_FLAGS})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${NX64_OPT_FLAGS})

# Target options
add_compile_options(-mcpu=cortex-a57+fp+simd+crypto+crc)
add_compile_options(-mno-implicit-float)
# Environment
add_compile_options(-stdlib=libc++)
add_compile_options(-fPIC)
# Helps with matching as this causes Clang to emit debug type info even for dynamic classes
# with undefined vtables.
add_compile_options(-fstandalone-debug)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/libcxx-include)
# Helps with matching as this causes Clang to emit debug type info even for dynamic classes
# with undefined vtables.
add_compile_options(-fstandalone-debug)
# avoids reading system-wide headers on later clang versions (for example linter's libclang)
add_compile_options(--gcc-toolchain=/nonexistant)
# after all other includes, use fallback clang headers
# => applied only when building this project normally, using system-wide (lib-)clang will use its own
add_compile_options(-idirafter ${CMAKE_CURRENT_LIST_DIR}/clang-include)
# custom libc++, provided in combination with clang-3.9.1
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/libcxx-include)


add_definitions(-D SWITCH)
add_definitions(-D NNSDK)
add_definitions(-D MATCHING_HACK_NX_CLANG)

add_link_options(-nostdlib)
add_link_options(-fPIC -Wl,-Bsymbolic-functions -shared)
add_link_options(-fuse-ld=lld)