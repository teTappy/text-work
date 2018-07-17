#include <stdio.h>
#include <stdbool.h>

#define LENGTH 45

typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

bool load(const char *dictionary);

bool check(char *word);

unsigned int size(void);

bool unload(void);
