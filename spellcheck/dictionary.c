#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"


unsigned int word_count = 0;
bool is_loaded = false;
node *root;

bool load(const char *dictionary)
{
  FILE *dict_p = fopen(dictionary, "r");
  if (dict_p == NULL)
  {
    return false;
  }

  char current_word[LENGTH + 1];

  // Create root node
  root = create_new_node();
  if (root == NULL)
  {
    free(root);
    return false;
  }

  node *trav = root;
  int branch_index;

  while (fscanf(dict_p, "%s", current_word) != EOF)
  {
    for (int i = 0, len = strlen(current_word); i < len; i++)
    {
      // Find branch index : a = 0, b = 1 .... ' = 26
      branch_index = find_branch_index(current_word[i]);
      if (branch_index == -1)
      {
        printf("something went wrong finding the branch index within _load_\n");
        unload();
        return false;
      }

      if (trav->next[branch_index] == NULL)
      {
        trav->next[branch_index] = create_new_node();

        if (trav->next[branch_index] == NULL)
        {
          unload();
          return false;
        }
      }
      trav = trav->next[branch_index];
    }
    trav->is_word = true;
    trav = root;
    ++word_count;
  }

  is_loaded = true;
  fclose(dict_p);
  return true;
}

bool check(char *word)
{
  node *trav = root;
  int branch_index;

  for (int i = 0, n = strlen(word); i < n; i++)
  {
    branch_index = find_branch_index(word[i]);
    if (branch_index == -1)
    {
      printf("something went wrong finding the branch index within _check_\n");
      return false;
    }

    if (trav->next[branch_index] == NULL)
      return false;
    trav = trav->next[branch_index];
  }

  if (trav->is_word)
    return true;
  else
    return false;
}

unsigned int size(void)
{
  if (is_loaded)
    return word_count;
  else
    return 0;
}

bool unload(void)
{
  free_node(root);
  return true;
}

node *create_new_node(void)
{
  node *new = malloc(sizeof(node));

  // Assign all pointers to NULL
  for (int i = 0; i < 27; i++)
    new->next[i] = NULL;

  return new;
}

int find_branch_index(char c)
{

  if (c == '\'')
  {
    return 26;
  }
  else if (isalpha(c))
  {
    if (isupper(c))
      c = tolower(c);

    return c - 'a';
  }
  else
  {
    return -1;
  }
}

void free_node(node *n)
{
  for (int i = 0; i < 27; i++)
  {
    if (n->next[i] != NULL)
    {
      free_node(n->next[i]);
    }
  }
  free(n);
  return;
}
