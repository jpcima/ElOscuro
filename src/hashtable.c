#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

void
InitHashTable (HashTable * hashTable, int32_t initSize)
{
  hashTable->totalSize = initSize;

  hashTable->table = calloc (sizeof (listNode), initSize);

  listNode *emptyNode = malloc (sizeof (listNode));

  emptyNode->isAvaliable = 1;

  emptyNode->key = -1;
  emptyNode->data = -1;

  for (int32_t x = 0; x < initSize; ++x)
  {
    listNode* node = malloc (sizeof (listNode));

    memcpy (node, emptyNode, sizeof (&emptyNode));

    hashTable->table[x] = node;
  }
}

static int32_t
HashFunc (HashTable * hashTable, int32_t key)
{
  return abs ((key)) % hashTable->totalSize;
}

void
Delete (HashTable * hashTable, int32_t key)
{
  int32_t index = HashFunc (hashTable, key);

  while (hashTable->table[index]->key != key)
  {
    //go to next cell
    ++index;

    //wrap around the table
    index %= hashTable->totalSize;
  }

  hashTable->table[index]->isAvaliable = 1;
}

void
ClearHashTable (HashTable* hashTable)
{
  for (int32_t x = 0; x < ARRAY_SIZE (hashTable->table); ++x)
  {
    if (hashTable->table[x])
    {
      free (hashTable->table[x]);
    }
  }
  free (hashTable->table);
}

void
Insert (HashTable* hashTable, int32_t key, int32_t item)
{
  int32_t index = HashFunc (hashTable, key);

  while (!hashTable->table[index]->isAvaliable)
  {
    //go to next cell
    ++index;

    //wrap around the table
    index %= hashTable->totalSize;
  }

  hashTable->table[index]->data = item;
  hashTable->table[index]->key = key;
  hashTable->table[index]->isAvaliable = 0;
}

int32_t
Lookup (HashTable* hashTable, int32_t key)
{
  int32_t index = HashFunc (hashTable, key);

  int32_t origIndex = index;

  while (hashTable->table[index]->key != key && !hashTable->table[index]->isAvaliable)
  {
    //go to next cell
    ++index;

    //wrap around the table
    index %= hashTable->totalSize;

    if (index == origIndex)
    {
      return 0;
    }
  }

  return hashTable->table[index]->data;
}
