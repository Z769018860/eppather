/* Generated typed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_lpush slice=type_erased */


/* ===== TYPED APPROX FUNCTION list_lpush ===== */

int *list_lpush(int *self, int *node)
{

  if (!node) return 0;

  if (self[4]) {
    node[2] = self[3];
    node[1] = 0;
    self[4] = node;
    self[3] = node;
  } else {
    self[3] = self[2] = node;
    node[1] = node[2] = 0;
  }

  ++self[4];
  return node;
}


