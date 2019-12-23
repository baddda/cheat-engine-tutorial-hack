#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <Windows.h>

class debugStreambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c = EOF) {
        if (c != EOF) {
            TCHAR buf[] = { c, '\0' };
            OutputDebugString(buf);
        }
        return c;
    }
};

class Clog2VisualStudioDebugOutput {

    debugStreambuf dbgstream;
    std::streambuf* default_stream;

public:
    Clog2VisualStudioDebugOutput() {
        default_stream = std::clog.rdbuf(&dbgstream);
    }

    ~Clog2VisualStudioDebugOutput() {
        std::clog.rdbuf(default_stream);
    }
};

void PrintLastErrorMessage();

#endif