#include <stdio.h>
#include "textstuff.h"

int main(void)
{
  int x = 1, y = 3;
  char *string = get_string();
  char *spliced_string = splice(string, x, y);
  char *reversed_string = reverse_string(string);
  bool is_palindromic = is_palindrome();


  //printf("%s\n", string);
  printf("Spliced at indeces %i and %i:\n%s\n", x, y, spliced_string);
  printf("\"%s\" %s\n", reversed_string, is_palindromic ? "is a Palindrome!" : "is NOT a Palindrome");

  return 0;
}
