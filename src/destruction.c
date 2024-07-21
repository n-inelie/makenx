#include "makenx.h"
#include <stdlib.h>

void destroyNode(Node *n) {
    free(n->sub_nodes);
    free(n);
}
