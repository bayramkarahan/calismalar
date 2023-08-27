#include <stdio.h>
#include <sys/statvfs.h>
#include <string_view>
#include <optional>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/mount.h>

std::optional<std::string> get_device_of_mount_point(std::string_view devicepath)
{
   std::ifstream mounts{"/proc/mounts"};
   std::string device, mountpoint, type;
   std::string line;


if (mounts.is_open()) {
    while (std::getline(mounts, line)) {
    
    std::istringstream iss(line);

    getline(iss, device, ' ');
    getline(iss, mountpoint, ' ');
    getline(iss, type, ' ');
	     if (device == devicepath)
	     {
	    	//std::cout << device << '|'<< mountpoint << '|'<< type<< std::endl;
	    	return mountpoint;
	     }
    }
    mounts.close();
}

  return std::nullopt;
}

void mountdevice()
{
system("mkdir /tmp/by");

if (mount("/dev/sdb1", "/tmp/by", "dos", MS_MGC_VAL | MS_REMOUNT | MS_NOSUID, NULL)) {
    if (errno == EBUSY) {
        printf("Mountpoint busy");
    } else {
        printf("Mount error: %s", strerror(errno));
    }
} else {
    printf("Mount successful");
}
}
int main(int argc, char **argv){
mountdevice();
//mount("/dev/sdb1", "/tmp/by", "ntfs", MS_MGC_VAL | MS_REMOUNT, "");
/* //get_device_of_mount_point("/dev/sdb1");
if (const auto point = get_device_of_mount_point("/dev/sdb1"))
   std::cout << *point << "\n";
else
   std::cout << "Not found\n";
   */
    return 0;
}
