
#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 1
#if DEBUG==1
#define DD(x) (x)
#define DR(x) (std::cerr << (x) << "\n")
#define DO(x) (std::cout << (x) << "\n")
#else
#define DD(x)
#define DR(x)
#define DO(x)
#endif

#include <iostream>

#endif // DEBUG_H

