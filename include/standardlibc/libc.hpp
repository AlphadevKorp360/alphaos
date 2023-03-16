#pragma once
#include <standardlibc/typedef.hpp>

types::uVoid Print(const char *Msg, ...)
{
    static auto *VIDEOMEM = (types::uShort *)0xb8000;
    static types::uChar X = 0, Y = 0;

    for (types::int_t i = 0; Msg[i] != '\0'; ++i)
    {
        switch (Msg[i])
        {
        case '\n':
            X = 0;
            Y++;
            break;
        case '\t':
            ++X;
            Y = Y;
            break;
        default:
            VIDEOMEM[80 * Y + X] = (VIDEOMEM[80 * Y + X] & 0xFF00) | Msg[i];
            X++;
            break;
        }

        if (X >= 80)
        {
            X = 0;
            Y++;
        }

        if (Y >= 25)
        {
            for (Y = 0; Y < 25; Y++)
                for (X = 0; X < 80; X++)
                    VIDEOMEM[80 * Y + X] = (VIDEOMEM[80 * Y + X] & 0xFF00) | ' ';
            X = 0;
            Y = 0;
        }
    }
};

types::uInt Counter(types::int_t Num)
{
    types::uInt Count = 0;
    if (Num == 0)
        return 1;
    while (Num > 0)
    {
        Count++;
        Num = Num / 10;
    }
    return Count;
};

types::uInt StringLength(const types::string Str)
{
    types::uInt Length = 0;
    while (Str[Length])
        Length++;
    return Length;
};

types::uVoid Identify(types::int_t Num, auto *IdentityNumber)
{
    types::int_t DGCount = Counter(Num);
    types::int_t Index = DGCount - 1;
    char X;
    if (Num == 0 && DGCount == 1)
    {
        IdentityNumber[0] = '0';
        IdentityNumber[1] = '\0';
    }
    else
    {
        while (Num != 0)
        {
            X = Num % 10;
            IdentityNumber[Index] = X + '0';
            Index--;
            Num = Num / 10;
        }
        IdentityNumber[DGCount] = '\0';
    }
};

types::uVoid PrintDigit(types::uInt Num)
{
    char NumConv_Str[Counter(Num) + 1];
    Identify(Num, NumConv_Str);
    Print(NumConv_Str);
};

types::uVoid PrintHexa(types::uChar Hexa)
{
    char *Out = (char *) "00";
    char *hex = (char *) "0123456789ABCDEF";
    Out[0] = hex[(Hexa >> 4) & 0xF];
    Out[1] = hex[Hexa & 0xF];
    Print(Out);
};

types::uVoid PrintHexa16(types::uShort Hexa16)
{
    PrintHexa((Hexa16 >> 8) & 0xFF);
    PrintHexa(Hexa16 & 0xFF);
};

types::uVoid PrintHexa32(types::uInt Hexa32)
{
    PrintHexa16((Hexa32 >> 24) & 0xFF);
    PrintHexa16((Hexa32 >> 16) & 0xFF);
    PrintHexa16((Hexa32 >> 8) & 0xFF);
    PrintHexa16(Hexa32 & 0xFF);
}

types::uInt StrLen(types::uChar Str[])
{
    types::uInt i = 0;
    while (Str[i] != '\0')
        ++i;
    return i;
};

types::uVoid Append(types::uChar Str[], types::uChar Num)
{
    types::uInt len = StrLen(Str);
    Str[len] = Num;
    Str[len + 1] = '\0';
};

types::uVoid BackSpace(types::uChar Str[])
{
    types::uInt Len = StrLen(Str);
    Str[Len - 1] = '\0';
};

types::int_t StrCopy(auto Str1[], auto Str2[])
{
    types::int_t i;
    for (i = 0; Str1[i] == Str2[i]; i++)
    {
        if (Str1[i] == '\0')
            return 0;
    }
    return Str1[i] - Str2[i];
};