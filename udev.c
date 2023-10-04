#include <iostream>
#include <libudev.h>
#include <stdio.h>
#include <string.h> 
int main() {
    struct udev *udev = udev_new();
    if (!udev) {
        std::cerr << "Udev başlatılamadı!" << std::endl;
        return 1;
    }

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "input");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *device = udev_device_new_from_syspath(udev, path);
        const char *devnode = udev_device_get_devnode(device);
        const char *subsystem = udev_device_get_subsystem(device);

        if (devnode && subsystem && strcmp(subsystem, "input") == 0) {
            std::cout << "Klavye giriş alanı: " << devnode << std::endl;
        }

        udev_device_unref(device);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return 0;
}

