/* Generated typed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_at slice=type_erased */


/* ===== TYPED APPROX FUNCTION list_at ===== */

int *list_at(int *self, int index)
{

  int direction = LIST_HEAD;

  if (index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if (index < self[4]) {
    int *it;
    int *node;
    while (index--) node = 1;
    1;
    return node;
  }

  return 0;
}


