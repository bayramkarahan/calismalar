#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;
bool drm=false;
static
struct udev_device*
get_child(struct udev* udev, struct udev_device* parent, const char* subsystem) {
  struct udev_device* child = NULL;
  struct udev_enumerate *enumerate = udev_enumerate_new(udev);

  udev_enumerate_add_match_parent(enumerate, parent);
  udev_enumerate_add_match_subsystem(enumerate, subsystem);
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry *entry;

  udev_list_entry_foreach(entry, devices) {
      const char *path = udev_list_entry_get_name(entry);
      child = udev_device_new_from_syspath(udev, path);
      break;
  }

  udev_enumerate_unref(enumerate);
  return child;
}

static void enumerate_usb_mass_storage(struct udev* udev) {
  struct udev_enumerate* enumerate = udev_enumerate_new(udev);

  udev_enumerate_add_match_subsystem(enumerate, "scsi");
  udev_enumerate_add_match_property(enumerate, "DEVTYPE", "scsi_device");
  udev_enumerate_scan_devices(enumerate);

  struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
  struct udev_list_entry *entry;

  udev_list_entry_foreach(entry, devices) {
      const char* path = udev_list_entry_get_name(entry);
      struct udev_device* scsi = udev_device_new_from_syspath(udev, path);

      struct udev_device* block = get_child(udev, scsi, "block");
      struct udev_device* scsi_disk = get_child(udev, scsi, "scsi_disk");

      struct udev_device* usb
          = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

      if (block && scsi_disk && usb) {
          printf("block = %s, usb = %s:%s, scsi = %s, name = %s, size = %s, x = %i, x = %s, x = %s\n",
                 udev_device_get_devnode(block),
                 udev_device_get_sysattr_value(usb, "idVendor"),
                 udev_device_get_sysattr_value(usb, "idProduct"),
                 udev_device_get_sysattr_value(scsi, "vendor"),
udev_device_get_sysattr_value(usb, "udev"),
udev_device_get_sysattr_value(usb, "udev_root"),
udev_device_get_sysattr_value(usb, "size"),
udev_device_get_sysattr_value(usb, "speed"),
udev_device_get_sysattr_value(usb, "bMaxPower"));

      }

      if (block) {
          udev_device_unref(block);
      }

      if (scsi_disk) {
          udev_device_unref(scsi_disk);
      }
      udev_device_unref(scsi);
  }

  udev_enumerate_unref(enumerate);
}

int main(){


    struct udev* udev = udev_new();
    enumerate_usb_mass_storage(udev);


    struct udev_device *dev;
    struct udev_monitor *mon;
    int fd;

    mon = udev_monitor_new_from_netlink(udev, "udev");
    udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
    udev_monitor_enable_receiving(mon);
    fd = udev_monitor_get_fd(mon);

    while (1) {

        fd_set fds;
        struct timeval tv;
        int ret;

        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        ret = select(fd+1, &fds, NULL, NULL, &tv);

        /* Check if our file descriptor has received data. */
        if (ret > 0 && FD_ISSET(fd, &fds))
        {
            printf("\nselect() says there should be data\n");

            dev = udev_monitor_receive_device(mon);
            if (dev) {
                printf("Got Device\n");
                printf("   Node: %s\n", udev_device_get_devnode(dev));
                printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));
                printf("   Devtype: %s\n", udev_device_get_devtype(dev));
                printf("   Action: %s\n", udev_device_get_action(dev));
                ///cout << udev_get_run_path (dev) << endl;

                if( strcmp(udev_device_get_action(dev),"add")==0 ) 
                {
                drm=true;
                cout << "conectat" << endl;
                } 
                
                 if( strcmp(udev_device_get_action(dev),"change")==0&&(drm==true) ) 
                {
                drm=false;
                cout << "eklendi ve bağlandı" << endl;
                } 
                
                udev_device_unref(dev);
            }
            else {
                printf("No Device from receive_device(). An error occured.\n");
            }                   
        }
        usleep(250*1000);
        fflush(stdout);
    }




  udev_unref(udev);
  return 0;
}
