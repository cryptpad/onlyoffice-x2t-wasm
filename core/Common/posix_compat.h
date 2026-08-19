#pragma once

#ifdef _WIN32
    #include <sys/stat.h>
    #include <sys/utime.h>
#else
    #include <sys/stat.h>
    #include <utime.h>
    #include <unistd.h>
#endif
