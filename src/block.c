
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/block.h"

static const int HASH_SIZE = 16;
static const char* CHARSET = "abcdef0123456789";

struct chainz_block_t
{
  int index;
  unsigned long long timestamp;
  char* data;
  char* hash;
  chainz_block_t* last_block;
};

chainz_block_t*
chainz_block_create(char* data)
{
  chainz_block_t* block = malloc(sizeof(chainz_block_t));
  memset(block, 0, sizeof(chainz_block_t));
  static int chain_index = 0;
  block->index = chain_index++;
  block->timestamp = get_time_milliseconds();
  block->data = data;
  block->hash = chainz_make_hash(block);
  return block;
}

void
chainz_block_destroy(chainz_block_t* block)
{
  free(block);
}

char*
chainz_make_hash(chainz_block_t* block)
{
  assert(block && block->data);
  char* hash = malloc(sizeof(char) * HASH_SIZE);
  memset(hash, 1, sizeof(char) * HASH_SIZE);

  int data_size = strlen(block->data);
  int charset_size = strlen(CHARSET);

  // more iterations as blockchain grows in size
  float growth_factor = 1 + ((1 + block->index) * 0.01);
  unsigned long long iterations = (block->timestamp / 100000) * growth_factor;
  printf("%llu\n", iterations);

  char* p = block->data;
  int c;
  int newchar_index;
  char newchar;
  char hash_char;
  int hash_index = 0;
  int counter = 0;
  while (counter++ < iterations) {
    c = block->data[counter % data_size];
    hash_index = counter % HASH_SIZE;
    hash_char = hash[hash_index];
    newchar_index = ((c << 3) + hash_char) % charset_size;
    newchar = CHARSET[newchar_index];
    hash[hash_index] = newchar;
  }

  return hash;
}

void
chainz_block_print(chainz_block_t* block)
{
  assert(block);
  printf("index: %d\n", block->index);
  printf("timestamp: %llu\n", block->timestamp);
  printf("data: %s\n", block->data);
  printf("hash: %s\n", block->hash);
}

unsigned long long
get_time_milliseconds()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long long)(tv.tv_sec) * 1000 +
         (unsigned long long)(tv.tv_usec) / 1000;
}