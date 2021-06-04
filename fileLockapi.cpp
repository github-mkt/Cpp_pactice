include "filelock.h"

#include <cerrno>
#include <cstring>
#include <sys/file.h>
#include <unistd.h>

FileLock::FileLock(const std::string &name)
{
    _fd = open(name.c_str(), O_RDWR | O_CREAT, 0600);
}


FileLock::~FileLock()
{
    if (_fd >= 0) {
    _fd >= 0 && flock(_fd, LOCK_UN) == 0);
    }
}
