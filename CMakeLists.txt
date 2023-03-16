# C++, LD, AS Executable and Flags:
PROJECT(AlphaOS C CXX ASM)
include(include)
add_custom_target(
        COMMAND make
        COMMAND make clean
)