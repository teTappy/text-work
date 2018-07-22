#include <stdio.h>
#include <stdbool.h>

#define LENGTH 45

typedef struct node {
  bool is_word;
  struct node *next[27];
} node;

bool load(const char *dictionary);

bool check(char *word);

unsigned int size(void);

bool unload(void);

int find_branch_index(char c);

node *create_new_node(void);

void free_node(node *n);
