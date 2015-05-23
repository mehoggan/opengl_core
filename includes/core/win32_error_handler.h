#ifndef WIN32_ERROR_HANDLER_H_INCLUDED
#define WIN32_ERROR_HANDLER_H_INCLUDED

#include <cassert>

#include <Windows.h>

#define print_last_error_and_assert() do { \
    DWORD last_error = ::GetLastError(); \
    if (last_error != 0) { \
      LPSTR message_buffer = nullptr; \
      DWORD size = ::FormatMessageA( \
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | \
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, last_error, \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, \
        NULL); \
      ::OutputDebugStringA("\n"); \
      ::OutputDebugStringA("==============================================\n"); \
      ::OutputDebugStringA("Win32 Fatal Error: "); \
      ::OutputDebugStringA(message_buffer); \
      ::OutputDebugStringA("==============================================\n"); \
      ::LocalFree(message_buffer); \
    } \
    assert(false && "Windows Error Handler"); \
  } while (false);

#define print_last_error() do { \
    DWORD last_error = ::GetLastError(); \
    if (last_error != 0) { \
      LPSTR message_buffer = nullptr; \
      DWORD size = ::FormatMessageA( \
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | \
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, last_error, \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&message_buffer, 0, \
        NULL); \
      ::OutputDebugStringA("\n"); \
      ::OutputDebugStringA("==============================================\n"); \
      ::OutputDebugStringA("Win32 Error: "); \
      ::OutputDebugStringA(message_buffer); \
      ::OutputDebugStringA("==============================================\n"); \
      ::LocalFree(message_buffer); \
    } \
  } while (false);

#endif