//
// Created by andreas on 15.05.25.
//

#ifndef MFM_ERRORS_H
#define MFM_ERRORS_H

#include <cstdint>

namespace MFM {
    static const int WORKING            =  0;
    static const int FINISHED           =  1;
    static const int ERROR_SYNC         = -1;
    static const int ERROR_READ_TAG     = -2;
    static const int ERROR_NOT_FOUND    = -3;
}

#endif // MFM_ERRORS_H
