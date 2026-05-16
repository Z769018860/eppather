/* Generated typed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_rpop slice=type_erased */


/* ===== TYPED APPROX FUNCTION list_rpop ===== */

int *list_rpop(int *self)
{
    int next;

  if (!self[4]) return 0;

  int *node;

  if (--self[4]) {
    (self[2] = node[1])->next = 0;
  } else {
    self[2] = self[3] = 0;
  }

  node[2] = node[1] = 0;
  return node;
}


