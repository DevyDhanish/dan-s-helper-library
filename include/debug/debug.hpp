/*
   Property of [Dhanish aka dan]
   [header file for debuging methods. link the binary with `.lib`]
   [written @ 12:13 22 march 2024]
*/

#pragma once

#include <stdint.h>
#include <iostream>

namespace CONSOLELOG
{
   enum LOGTYPE
   {
      ERRORLOG,
      INFOLOG,
      DEBUGLOG,
   };
};

// comment this line if you want to remove the logs
#define LOGGING

#define WHITE_COLOR (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)
#define ERROR_BG_COLOR (BACKGROUND_RED)
#define INFO_BG_COLOR (BACKGROUND_GREEN)
#define DEBUG_BG_COLOR (BACKGROUND_RED | BACKGROUND_BLUE)

void __print__errorlog_background_banner__(const char *text, unsigned short foregroundColor, unsigned short backgroundColor);
void __print__banner(CONSOLELOG::LOGTYPE type);

/// <summary>
/// Log the msg, USE #define ENABLE_DEBUG in your src files inorder for log function to work. 
/// </summary>
/// <param name="msg">msg you wanna print</param>
#ifdef __cplusplus < 201402L	// if the c++ compiler does not have the auto feature
template<typename T>
void consolelog(T data, CONSOLELOG::LOGTYPE type)
{
#ifdef LOGGING
	__print__banner(type);
	std::cout << data << "\n";
#endif
}
#else
void consolelog(auto data, CONSOLELOG::LOGTYPE type)
{
#ifdef LOGGING
	__print__banner(type);
	std::cout << data << "\n";
#endif
}
#endif