/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_lpop slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION list_lpop ===== */

int *list_lpop(int *self)
{
    int prev;

  if (!self[4]) return 0;

  int *node;

  if (--self[4]) {
    (self[3] = node[2])->prev = 0;
  } else {
    self[3] = self[2] = 0;
  }

  node[2] = node[1] = 0;
  return node;
}


