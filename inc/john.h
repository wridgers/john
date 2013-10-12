#include <chrono>
#include <iostream>
#include <thread>

// visual leak detector
#ifdef __VS
    #include <vld.h>
#endif

#include "core/tracer.h"
