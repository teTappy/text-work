#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#include "dictionary.h"
#define DICTIONARY "dictionaries/dict.txt"

int main(int argc, char *argv[])
{
  // Start timer
  clock_t tic = clock();

  // Check that word entered does not exceed 45 chars
  int n = strlen(argv[1]);
  if (argc != 2 || n > 45)
  {
    printf("Usage: <./wordcheck> [word (< 45 chars long)]\n");
    return 1;
  }

  // Load dictionary into memory
  const char *dict = DICTIONARY;
  bool loaded = load(dict);
  if (!loaded)
  {
    printf("Failed to load dictionary\n");
    return 1;
  }

  char *word = argv[1];
  char tempWord[LENGTH + 1];

  // copy original word into tempWord, making sure each letter is alphabetical.
  for (int i = 0, n = strlen(word); i < n; i++)
  {
    if (isalpha(word[i]))
    {
      tempWord[i] = word[i];
    }
    else
    {
      printf("Word must be alphabetical\n");
      return 1;
    }
  }
  tempWord[n] = '\0';

  bool in_dictionary = check(tempWord);

  // Stop timer
  clock_t toc = clock();

  printf("\"%s\" %s in the dictionary\n", word, in_dictionary ? "is" : "is NOT");
  printf("Elapsed time = %.5fseconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

  return 0;
}
