
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* assume ascii; warning: evaluates x multiple times! */
#define order(x) ((x) == '~' ? -1 \
		: isdigit((x)) ? 0 \
		: !(x) ? 0 \
		: isalpha((x)) ? (x) \
		: (x) + 256)

static int verrevcmp(const char *val, const char *ref) {
  if (!val) val= "";
  if (!ref) ref= "";

  while (*val || *ref) {
    int first_diff= 0;

    while ( (*val && !isdigit(*val)) || (*ref && !isdigit(*ref)) ) {
      /* if we have two non digits */
      int vc= order(*val), rc= order(*ref);
      if (vc != rc) {
        printf("     returning vc - rc\n");
        return vc - rc;
      }
      val++; ref++;
    }

    /* strip off leading 0's */
    while ( *val == '0' ) val++;
    while ( *ref == '0' ) ref++;

    /* check if we have two digits */
    while (isdigit(*val) && isdigit(*ref)) {
      if (!first_diff) {
        printf("    first digit triggered at val = %c, ref = %c\n", *val, *ref);
        first_diff= *val - *ref;
      }
      printf("    incrementing past %c, %c\n", *val, *ref);
      val++; ref++;
    }
    printf("    number comparison\n");
    if (isdigit(*val)) {
      printf("    *val = %c, returning 1\n", *val);
      return 1;
    }
    if (isdigit(*ref)) {
      printf("    *ref = %c, returning -1\n", *ref);
      return -1;
    }
    if (first_diff) {
      printf("    returning first_diff = %i\n", first_diff);
      return first_diff;
    }
  }
  printf("    strings equal\n");
  return 0;
}

main()
{
  char * test_strings[][2] =  {
    {"cliff-1.0", "cliff-2.0"},
    {"cliff-1.0", "cliff-1.0"},
    {"cliff-001.0", "cliff-1.0"},
    {"cliff-2.0", "cliff-1.0"},
    {"cliff-10.0", "cliff-1.0"},
    {"cliff-10.0", "cliff-2.0"},
    {"cliff-1.0", "cliff-1.0+2.0"},
    {"cliff-10.0", "cliff-1.0+2.0"},
    {"cliff-ab", "cliff-ac"},
    {"cliff-abc", "cliff-ab"},
    {"cliff-1.0bec1", "cliff-1.0"},
    {"cliff-101", "cliff-102"},
    {"cliff-110", "cliff-120"},
  };

  int i;

  for (i=0; i<ARRAY_SIZE(test_strings); i++) {
    printf("==========================\n");
    int ret = verrevcmp(test_strings[i][0], test_strings[i][1]);
    char c;
    if (ret == 0) c = '=';
    else if (ret < 0) c = '<';
    else if (ret > 0) c = '>';
    else {
      printf("Error");
      exit(-1);
    }

    printf("%s %c %s\n\n", test_strings[i][0], c, test_strings[i][1]);
  }
}

