#ifndef BASICS
#define BASICS

#include <string>
#include <chrono>

// for ease of use when timing the executions of various methods

typedef std :: chrono :: steady_clock clk;

typedef std :: chrono :: milliseconds ms;

typedef std :: chrono :: microseconds us;

int num (int);

void space (void);

std :: string check (std :: string);

void exit (bool);

#endif // BASICS