#ifndef MEMORY_LEAKS_H_INCLUDED
#define MEMORY_LEAKS_H_INCLUDED

#include "core/platform.h"

#ifdef __OPENGL_CORE_WINDOWS__
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>

  #define MEMORY_LEAK_DETECTION_START() do { \
      _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); \
      _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG); \
    } while (false);

  #define MEMORY_LEAK_DETECTION_STOP() do { \
      _CrtDumpMemoryLeaks(); \
    } while (false);
#else
  #define MEMORY_LEAK_DETECTION_START() do { \
    } while (false);

  #define MEMORY_LEAK_DETECTION_STOP() do { \
    } while (false);
#endif

#endif
