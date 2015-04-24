#ifdef __CYGWIN__
  #ifdef _USRDLL
    #ifdef OPENGL_CORE_EXPORTS
      #define OPENGL_CORE_API __declspec(dllexport)
    #else
      #define OPENGL_CORE_API __declspec(dllimport)
    #endif
  #else
    #define OPENGL_CORE_API
  #endif
#elif (defined WIN32) || (defined _WIN32) || (defined __WIN32__)
  #ifdef _USRDLL
    #ifdef OPENGL_CORE_EXPORTS
      #define OPENGL_CORE_API __declspec(dllexport)
    #else
      #define OPENGL_CORE_API __declspec(dllimport)
    #endif
  #else
    #define OPENGL_CORE_API
  #endif
#elif (defined __gnu_linux__) || (defined __linux__)
  #define OPENGL_CORE_API
#endif
