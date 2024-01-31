#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
  int i, n, min_range, max_range, value;

  if (argc != 4) {
    printf("Please provide an integer input for the loop in addition to the range (min, max)!\n");
    exit(-1);
  }

  n = atoi(argv[1]);
  min_range = atoi(argv[2]);
  max_range = atoi(argv[3]);

  /*
   * Simple check just to make sure the range is not = 0
   */
  if ( min_range == max_range ) {
    printf("Please provide a range that is not equal to 0!\n");
    exit(-2);
  }

  srand((unsigned) getpid());

  //srand(time(0));

  for ( i = 0; i < n; i++ ) {
    value = (int) (min_range + (rand() % (max_range - min_range)));

    printf("value = %d\n", value);
  }

  return(0);
}
