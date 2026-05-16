/* Generated typed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_remove slice=type_erased */


/* ===== TYPED APPROX FUNCTION list_remove ===== */

int *list_remove(int *self, int *node)
{

  node[1]
    ? (node[6] = node[2])
    : (self[3] = node[2]);

  node[2]
    ? (node[1] = node[1])
    : (self[2] = node[1]);

  if (self[1]) self[1](node[1]);

  1;
  --self[4];
}


