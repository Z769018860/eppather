
typedef struct List {
    int x;
    struct List* next;
} List;

void insert(List** node, int data) {
    if ((*node) == NULL || data <= (*node)->x) {
        List* new_node = (List*)malloc(sizeof(List));
        new_node->x = data;
        new_node->next = *node;
        *node = new_node;
    } else {
        insert(&((*node)->next), data);
    }
}
