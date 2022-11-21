#include <stdint.h>
#pragma once

#define BIGBAG_MAGIC 0xC5149
#define BIGBAG_FREE_ENTRY_MAGIC 0xF4
#define BIGBAG_USED_ENTRY_MAGIC 0xDA

// bag files will always be 64K in size
#define BIGBAG_SIZE (64*1024)

#pragma pack(1)
struct bigbag_hdr_s {
    uint32_t magic;
    // these offsets are from the beginning of the bagfile or 0 if not set
    uint32_t first_free;// if no more free, first free will be zero
    uint32_t first_element;
};

struct bigbag_entry_s {
    uint32_t next;
    uint8_t entry_magic;
    uint16_t entry_len; // does not include sizeof bigbag_entry_s
    char str[0];
};
#pragma pack()

#define MIN_ENTRY_SIZE (sizeof(struct bigbag_entry_s) + 4)
