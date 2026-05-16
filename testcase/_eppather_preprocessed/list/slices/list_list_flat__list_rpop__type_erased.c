/* Generated type-erased approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_rpop slice=type_erased */


/* ===== TYPE ERASED FUNCTION list_rpop ===== */

int * list_rpop(int *self)
{
    int next;

  if (!self[8]) return 0;

  int *node = self[8];

  if (--self[8]) {
    (self[8] = node[8])->next = 0;
  } else {
    self[8] = self[8] = 0;
  }

  node[8] = node[8] = 0;
  return node;
}


