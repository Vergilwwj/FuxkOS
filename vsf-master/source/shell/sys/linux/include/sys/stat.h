#ifndef __VSF_LINUX_STAT_H__
#define __VSF_LINUX_STAT_H__

#include "shell/sys/linux/vsf_linux_cfg.h"

#if VSF_LINUX_CFG_RELATIVE_PATH == ENABLED
#   include "../sys/types.h"
#   include "../simple_libc/time.h"
#else
#   include <sys/types.h>
#   include <time.h>
#endif

// for fs constants
#include "component/vsf_component.h"

#ifdef __cplusplus
extern "C" {
#endif

#if VSF_LINUX_CFG_WRAPPER == ENABLED
#define stat            VSF_LINUX_WRAPPER(stat)
#define fstat           VSF_LINUX_WRAPPER(fstat)
#endif

#define S_IFDIR         VSF_FILE_ATTR_DIRECTORY
#define S_IFREG         (VSF_FILE_ATTR_USER << 0)
#define S_IFLNK         (VSF_FILE_ATTR_USER << 8)
#define S_IFIFO         (VSF_FILE_ATTR_USER << 9)
#define S_IFSOCK        (VSF_FILE_ATTR_USER << 10)
#define S_IFMT          (S_IFDIR | S_IFREG | S_IFLNK | S_IFIFO | S_IFSOCK)

#define S_IRUSR         (VSF_FILE_ATTR_USER << 1)
#define S_IWUSR         (VSF_FILE_ATTR_USER << 2)
#define S_IXUSR         (VSF_FILE_ATTR_USER << 3)
#define S_IRGRP         (VSF_FILE_ATTR_USER << 4)
#define S_IWGRP         (VSF_FILE_ATTR_USER << 5)

#define S_ISLNK(__MODE) (((__MODE) & S_IFMT) == S_IFLNK)
#define S_ISREG(__MODE) (((__MODE) & S_IFMT) == S_IFREG)
#define S_ISDIR(__MODE) (((__MODE) & S_IFMT) == S_IFDIR)
#define S_ISFIFO(__MODE)(((__MODE) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(__MODE)(((__MODE) & S_IFMT) == S_IFSOCK)

struct stat {
    mode_t      st_mode;
    off_t       st_size;
    time_t      st_atime;
    time_t      st_mtime;
    time_t      st_ctime;
};

int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);

#ifdef __cplusplus
}
#endif

#endif
