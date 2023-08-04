#include "usb_interface.h"

void usb_interface::add_endpoint(usb_endpoint_interface & ep) {
    int i=0;
    for (i=0; i < 5; ++i) {
        if (!_endpoints[i]) {
            _endpoints[i] = &ep;
            break;
        }
    }
    assert(i != 5);
    descriptor.bNumEndpoints = i+1;
}
