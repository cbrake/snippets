// this does not work

#include <glib.h>

G_LOCK_DEFINE_STATIC(mystruct);

typedef struct {
  int a;
  int b;
} mystruct_t;

mystruct_t mystruct;

#define MYSTRUCT_GET(param) {\
  G_LOCK(mystruct); \
  mystruct.param; \
  G_UNLOCK(mystruct); \
}

#define MYSTRUCT_SET(p,v) {\
  G_LOCK(mystruct); \
  mystruct.p = v; \
  G_UNLOCK(mystruct); \
}

main ()
{
  MYSTRUCT_SET(a,10);
  MYSTRUCT_SET(b,20);

  //int c = MYSTRUCT_GET(a);

  int c = {
    g_debug ("hi\n");
    int i = 10;
    g_debug ("hi\n");
  };

  g_debug("a = %i, b = %i\n", c, MYSTRUCT_GET(b));
} 


