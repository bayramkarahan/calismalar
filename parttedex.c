#include <fcntl.h>
#include <unistd.h>
#include <parted/parted.h>
#include <cerrno> 
#include <cstring>
#include <iostream>

void find()
{
  PedDevice* pdev = ped_device_get("/dev/sda");
}

void Out(const std::string& S, int R)
{
  std::cout << S << "\t" << R << "\t" << std::strerror(errno) << std::endl;
}

int main()
{
  int fd = open("/dev/sda1", O_RDWR);
  Out("Opening  ", fd);
  int res = close(fd);
  Out("Closing  ", res);
}
