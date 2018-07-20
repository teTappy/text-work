// The goal of this file is compile a few handy functions to work with strings.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 1000

bool palindrome_flag = false;

// Split the string and return the string between the indeces splice_from and
// splice_to (does not alter original string)
char *splice(char str[], int splice_from, int splice_to)
{
  int n = strlen(str);
  static char spliced_str[MAX_LENGTH];

  if (splice_from < 0 || splice_from > n || splice_to < splice_from || splice_to > n)
  {
    sprintf(spliced_str, "The indeces %i and %i are beyond the string length: %i", splice_from, splice_to, n);
    return spliced_str;
  }
  int i, j = 0;

  for (i = splice_from; i <= splice_to && i < n; i++)
  {
    spliced_str[j++] = str[i];
  }
  spliced_str[++j] = '\0';

  return spliced_str;
}

// This function does exactly what it says, reads input and returns a pointer
// to the input. (does not alter original string)
char *get_string(void)
{
  printf("input: (%i char max)\n", MAX_LENGTH);
  int c, counter = 0;
  static char input_line[MAX_LENGTH + 1];

  while (((c = getchar()) != '\n') && counter < MAX_LENGTH)
  {
    input_line[counter++] = c;
  }
  return input_line;
}

// Does not alter original string, instead returns a pointer to a new 'reversed'
// string.
char *reverse_string(char str[])
{
  int n = strlen(str);
  static char reversed_str[MAX_LENGTH];
  int j = n;

  for (int i = 0; i < n; i++)
    reversed_str[i] = str[--j];

  reversed_str[n] = '\0';
  palindrome_flag = strcmp(str, reversed_str) ? false : true;

  return reversed_str;
}

// reverse_string() must be called prior to is_palindrome(); will
// return false by default.
bool is_palindrome(void)
{
  return palindrome_flag;
}
