#ifndef __VSF_LINUX_TERMIOS_H__
#define __VSF_LINUX_TERMIOS_H__

#include "shell/sys/linux/vsf_linux_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#if VSF_LINUX_CFG_WRAPPER == ENABLED
#define tcgetattr   VSF_LINUX_WRAPPER(tcgetattr)
#define tcsetattr   VSF_LINUX_WRAPPER(tcsetattr)
#endif

typedef unsigned int tcflag_t;
typedef unsigned char cc_t;
typedef unsigned int speed_t;

// tcsetattr optional_actions
#define TCSANOW     0
#define TCSADRAIN   1
#define TCSAFLUSH   2

#define IGNBRK      0000001
#define BRKINT      0000002
#define IGNPAR      0000004
#define PARMRK      0000010
#define INPCK       0000020
#define ISTRIP      0000040
#define INLCR       0000100
#define IGNCR       0000200
#define ICRNL       0000400
#define IUCLC       0001000
#define IXON        0002000
#define IXANY       0004000
#define IXOFF       0010000
#define IMAXBEL     0020000
#define IUTF8       0040000

#define OPOST       0000001
#define OLCUC       0000002
#define ONLCR       0000004
#define OCRNL       0000010
#define ONOCR       0000020
#define ONLRET      0000040
#define OFILL       0000100
#define OFDEL       0000200

#define ISIG        0000001
#define ICANON      0000002
#define ECHO        0000010
#define ECHOE       0000020
#define ECHOK       0000040
#define ECHONL      0000100
#define NOFLSH      0000200
#define TOSTOP      0000400
#define IEXTEN      0100000

/* tcflow() and TCXONC use these */
#define TCOOFF      0
#define TCOON       1
#define TCIOFF      2
#define TCION       3

/* tcflush() and TCFLSH use these */
#define TCIFLUSH    0
#define TCOFLUSH    1
#define TCIOFLUSH   2

/* tcsetattr uses these */
#define TCSANOW     0
#define TCSADRAIN   1
#define TCSAFLUSH   2

#define NCCS        32
#define VINTR       0
#define VQUIT       1
#define VERASE      2
#define VKILL       3
#define VEOF        4
#define VTIME       5
#define VMIN        6
#define VSWTC       7
#define VSTART      8
#define VSTOP       9
#define VSUSP       10
#define VEOL        11
#define VREPRINT    12
#define VDISCARD    13
#define VWERASE     14
#define VLNEXT      15
#define VEOL2       16

struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_cc[NCCS];
    speed_t c_ispeed;
    speed_t c_cspeed;
};

int tcgetattr(int fd, struct termios *termios);
int tcsetattr(int fd, int optional_actions, const struct termios *termios);

#ifdef __cplusplus
}
#endif

#endif
