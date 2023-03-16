#include <drivers/video/videogfx.hpp>
#include <standardlibc/libc.hpp>

extern "C" void kernelinit()
{
    InitVGA(WHITE, CYAN);
    Print("Ibrahim Zaman A!\n");
    PrintDigit(100000);
    PrintHexa16(1011);
}