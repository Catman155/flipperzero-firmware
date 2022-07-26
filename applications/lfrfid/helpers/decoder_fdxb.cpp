#include "decoder_fdxb.h"
#include <furi.h>
#include <furi_hal.h>

#define FDX_B_CLOCKS_IN_US (64)
#define FDX_B_SHORT_TIME (128 * FDX_B_CLOCKS_IN_US)
#define FDX_B_LONG_TIME (256 * FDX_B_CLOCKS_IN_US)
#define FDX_B_JITTER_TIME (50 * FDX_B_CLOCKS_IN_US)

#define FDX_B_SHORT_TIME_LOW (FDX_B_SHORT_TIME - FDX_B_JITTER_TIME)
#define FDX_B_SHORT_TIME_HIGH (FDX_B_SHORT_TIME + FDX_B_JITTER_TIME)
#define FDX_B_LONG_TIME_LOW (FDX_B_LONG_TIME - FDX_B_JITTER_TIME)
#define FDX_B_LONG_TIME_HIGH (FDX_B_LONG_TIME + FDX_B_JITTER_TIME)

void DecoderFdxB::reset_state() {
    ready = false;
    read_data = 0;
    last_short = false;
}

bool DecoderFdxB::read(uint8_t* data, uint8_t data_size) {
    bool result = false;

    if(ready) {
        fdxb.decode(read_data, FDX_B_ENCODED_BYTE_FULL_SIZE, data, data_size);
        result = true;
        ready = false;
    }

    return result;
}

void DecoderFdxB::process_front(bool polarity, uint32_t time) {
    if(ready) return;

    UNUSED(polarity);
    UNUSED(time);

    bool pushed = false;

    // Bi-Phase Manchester decoding
    if(time >= FDX_B_SHORT_TIME_LOW && time <= FDX_B_SHORT_TIME_HIGH) {
        if(last_short == false) {
            last_short = true;
        } else {
            pushed = true;
            bit_lib_push_bit(read_data, FDX_B_ENCODED_BYTE_FULL_SIZE, false);
            last_short = false;
        }
    } else if(time >= FDX_B_LONG_TIME_LOW && time <= FDX_B_LONG_TIME_HIGH) {
        if(last_short == false) {
            pushed = true;
            bit_lib_push_bit(read_data, FDX_B_ENCODED_BYTE_FULL_SIZE, true);
        } else {
            // reset
            last_short = false;
        }
    } else {
        // reset
        last_short = false;
    }

    if(pushed && fdxb.can_be_decoded(reinterpret_cast<const uint8_t*>(read_data), FDX_B_ENCODED_BYTE_FULL_SIZE)) {
        ready = true;
    }
}

DecoderFdxB::DecoderFdxB() {
    reset_state();
    read_data = reinterpret_cast<uint8_t*>(calloc(FDX_B_ENCODED_BYTE_FULL_SIZE, sizeof(uint8_t)));
    furi_check(read_data);
}

DecoderFdxB::~DecoderFdxB() {
    free(read_data);
}
