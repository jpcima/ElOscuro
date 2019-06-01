/*
 * File:   HashTable.h
 * Author: Steven LeVesque
 *
 * Created on March 13, 2018, 5:10 PM
 */

#pragma once

#include <stdint.h>

typedef struct listNode
{
    int32_t isAvaliable;
    int32_t key;
    int32_t data;
} listNode;

typedef struct HashTable
{
    int32_t totalSize;
    listNode** table;
} HashTable;

void ClearHashTable (HashTable*);
void Delete(HashTable*, int32_t);
void InitHashTable(HashTable*, int32_t);
void Insert(HashTable*, int32_t, int32_t);
int32_t Lookup(HashTable*, int32_t);
