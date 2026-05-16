/* Generated type-erased approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_lpush slice=type_erased */


/* ===== TYPE ERASED FUNCTION list_lpush ===== */

int * list_lpush(int *self, int *node)
{

  if (!node) return 0;

  if (self[8]) {
    node[8] = self[8];
    node[8] = 0;
    self[8][8] = node;
    self[8] = node;
  } else {
    self[8] = self[8] = node;
    node[8] = node[8] = 0;
  }

  ++self[8];
  return node;
}


