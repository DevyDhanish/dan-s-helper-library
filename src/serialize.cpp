#include "../include/serialize/serialize.hpp"
#include <iostream>
#include "../include/debug/debug.hpp"

void serialize(uint64_t data, uint32_t dataSize, char* buf, uint32_t bufSize)
{
    if (dataSize != bufSize)
    {
        const char msg[] = "Data Size and buffer size do not match";
        //errlog((void *)msg, ddtype::DTYPE::STRING);
        return;
    }

    for (uint32_t i = 0; i < bufSize; i++)
    {
        buf[(bufSize - (i + 1))] = data & 0xff;
        data = data >> 8;
    }
}

uint64_t deserialize(char* buf, uint32_t bufSize)
{
    uint64_t bufDat = 0;

    for (uint32_t i = 0; i < bufSize; i++)
    {
        bufDat = bufDat << 8;
        bufDat = bufDat | (uint8_t)buf[i];
    }

    return bufDat;
}

void serializeF(float data, uint32_t dataSize, char* buf, uint32_t bufSize)
{
    const char msg[] = "SerializeF not implemented";
    //errlog((void *)msg, ddtype::DTYPE::STRING);
}