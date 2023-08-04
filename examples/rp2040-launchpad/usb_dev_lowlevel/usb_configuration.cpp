#include "usb_configuration.h"

void usb_configuration::add_interface(usb_interface & interface) {
    int i=0;
    for (i=0; i < 5; ++i) {
        if (!_interfaces[i]) {
            _interfaces[i] = &interface;
            break;
        }
    }
    assert(i != 5);
    descriptor.bNumInterfaces = i+1;
    descriptor.wTotalLength   = sizeof(usb_configuration_descriptor) +
                                sizeof(usb_interface_descriptor) * descriptor.bNumInterfaces +
                                sizeof(usb_endpoint_descriptor)  * interface.descriptor.bNumEndpoints;
}
    
