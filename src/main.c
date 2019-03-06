
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/block.h"

int
main()
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

  {
    chainz_block_t* cursor = tail;
    cursor->hash = "bad hash";
    printf("placed bad hash...\n");
    chainz_block_print(cursor);
    bool verified = chainz_block_verify(cursor);
    assert(verified == false);
    printf("block verification FAILED: %s\n\n", cursor->hash);
  }

  return 0;
}