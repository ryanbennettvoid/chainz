
#include <stdio.h>

#include "../include/block.h"

int
main()
{

  for (int i = 0; i < 20; i++) {
    char data[32];
    sprintf(data, "this is my fake data %d", i);
    chainz_block_t* testblock = chainz_block_create(data);
    putchar('\n');
    chainz_block_print(testblock);
    chainz_block_destroy(testblock);
  }

  return 0;
}