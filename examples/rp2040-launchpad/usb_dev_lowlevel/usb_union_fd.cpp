//
// Created by andreas on 13.08.23.
//

#include "usb_union_fd.h"

usb_union_fd::usb_union_fd()
        : usb_functional_descriptor((uint8_t *)&descriptor,
                                    sizeof(descriptor) )
{
    descriptor.bLength              = sizeof(descriptor);
    descriptor.bDescriptorType      = USB::CDC::func_desc_type_t::CS_INTERFACE;
    descriptor.bDescriptorSubType   = USB::CDC::func_desc_subtype_t::CDC_FUNC_DESC_UNION;
}
