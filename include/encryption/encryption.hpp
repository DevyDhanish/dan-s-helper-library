/*
   Property of [Dhanish aka dan]
   [header file for encryption methods. link the binary with `.lib`]
   [written @ 22:51 22 march 2024]
*/

#pragma once

#include <stdint.h>

uint32_t getSubtituteEncryptKey();

/// <summary
/// Encrypts the srcBuf
///	</summary>
/// <param name="srcBuf"></param>
/// <param name="srcBufSize"></param>
/// <param name="destBuf"></param>
/// <param name="destBufSize"></param>
void subtituteEncrypt(uint8_t* srcBuf, uint32_t srcBufSize, uint32_t key);

/// <summary
/// decrypts the srcBuf
///	</summary>
/// <param name="srcBuf"></param>
/// <param name="srcBufSize"></param>
/// <param name="destBuf"></param>
/// <param name="destBufSize"></param>
void subtituteDecrypt(uint8_t* srcBuf, uint32_t srcBufSize, uint32_t key);