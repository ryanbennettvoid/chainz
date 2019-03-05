#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>

typedef struct chainz_block_t chainz_block_t;

chainz_block_t*
chainz_block_create(char* data);

void
chainz_block_destroy(chainz_block_t* block);

char*
chainz_make_hash(chainz_block_t* block);

void
chainz_block_print(chainz_block_t* block);

unsigned long long
get_time_milliseconds();

#endif