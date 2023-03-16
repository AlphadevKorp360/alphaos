#pragma once
#define VGA_ADDRESS 0xB8000
#define NULL 0
#define BUFFSIZE 2200
#include <standardlibc/typedef.hpp>
using namespace types;

uShort *VGA_BUFFER;
enum VGA_COLOR_PALLETE
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

unsigned int VGA_INDEX;
static unsigned int NXTLINE = 1;
unsigned char GlobalForColor, GlobalBgColor;
int DigitalASCII[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

uShort StartVGA(unsigned char Charaters, uChar BackColor, uChar ForColor)
{
    uShort ax = 0;
    uChar ah = 0, al = 0;
    ah = ForColor;
    ah <<= 4;
    ah |= BackColor;
    ax = ah;
    ax <<= 8;
    al = Charaters;
    ax |= al;
    return ax;
}

void ClearVGABUFF(uShort **Buffer, uChar BackColor, uChar ForColor)
{
    uInt i;
    for (i = 0; i < BUFFSIZE; i++)
    {
        (*Buffer)[i] = StartVGA(NULL, BackColor, ForColor);
    }
    NXTLINE = 1;
    VGA_INDEX = 0;
}

void InitVGA(uChar BackColor, uChar ForColor)
{
    VGA_BUFFER = (uShort *)VGA_ADDRESS;
    ClearVGABUFF(&VGA_BUFFER, BackColor, ForColor);
    GlobalBgColor = BackColor;
    GlobalForColor = ForColor;
}