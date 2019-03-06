
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/block.h"

int
main(int argc, char** argv)
{

  chainz_block_t *genesis, *tail;
  genesis = chainz_block_create("initial block", NULL);
  tail = genesis;

  char* data;

  for (int i = 0; i < 3; i++) {
    data = malloc(sizeof(char) * MAX_DATA_SIZE);
    snprintf(data, MAX_DATA_SIZE, "this is my fake data %d", i);
    data = realloc(data, strlen(data) + 1);
    chainz_block_t* block = chainz_block_create(data, tail);
    block->prev_block = tail;
    tail = block;
  }

  {
    chainz_block_t* cursor = tail;
    do {
      chainz_block_print(cursor);
      bool verified = chainz_block_verify(cursor);
      assert(verified);
      printf("block verified: %s\n\n", cursor->hash);
    } while ((cursor = cursor->prev_block));
  }

  printf("-------------\n\n");

  {
    chainz_block_t* cursor = tail;
    int old_index = cursor->index;
    char* old_hash = cursor->hash;
    char* old_data = cursor->data;
    unsigned long long old_timestamp = cursor->timestamp;
    // fail if bad index
    {
      cursor->index = 52;
      printf("placed bad index...\n");
      chainz_block_print(cursor);
      bool verified = chainz_block_verify(cursor);
      assert(verified == false);
      printf("block verification FAILED as expected: %s\n\n", cursor->hash);
    }
    // restore
    {
      cursor->index = old_index;
      printf("restored good index...\n");
      bool verified = chainz_block_verify(cursor);
      assert(verified);
      printf("block verified: %s\n\n", cursor->hash);
    }
    // fail if bad hash
    {
      cursor->hash = "bad hash";
      printf("placed bad hash...\n");
      chainz_block_print(cursor);
      bool verified = chainz_block_verify(cursor);
      assert(verified == false);
      printf("block verification FAILED as expected: %s\n\n", cursor->hash);
    }
    // restore
    {
      cursor->hash = old_hash;
      printf("restored good hash...\n");
      bool verified = chainz_block_verify(cursor);
      assert(verified);
      printf("block verified: %s\n\n", cursor->hash);
    }
    // fail if bad data
    {
      cursor->data = "bad hash";
      printf("placed bad data...\n");
      chainz_block_print(cursor);
      bool verified = chainz_block_verify(cursor);
      assert(verified == false);
      printf("block verification FAILED as expected: %s\n\n", cursor->hash);
    }
    // restore
    {
      cursor->data = old_data;
      printf("restored good data...\n");
      bool verified = chainz_block_verify(cursor);
      assert(verified);
      printf("block verified: %s\n\n", cursor->hash);
    }
    // fail if bad timestamp
    {
      cursor->timestamp = 8000;
      printf("placed bad timestamp...\n");
      chainz_block_print(cursor);
      bool verified = chainz_block_verify(cursor);
      assert(verified == false);
      printf("block verification FAILED as expected: %s\n\n", cursor->hash);
    }
    // restore
    {
      cursor->timestamp = old_timestamp;
      printf("restored good timestamp...\n");
      bool verified = chainz_block_verify(cursor);
      assert(verified);
      printf("block verified: %s\n\n", cursor->hash);
    }
  }

  return 0;
}