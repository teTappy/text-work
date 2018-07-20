#include <stdio.h>
#include "textstuff.h"

int main(void)
{
  char *string = get_string();

  char *spliced_string = splice(string, 2, 8);

  printf("%s\n", string);
  printf("%s\n", spliced_string);


  return 0;
}
