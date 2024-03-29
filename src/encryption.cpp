#include "../include/encryption/encryption.hpp"
#include "../include/utils/utils.hpp"
#include <iostream>
#include <map>

uint32_t getSubtituteEncryptKey()
{
	return 0x0303070b;
}

int getSubChar(const char currChar, const char* pool, uint32_t poolSize, uint8_t offset)
{
	int result = 0;
	
	for (uint32_t i = 0; i < poolSize; i++)
	{
		if (currChar == pool[i])
		{
			result = offset * i;

			return result;
		}
	}

	return result;
}

void subtituteEncrypt(uint8_t *srcBuf, uint32_t srcBufSize, uint32_t key)
{
	std::map<char, uint32_t> occurance;

	uint8_t nonCharShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t dupCharShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t wordCountShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t charShiftnessAmount = key & 0xff;
	key = key >> 8;

	for (uint32_t i = 0; i < srcBufSize; i++)
	{
		occurance[srcBuf[i]] = ++occurance[srcBuf[i]];
	}

	for (uint32_t i = 0; i < srcBufSize; i++)
	{
		if (occurance[srcBuf[i]] > 1)
		{
			int offset = getSubChar(srcBuf[i], allChars, sizeof(allChars), occurance[srcBuf[i]] + dupCharShiftnessAmount);
			srcBuf[i] = allChars[offset];

			std::cout << offset << " " << allChars[offset] << "\n";
		}
		else
		{
			int offset = getSubChar(srcBuf[i], allChars, sizeof(allChars), occurance[srcBuf[i]] + charShiftnessAmount);
			srcBuf[i] = allChars[offset];

			std::cout << offset << " " << allChars[offset] << "\n";
		}
	}

	srcBuf[srcBufSize - 1] = '\0';
}

void subtituteDecrypt(uint8_t *srcBuf, uint32_t srcBufSize, uint32_t key)
{
	std::map<char, uint32_t> occurance;

	uint8_t nonCharShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t dupCharShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t wordCountShiftnessAmount = key & 0xff;
	key = key >> 8;

	uint8_t charShiftnessAmount = key & 0xff;
	key = key >> 8;

	for (uint32_t i = 0; i < srcBufSize; i++)
	{
		occurance[srcBuf[i]] = ++occurance[srcBuf[i]];
	}

	for (uint32_t i = 0; i < srcBufSize; i++)
	{
		if (occurance[srcBuf[i]] > 1)
		{
			int offset = getSubChar(srcBuf[i], allChars, sizeof(allChars), occurance[srcBuf[i]] - dupCharShiftnessAmount); // Reverse the shift for duplicate characters
			srcBuf[i] = allChars[offset];
		}
		else
		{
			int offset = getSubChar(srcBuf[i], allChars, sizeof(allChars), occurance[srcBuf[i]] - charShiftnessAmount); // Reverse the shift for non-duplicate characters
			srcBuf[i] = allChars[offset];
		}
	}

	srcBuf[srcBufSize - 1] = '\0';
}