#ifndef MACROS_H
#define MACROS_H

#include <cmath>

#ifndef NDEBUG_PRINT
    #define DEBUG(x) do {\
    std::cout << x << "\tid = " << id << "\tPriority = "\
    << static_cast<unsigned>(Priority) <<"\tsim time = " << Time\
    << "\treal time = " << static_cast<unsigned>(Time / 60) << ':'\
    <<  static_cast<unsigned>(fmod(Time, 60)) << std::endl;\
    } while (0)
#else
    #define DEBUG(x)
#endif //NDEBUG

#endif //MACORS_H
