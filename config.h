#ifndef _CONFIG_H_
#define _CONFIG_H_
// When submitting in MAMA, put the line below in remark and make sure your project compiles in Linux!
// (this is not mandatory, but can add bonus points)
#define WINDOWS
// make sure to always submit a readme file in English, with student names and ids
// if you put the above #define WINDOWS in comment for compilation in MAMA - remind us in the readme file that we need to take it out of comment!

    #ifndef WINDOWS

    int _getch(void);
    int _kbhit(void);
    void Sleep(unsigned long);
    void _itoa_s(unsigned int, char s[], unsigned int, int);

    #else
    #include <stdlib.h>
    #include <conio.h>
    #include <windows.h>
    #endif

#endif

