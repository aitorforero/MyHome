#ifndef _Debug_h
#define _Debug_h

class Debug
{
    public:
        static void initialize(int br);
        static void debug(const char* text);
        static void debug(int maxSize,const char* text, ...);
};

#endif
