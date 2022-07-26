#pragma once
#include "protocol_generic.h"
#include "../bit_lib.h"

#define FDX_B_ENCODED_BIT_SIZE (128)
#define FDX_B_ENCODED_BYTE_SIZE (((FDX_B_ENCODED_BIT_SIZE) / 8))
#define FDX_B_PREAMBLE_BIT_SIZE (11)
#define FDX_B_PREAMBLE_BYTE_SIZE (2)
#define FDX_B_ENCODED_BYTE_FULL_SIZE (FDX_B_ENCODED_BYTE_SIZE + FDX_B_PREAMBLE_BYTE_SIZE)

#define FLAG_ANIMAL_USE (1 << 0)
#define FLAG_BLOCK (1 << 1)
#define FLAG_RUDI (1 << 2)


class ProtocolFdxB : public ProtocolGeneric {
public:
    uint8_t get_encoded_data_size() final;
    uint8_t get_decoded_data_size() final;

    void encode(
        const uint8_t* decoded_data,
        const uint8_t decoded_data_size,
        uint8_t* encoded_data,
        const uint8_t encoded_data_size) final;

    void decode(
        const uint8_t* encoded_data,
        const uint8_t encoded_data_size,
        uint8_t* decoded_data,
        const uint8_t decoded_data_size) final;

    bool can_be_decoded(const uint8_t* encoded_data, const uint8_t encoded_data_size) final;
};
