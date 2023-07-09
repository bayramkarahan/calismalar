#include <fcntl.h>
#include <unistd.h>
#include <cerrno> 
#include <cstring>
#include <iostream>
#include <iostream>
#include <parted/parted.h>
#include <parted/device.h>
int main() {
    PedDevice* device = ped_device_get("/dev/sdb");
    PedDisk* disk = ped_disk_new(device);

    PedPartition* partition1 = ped_partition_new(disk, PED_PARTITION_NORMAL,NULL, 0, 5);
    PedPartition* partition2 = ped_partition_new(disk, PED_PARTITION_NORMAL,NULL, 6, 10);

    ped_disk_commit(disk);

    std::cout << "İki bölüm başarıyla oluşturuldu." << std::endl;

    ped_partition_destroy(partition1);
    ped_partition_destroy(partition2);
    ped_disk_destroy(disk);
    ped_device_destroy(device);

    return 0;
}
