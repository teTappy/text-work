#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

node *hashtable[26] = {NULL};
unsigned int word_count = 0;
bool is_loaded = false;

bool load(const char *dictionary)
{
  FILE *dict_p = fopen(dictionary, "r");
  if (dict_p == NULL)
  {
    return false;
  }

  char current_word[LENGTH + 1];
  int index = 0;

  while (fscanf(dict_p, "%s", current_word) != EOF)
  {
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
      unload();
      return false;
    }
    strcpy(n->word, current_word);

    if (isupper(current_word[0]))
      current_word[0] = tolower(current_word[0]);

    index = current_word[0] - 'a';
    if (index < 0 || index > 25)
    {
      printf("Hashing went wrong\n");
      unload();
      return false;
    }

    if (hashtable[index] != NULL)
        {
            n->next = hashtable[index];
            hashtable[index] = n;
        }
        else
        {
            hashtable[index] = n;
            n->next = NULL;
        }
        ++word_count;
  }
  is_loaded = true;
  fclose(dict_p);
  return true;
}

bool check(char *word)
{
  for (int i = 0, l = strlen(word); i < l; i++)
  {
    if (isupper(word[i]) && isalpha(word[i]))
    {
      word[i] = tolower(word[i]);
    }
  }
  int index = word[0] - 'a';

  // Cycle through hashtable starting from the index
  node *ls_ptr = hashtable[index];
  while (ls_ptr != NULL)
  {
    if (strcmp(ls_ptr->word, word) == 0)
      return true;

    ls_ptr = ls_ptr->next;
  }
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
  node *ls_ptr = NULL;
  node *tmp = NULL;

  for (int i = 0; i < 26; i++)
  {
    ls_ptr = hashtable[i];

    while (ls_ptr != NULL)
    {
      tmp = ls_ptr;
      ls_ptr = ls_ptr->next;

      free(tmp);
    }
  }
  free(ls_ptr);
  return true;
}
