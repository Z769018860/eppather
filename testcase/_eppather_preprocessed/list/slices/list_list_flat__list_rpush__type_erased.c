/* Generated typed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_rpush slice=type_erased */


/* ===== TYPED APPROX FUNCTION list_rpush ===== */

int *list_rpush(int *self, int *node)
{

  if (!node) return 0;

  if (self[4]) {
    node[1] = self[2];
    node[2] = 0;
    self[2] = node;
    self[2] = node;
  } else {
    self[3] = self[2] = node;
    node[1] = node[2] = 0;
  }

  ++self[4];
  return node;
}


