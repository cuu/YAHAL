#include "dma_msp432.h"
#include "msp.h"

dma_msp432 dma_msp432::_inst;

dma_msp432::dma_msp432() {
    DMA_Control->CTLBASE = (uint32_t)ctrl_data;
}

dma_msp432 & dma_msp432::inst() {
    return _inst;
}
