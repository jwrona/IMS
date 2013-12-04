#ifndef MACROS_H
#define MACROS_H

#ifndef NDEBUG_PRINT
    #define DEBUG(x) do { std::cout << x << "\tid = " \
    << id << "\tPriority = "<< static_cast<unsigned>(Priority) \
    << "\ttime = " << Time << std::endl;} while (0)
#else
    #define DEBUG(x)
#endif //NDEBUG

#endif //MACORS_H
