#include "protocol_fdxb.h"
#include <furi.h>

uint8_t ProtocolFdxB::get_encoded_data_size() {
    return FDX_B_ENCODED_BYTE_FULL_SIZE;
}

uint8_t ProtocolFdxB::get_decoded_data_size() {
    return 11;
}

void ProtocolFdxB::encode(
    const uint8_t* decoded_data,
    const uint8_t decoded_data_size,
    uint8_t* encoded_data,
    const uint8_t encoded_data_size) {
    UNUSED(decoded_data);
    UNUSED(decoded_data_size);
    UNUSED(encoded_data);
    UNUSED(encoded_data_size);
}

void ProtocolFdxB::decode(
    const uint8_t* encoded_data,
    const uint8_t encoded_data_size,
    uint8_t* decoded_data,
    const uint8_t decoded_data_size) {
    UNUSED(encoded_data_size);
    UNUSED(decoded_data);
    UNUSED(decoded_data_size);
    
    // clean result
    memset(decoded_data, 0, decoded_data_size);

    uint8_t* data = reinterpret_cast<uint8_t*>(calloc(FDX_B_ENCODED_BYTE_FULL_SIZE, sizeof(uint8_t)));
    memcpy(data, encoded_data, FDX_B_ENCODED_BYTE_FULL_SIZE);

    // Remove Framing bits
    bit_lib_remove_bit_every_nth(data, 3, 13 * 9, 9);

    for(size_t i = 0; i < 11; i++)
        bit_lib_push_bit(data, FDX_B_ENCODED_BYTE_FULL_SIZE, 0);

    // 0  nnnnnnnn
    // 8  nnnnnnnn	  38 bit (12 digit) National code.
    // 16 nnnnnnnn	  eg. 000000001008 (decimal).
    // 24 nnnnnnnn
    // 32 nnnnnnnn	  10 bit (3 digit) Country code.
    // 40 cccccccc	  eg. 999 (decimal).
    // 48 s-------	  1 bit data block status flag.
    // 56 -------a	  1 bit animal application indicator.
    // 64 xxxxxxxx	  16 bit checksum.
    // 72 xxxxxxxx
    // 80 eeeeeeee	  24 bits of extra data if present.
    // 88 eeeeeeee	  eg. $123456.
    // 92 eeeeeeee

    // 10 bit of country code
    uint16_t country_code = bit_lib_get_bits_16(data, 38, 10) << 6;
    bit_lib_reverse_bits((uint8_t*)&country_code, 0, 16);
    decoded_data[0]=country_code & 0xff;
    decoded_data[1]=(country_code >> 8);

    uint64_t national_code = 0;
    for (uint8_t i = 38; i > 0; i--) {
        national_code = national_code << 1;
        if (bit_lib_get_bit(data, i-1)) national_code |= 1; 
    }

    uint64_t currentTag = country_code;
    currentTag = (currentTag<<38) + national_code; 
    memcpy(decoded_data, &currentTag, sizeof(uint64_t));

    free(data);
}

bool ProtocolFdxB::can_be_decoded(const uint8_t* encoded_data, const uint8_t encoded_data_size) {
    UNUSED(encoded_data_size);
    /*
    msb		lsb
    0   10000000000	  Header pattern. 11 bits.
    11    1nnnnnnnn	
    20    1nnnnnnnn	  38 bit (12 digit) National code.
    29    1nnnnnnnn	  eg. 000000001008 (decimal).
    38    1nnnnnnnn	
    47    1nnnnnncc	  10 bit (3 digit) Country code.
    56    1cccccccc	  eg. 999 (decimal).
    64    1s-------	  1 bit data block status flag.
    73    1-------a	  1 bit animal application indicator.
    82    1xxxxxxxx	  16 bit checksum.
    91    1xxxxxxxx	
    100   1eeeeeeee	  24 bits of extra data if present.
    109   1eeeeeeee	  eg. $123456.
    118   1eeeeeeee	
    */

    do {
        // check 11 bits preamble
        if(bit_lib_get_bits_16(encoded_data, 0, 11) != 0b10000000000) break;

        // check control bits
        if(!bit_lib_test_parity(encoded_data, 3, 13 * 9, BitLibParityAlways1, 9)) break;

        // check next 11 bits preamble
        if(bit_lib_get_bits_16(encoded_data, 128, 11) != 0b10000000000) break;

        return true;
    } while(false);

    return false;
}
