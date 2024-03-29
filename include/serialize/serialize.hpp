/*
   Property of [Dhanish aka dan]
   [header file for serialization methods. link the binary with `.lib`]
   [written @ 12:13 22 march 2024]
*/

#pragma once
#include <stdint.h>

/// <summary>
/// Function to serialize data types like (int, uint8..uint64, short, long)
/// DO NOT USE THIS FUNCTION WITH FLOAT/DOUBLES FOR THAT USE serializeF
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="data">data you want to serialize</param>
/// <param name="dataSize">size of the data use "sizeof(data)"</param>
/// <param name="buf">buffer where the serialized data will be stored</param>
/// <param name="bufSize">size of the buffer use "sizeof(buf)"</param>
void serialize(uint64_t data, uint32_t dataSize, char* buf, uint32_t bufSize);

/// <summary>
/// Function to deserialize the buffer into it's data.
/// </summary>
uint64_t deserialize(char* buf, uint32_t bufSize);


/// <summary>
/// Function to serialize data types like (float double)
/// DO NOT USE THIS FUNCTION WITH ANYTHING OTHER THAN FLOATS/DOUBLES FOR THAT USE serialize
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="data">data you want to serialize</param>
/// <param name="dataSize">size of the data use "sizeof(data)"</param>
/// <param name="buf">buffer where the serialized data will be stored</param>
/// <param name="bufSize">size of the buffer use "sizeof(buf)"</param>
void serializeF(float data, uint32_t dataSize, char* buf, uint32_t bufSize);