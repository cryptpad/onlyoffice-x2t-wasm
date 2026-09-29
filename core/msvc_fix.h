#ifdef _WIN32
#   include <winsock2.h>
#   include <windows.h>
/* Undef Windows API macros that conflict with FontFile.cpp */
#   ifdef GetCharWidth
#       undef GetCharWidth
#   endif
/* Undef Windows API macros that conflict with docbuilder_p.cpp */
#   ifdef CreateFile
#       undef CreateFile
#   endif
#endif
