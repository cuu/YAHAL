#include <string>
#include <vector>
using namespace std;

// This data structure stores all relevant
// information for one specific register.
struct register_info_t {
    string          type;               // Type of register
    string          name;               // Name of register
    uint32_t        size        {0};    // Size of register in bytes
    uint32_t        dim         {0};    // Dimension (array if > 1)
    uint32_t        dimInc      {0};    // Increment for dim elements in bytes
    bool            userIndex   {false};// User-defined Index names
    vector<string>  dimIndices;         // Specific index names
    uint32_t        offset      {0};    // Offset from base address in bytes
};

// registerInfo stores a vector of register_info_t
class registerInfo : public vector<register_info_t> {
public:
    // Check if there are register left to process.
    // For simple register, dim will be initially 1,
    // and after processing it will be decremented.
    // dim == 0 is a sign that the complete register
    // (also arrays) have been processed.
    bool registers_left() {
        for (auto & e : *this) {
            if(e.dim > 0) return true;
        }
        return false;
    }

    // Find the next register to be processed.
    // This method looks for the smallest offset
    // in all unprocessed (dim > 0) registers.
    register_info_t * next_register() {
        uint32_t min = 0xffffffff;
        register_info_t * res = nullptr;
        for (auto & e : *this) {
            if ((e.dim > 0) && (e.offset < min)) {
                min = e.offset;
                res = &e;
            }
        }
        return res;
    }
};
