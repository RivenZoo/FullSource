#include "Precompile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __GNUC__
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "KGCRT.h"

#ifdef __GNUC__

int kbhit()
{
    int            nResult         = false;
    int            nRetCode        = false;
    int            nGetOldAttrFlag = false;
    int            nStdinFD        = -1;
    int            nTtyFlag        = false;      
    struct termios OldValue;
    struct termios NewValue;
    timeval        Timeout         = {0, 0};
    fd_set         FDSet;

    nStdinFD = fileno(stdin);
    if (nStdinFD < 0)
        goto Exit0;

    // stdin maybe redirect to socket
    nTtyFlag = isatty(nStdinFD);
    if (nTtyFlag)
    {
        nRetCode = tcgetattr(nStdinFD, &OldValue);
        if (nRetCode)
        {
            // not a tty 
            goto Exit0;
        }
        nGetOldAttrFlag = true;

        NewValue = OldValue;

        /* Disable canonical mode, and set buffer size to 1 byte */
        NewValue.c_lflag     &= (~ICANON);
        NewValue.c_cc[VTIME]  = 0;
        NewValue.c_cc[VMIN]   = 1;

        tcsetattr(nStdinFD, TCSANOW, &NewValue);
    }

    // select or poll
    FD_ZERO(&FDSet);
    FD_SET(nStdinFD, &FDSet);

    nRetCode = select(nStdinFD + 1, &FDSet, NULL, NULL, &Timeout);
    if (nRetCode != 1)
        goto Exit0;

    nResult = true;
Exit0:
    if (nTtyFlag && nGetOldAttrFlag)
    {
        tcsetattr(nStdinFD, TCSANOW, &OldValue);
        nGetOldAttrFlag = false;
    }
    return nResult;
}

#endif
