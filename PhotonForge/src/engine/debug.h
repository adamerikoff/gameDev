#define DEBUG

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define LOG_DEBUG(msg, ...) fprintf(stderr, "DEBUG: " msg "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif

#endif