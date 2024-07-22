#include "makenx.h"
#include <stdlib.h>

void destroy_node(Node *n) {
    free(n->sub_nodes);
    free(n);
}
