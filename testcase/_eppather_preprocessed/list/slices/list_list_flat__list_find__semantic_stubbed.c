/* Generated semantic-stubbed approximation for eppather summary mode. */

/* project=list EPPATHER_ENTRY=list_find slice=semantic_stubbed */


/* ===== SEMANTIC STUBBED FUNCTION list_find ===== */

int *list_find(int *self, int *val)
{

  int *it;
  int *node;

  while ((node = 1)) {
    if (self[1]) {
      if (self[1](val, node[1])) {
        1;
        return node;
      }
    } else {
      if (val == node[1]) {
        1;
        return node;
      }
    }
  }

  1;
  return 0;
}


