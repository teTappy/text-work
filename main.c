#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define WORD true
#define N_WORD false

void print(int w, int l, int b, int s, int t);

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("usage: <./main> <file>\n");
    return 1;
  }

  char *text = argv[1];
  FILE *fp = fopen(text, "r");
  if (fp == NULL)
  {
    printf("Could not open %s.\n", text);
    return 1;
  }

  int c;
  int lines = 0, word_count = 0, blank = 0, total_chars = 0, sents = 0;
  bool word = false;

  for (c = fgetc(fp); c != EOF; c = fgetc(fp))
  {

    ++total_chars;

    if (c == ' ' || c == '\t' || c == '\n')
    {
      ++blank;
      word = false;
    }

    if (isalpha(c) && (!word))
    {
      ++word_count;
      word = true;
    }

    if (c == '\n')
    {
      ++lines;
    }

    if (c == '.' || c == '?' || c == '!')
    {
      ++sents;
    }

  }
  fclose(fp);

  print(word_count, lines, blank, sents, total_chars);

  return 0;

}

void print(int w, int l, int b, int s, int t)
{
  printf("Words            = %5i\n", w);
  printf("Lines            = %5i\n", l);
  printf("Blanks           = %5i\n", b);
  printf("Sentences        = %5i\n", s);
  printf("Total Characters = %5i\n", t);
  printf("     (note: Total Characters also includes \\n)\n");
}
