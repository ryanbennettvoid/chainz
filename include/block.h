#ifndef BLOCK_H
#define BLOCK_H

#include <stdbool.h>
#include <stddef.h>

static const int MAX_DATA_SIZE = 1024;

typedef struct chainz_block_t chainz_block_t;

struct chainz_block_t
{
  int index;
  chainz_block_t* prev_block;
  unsigned long long timestamp;
  char* data;
  char* hash;
};

chainz_block_t*
chainz_block_create(char* data, chainz_block_t* prev_block);

void
chainz_block_destroy(chainz_block_t* block);

char*
chainz_make_hash(chainz_block_t* block);

bool
chainz_block_verify(chainz_block_t* block);

void
chainz_block_print(chainz_block_t* block);

unsigned long long
get_time_milliseconds();

#endif