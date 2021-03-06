
#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 0
#if DEBUG==1
#define DD(x) (x)
#define DER(x, ...) (fprintf(stderr, x , ##__VA_ARGS__))
#define DR(x) (std::cerr << (x) << "\n")
#define DO(x) (std::cout << (x) << "\n")
#else
#define DD(x)
#define DER(x, ...)
#define DR(x)
#define DO(x)
#endif

#define DEBUG_STAT 1
#if DEBUG_STAT==1
#define DES(x, ...) (fprintf(stderr, x , ##__VA_ARGS__))
#else
#define DES(x, ...)
#endif

#include <iostream>
#include <cstdio>

#endif // DEBUG_H

