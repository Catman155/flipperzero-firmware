#include "protocol_fdxb.h"
#include <furi.h>

const fdxbCountryMapping_t ProtocolFdxB::fdxbCountryMapping[] = {
    { 4, "AFG" },
    { 8, "ALB" },
    { 12, "DZA" },
    { 16, "ASM" },
    { 20, "AND" },
    { 24, "AGO" },
    { 660, "AIA" },
    { 10, "ATA" },
    { 28, "ATG" },
    { 32, "ARG" },
    { 51, "ARM" },
    { 533, "ABW" },
    { 36, "AUS" },
    { 40, "AUT" },
    { 31, "AZE" },
    { 44, "BHS" },
    { 48, "BHR" },
    { 50, "BGD" },
    { 52, "BRB" },
    { 112, "BLR" },
    { 56, "BEL" },
    { 84, "BLZ" },
    { 204, "BEN" },
    { 60, "BMU" },
    { 64, "BTN" },
    { 68, "BOL" },
    { 68, "BOL" },
    { 70, "BIH" },
    { 72, "BWA" },
    { 74, "BVT" },
    { 76, "BRA" },
    { 86, "IOT" },
    { 96, "BRN" },
    { 96, "BRN" },
    { 100, "BGR" },
    { 854, "BFA" },
    { 108, "BDI" },
    { 116, "KHM" },
    { 120, "CMR" },
    { 124, "CAN" },
    { 132, "CPV" },
    { 136, "CYM" },
    { 140, "CAF" },
    { 148, "TCD" },
    { 152, "CHL" },
    { 156, "CHN" },
    { 162, "CXR" },
    { 166, "CCK" },
    { 170, "COL" },
    { 174, "COM" },
    { 178, "COG" },
    { 180, "COD" },
    { 184, "COK" },
    { 188, "CRI" },
    { 384, "CIV" },
    { 384, "CIV" },
    { 191, "HRV" },
    { 192, "CUB" },
    { 196, "CYP" },
    { 203, "CZE" },
    { 208, "DNK" },
    { 262, "DJI" },
    { 212, "DMA" },
    { 214, "DOM" },
    { 218, "ECU" },
    { 818, "EGY" },
    { 222, "SLV" },
    { 226, "GNQ" },
    { 232, "ERI" },
    { 233, "EST" },
    { 231, "ETH" },
    { 238, "FLK" },
    { 234, "FRO" },
    { 242, "FJI" },
    { 246, "FIN" },
    { 250, "FRA" },
    { 254, "GUF" },
    { 258, "PYF" },
    { 260, "ATF" },
    { 266, "GAB" },
    { 270, "GMB" },
    { 268, "GEO" },
    { 276, "DEU" },
    { 288, "GHA" },
    { 292, "GIB" },
    { 300, "GRC" },
    { 304, "GRL" },
    { 308, "GRD" },
    { 312, "GLP" },
    { 316, "GUM" },
    { 320, "GTM" },
    { 831, "GGY" },
    { 324, "GIN" },
    { 624, "GNB" },
    { 328, "GUY" },
    { 332, "HTI" },
    { 334, "HMD" },
    { 336, "VAT" },
    { 340, "HND" },
    { 344, "HKG" },
    { 348, "HUN" },
    { 352, "ISL" },
    { 356, "IND" },
    { 360, "IDN" },
    { 364, "IRN" },
    { 368, "IRQ" },
    { 372, "IRL" },
    { 833, "IMN" },
    { 376, "ISR" },
    { 380, "ITA" },
    { 388, "JAM" },
    { 392, "JPN" },
    { 832, "JEY" },
    { 400, "JOR" },
    { 398, "KAZ" },
    { 404, "KEN" },
    { 296, "KIR" },
    { 408, "PRK" },
    { 410, "KOR" },
    { 410, "KOR" },
    { 414, "KWT" },
    { 417, "KGZ" },
    { 418, "LAO" },
    { 428, "LVA" },
    { 422, "LBN" },
    { 426, "LSO" },
    { 430, "LBR" },
    { 434, "LBY" },
    { 434, "LBY" },
    { 438, "LIE" },
    { 440, "LTU" },
    { 442, "LUX" },
    { 446, "MAC" },
    { 807, "MKD" },
    { 450, "MDG" },
    { 454, "MWI" },
    { 458, "MYS" },
    { 462, "MDV" },
    { 466, "MLI" },
    { 470, "MLT" },
    { 584, "MHL" },
    { 474, "MTQ" },
    { 478, "MRT" },
    { 480, "MUS" },
    { 175, "MYT" },
    { 484, "MEX" },
    { 583, "FSM" },
    { 498, "MDA" },
    { 492, "MCO" },
    { 496, "MNG" },
    { 499, "MNE" },
    { 500, "MSR" },
    { 504, "MAR" },
    { 508, "MOZ" },
    { 104, "MMR" },
    { 104, "MMR" },
    { 516, "NAM" },
    { 520, "NRU" },
    { 524, "NPL" },
    { 528, "NLD" },
    { 530, "ANT" },
    { 540, "NCL" },
    { 554, "NZL" },
    { 558, "NIC" },
    { 562, "NER" },
    { 566, "NGA" },
    { 570, "NIU" },
    { 574, "NFK" },
    { 580, "MNP" },
    { 578, "NOR" },
    { 512, "OMN" },
    { 586, "PAK" },
    { 585, "PLW" },
    { 275, "PSE" },
    { 591, "PAN" },
    { 598, "PNG" },
    { 600, "PRY" },
    { 604, "PER" },
    { 608, "PHL" },
    { 612, "PCN" },
    { 616, "POL" },
    { 620, "PRT" },
    { 630, "PRI" },
    { 634, "QAT" },
    { 638, "REU" },
    { 642, "ROU" },
    { 643, "RUS" },
    { 643, "RUS" },
    { 646, "RWA" },
    { 654, "SHN" },
    { 659, "KNA" },
    { 662, "LCA" },
    { 666, "SPM" },
    { 670, "VCT" },
    { 670, "VCT" },
    { 670, "VCT" },
    { 882, "WSM" },
    { 674, "SMR" },
    { 678, "STP" },
    { 682, "SAU" },
    { 686, "SEN" },
    { 688, "SRB" },
    { 690, "SYC" },
    { 694, "SLE" },
    { 702, "SGP" },
    { 703, "SVK" },
    { 705, "SVN" },
    { 90, "SLB" },
    { 706, "SOM" },
    { 710, "ZAF" },
    { 239, "SGS" },
    { 728, "SSD" },
    { 724, "ESP" },
    { 144, "LKA" },
    { 736, "SDN" },
    { 740, "SUR" },
    { 744, "SJM" },
    { 748, "SWZ" },
    { 752, "SWE" },
    { 756, "CHE" },
    { 760, "SYR" },
    { 158, "TWN" },
    { 158, "TWN" },
    { 762, "TJK" },
    { 834, "TZA" },
    { 764, "THA" },
    { 626, "TLS" },
    { 768, "TGO" },
    { 772, "TKL" },
    { 776, "TON" },
    { 780, "TTO" },
    { 788, "TUN" },
    { 792, "TUR" },
    { 795, "TKM" },
    { 796, "TCA" },
    { 798, "TUV" },
    { 800, "UGA" },
    { 804, "UKR" },
    { 784, "ARE" },
    { 826, "GBR" },
    { 840, "USA" },
    { 581, "UMI" },
    { 858, "URY" },
    { 860, "UZB" },
    { 548, "VUT" },
    { 862, "VEN" },
    { 862, "VEN" },
    { 704, "VNM" },
    { 704, "VNM" },
    { 92, "VGB" },
    { 850, "VIR" },
    { 876, "WLF" },
    { 732, "ESH" },
    { 887, "YEM" },
    { 894, "ZMB" },
    { 716, "ZWE" },
    { 0,   "N/A" } // must be the last entry
};

const char* ProtocolFdxB::mapFDBX(uint16_t countryCode) {
    uint16_t i = 0;
    while (ProtocolFdxB::fdxbCountryMapping[i].code > 0) {
        if (countryCode == ProtocolFdxB::fdxbCountryMapping[i].code) {
            return ProtocolFdxB::fdxbCountryMapping[i].desc;
        }
        i++;
    }
    return ProtocolFdxB::fdxbCountryMapping[i].desc;
}

uint8_t ProtocolFdxB::get_encoded_data_size() {
    return FDX_B_ENCODED_BYTE_FULL_SIZE;
}

uint8_t ProtocolFdxB::get_decoded_data_size() {
    return 8;
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
