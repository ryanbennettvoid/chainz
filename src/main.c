
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/block.h"

chainz_block_t*
append_block(char* data, chainz_block_t** tail)
{
  char* str = strdup(data);
  str[(size_t)strlen(str) - 1] = '\0'; // remove new line ending
  chainz_block_t* block = chainz_block_create(str, *tail);
  *tail = block;
  return block;
}

int
main(int argc, char** argv)
{

  chainz_block_t *genesis, *tail;
  genesis = chainz_block_create("initial block", NULL);
  tail = genesis;

  char* data = NULL;
  size_t len;
  while (getline(&data, &len, stdin) != EOF) {
    chainz_block_t* block = append_block(data, &tail);
    chainz_block_print(block);
    putchar('\n');
  }

  free(data);

  return 0;
}