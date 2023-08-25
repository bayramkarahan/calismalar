#include <cstdlib>
#include <iostream>



#include <IOKit/IOKitLib.h>
#include <IOKit/IOTypes.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>


std::string get_descriptor_idx(IOUSBDeviceInterface **dev, UInt8 idx);

int main(int argc, char *argv[]) {
  
  /*
   * Get the IO registry
   */
  auto entry = IORegistryGetRootEntry(kIOMasterPortDefault);
  if (entry == 0)
    return EXIT_FAILURE;
  
  io_iterator_t iter{};
  auto kret = IORegistryEntryCreateIterator(entry, kIOUSBPlane, kIORegistryIterateRecursively, &iter);
  if (kret != KERN_SUCCESS || iter == 0)
    return EXIT_FAILURE;
  
  io_service_t  service {};
  
  std::cout << std::endl;
  
  while ((service = IOIteratorNext(iter))) {
    
    IOCFPlugInInterface  **plug  = nullptr;
    IOUSBDeviceInterface **dev   = nullptr;
    io_string_t            path;
    SInt32                 score = 0;
    IOReturn               ioret;
    
    kret = IOCreatePlugInInterfaceForService(service, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plug, &score);
    IOObjectRelease(service);
    if (kret != KERN_SUCCESS || plug == nullptr) {
      continue;
    }
    
    /*
     * USB
     */
    ioret = (*plug)->QueryInterface(plug, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID),
                                    static_cast<LPVOID *>((void *) &dev));
    (*plug)->Release(plug);
    if (ioret != kIOReturnSuccess || dev == nullptr) {
      continue;
    }
    
    if (IORegistryEntryGetPath(service, kIOServicePlane, path) != KERN_SUCCESS) {
      (*dev)->Release(dev);
      continue;
    }
    
    std::cout << "USB Path: " << path << std::endl;
    UInt8   si;
    UInt16  u16v;
  
    if ((*dev)->GetDeviceVendor(dev, &u16v) == kIOReturnSuccess)
      std::cout << "VID: "<< u16v << std::endl;
  
    if ((*dev)->GetDeviceProduct(dev, &u16v) == kIOReturnSuccess)
      std::cout << "PID: "<< u16v << std::endl;
  
    if ((*dev)->USBGetManufacturerStringIndex(dev, &si) == kIOReturnSuccess) {
      std::cout << "Manufacturer: " << get_descriptor_idx(dev, si) << std::endl;
    }
  
    if ((*dev)->USBGetProductStringIndex(dev, &si) == kIOReturnSuccess) {
      std::cout << "Product: " << get_descriptor_idx(dev, si) << std::endl;
    }
    
    (*dev)->Release(dev);
    
    std::cout << std::endl;
  }
  
  IOObjectRelease(iter);
  
  return 0;
}


/* a quick version */
std::string get_descriptor_idx(IOUSBDeviceInterface **dev, UInt8 idx)
{
  IOUSBDevRequest request;
  IOReturn        ioret;
  char            buffer[4086] = { 0 };
  CFStringRef     cfstr;
  CFIndex         len;
  
  request.bmRequestType = USBmakebmRequestType(kUSBIn, kUSBStandard, kUSBDevice);
  request.bRequest      = kUSBRqGetDescriptor;
  request.wValue        = (kUSBStringDesc << 8) | idx;
  request.wIndex        = 0x409;
  request.wLength       = sizeof(buffer);
  request.pData         = buffer;
  
  ioret = (*dev)->DeviceRequest(dev, &request);
  if (ioret != kIOReturnSuccess)
    return "n/a";
  
  if (request.wLenDone <= 2)
    return "n/a";
  
  cfstr   = CFStringCreateWithBytes(nullptr, (const UInt8 *)buffer+2, request.wLenDone-2, kCFStringEncodingUTF16LE, 0);
  len     = CFStringGetMaximumSizeForEncoding(CFStringGetLength(cfstr), kCFStringEncodingUTF8) + 1;
  if (len < 0) {
    CFRelease(cfstr);
    return "n/a";
  }
  
  std::string str; str.resize(len);
  
  CFStringGetCString(cfstr, str.data(), len, kCFStringEncodingUTF8);
  
  CFRelease(cfstr);
  return str;
}
