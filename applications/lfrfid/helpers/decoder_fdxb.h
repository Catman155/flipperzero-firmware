#pragma once
#include <stdint.h>
#include <atomic>
#include "protocols/protocol_fdxb.h"

class DecoderFdxB {
public:
    bool read(uint8_t* data, uint8_t data_size);
    void process_front(bool polarity, uint32_t time);
    void reset_state();
    DecoderFdxB();
    ~DecoderFdxB();
private:

    uint8_t* read_data;

    std::atomic<bool> ready;
    std::atomic<bool> last_short;

    ProtocolFdxB fdxb;
};
