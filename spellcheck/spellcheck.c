#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("usage: [./spellcheck] [dict.txt] <text>\n");
    return 1;
  }
  // Open text
  char *text = argv[2];
  FILE *text_p = fopen(text, "r");
  if (text_p == NULL)
  {
    printf("failed to load text, quitting...\n");
    return 1;
  }

  // Open and load dictionary into memory
  const char *dict_p = argv[1];
  bool loaded = load(dict_p);
  if (!loaded)
  {
    printf("failed to load dictionary, quitting...\n");
    return 1;
  }

  // Create log file to to make a list of all misspelled words
  FILE *miss_p = fopen("misspelled.txt", "w");
  if (miss_p == NULL)
  {
    printf("failed to open log file");
    return 1;
  }


  char word[LENGTH+1];
  int c, word_index = 0;
  bool checked_word = false;
  unsigned int words_in_text = 0, misspelled = 0;

  // Go through text char by char
  for (c = fgetc(text_p); c != EOF; c = fgetc(text_p))
  {
    // Allow apostrophes to count as part of word
    if (isalpha(c) || (c == '\'' && word_index > 0))
    {
      word[word_index] = c;
      ++word_index;

      // If word is too long forget it and consume the rest of chars
      if (word_index > LENGTH)
      {
        while((c = fgetc(text_p) != EOF) && isalpha(c))

        // Reset index to prepare for another word
        word_index = 0;
      }
    }
    else if (isdigit(c))
    {
      // Consume digits and reset
      while((c = fgetc(text_p) != EOF) && isdigit(c))

      word_index = 0;
    }
    else if (word_index > 0)
    {
      // We have nound a whole word, write a escape char to the end of word
      word[word_index] = '\0';
      checked_word = check(word);
      ++words_in_text;

      if (!checked_word)
      {
        printf("%s\n", word);
        fprintf(miss_p, "%s\n", word);
        ++misspelled;
      }
      word_index = 0;
    }
  }
  if (ferror(text_p) || ferror(miss_p))
  {
    fclose(text_p);
    fclose(miss_p);
    printf("Error with either misspelled file or text file");
    unload();
    return 1;
  }
  fclose(text_p);

  fprintf(miss_p, "Misspelled words = %i\n", misspelled);
  fprintf(miss_p, "Words in dictionary = %i\n", size());
  fclose(miss_p);

  bool unloaded = unload();
  if (!unloaded)
  {
    printf("Failed to unload, aborting ...\n");
    return 1;
  }

  return 0;

}
