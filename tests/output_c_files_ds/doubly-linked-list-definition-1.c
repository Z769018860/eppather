int* newList(int* list) {
    list[0] = (int)&list[1];
    list[1] = 0;
    list[2] = (int)&list[0];
    return list;
}

int isEmpty(int* list) {
    int* head = (int*)list[0];
    if (head[0] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int* getHead(int* list) {
    return (int*)list[0];
}

int* getTail(int* list) {
    return (int*)list[2];
}

int* addTail(int* list, int* node) {
    node[0] = (int)&list[1];
    node[1] = list[2];
    int* tail_pred = (int*)list[2];
    tail_pred[0] = (int)node;
    list[2] = (int)node;
    return node;
}

int* addHead(int* list, int* node) {
    node[0] = list[0];
    node[1] = (int)&list[0];
    int* head = (int*)list[0];
    head[1] = (int)node;
    list[0] = (int)node;
    return node;
}

int* remHead(int* list) {
    int* head = (int*)list[0];
    list[0] = head[0];
    int* new_head = (int*)list[0];
    new_head[1] = (int)&list[0];
    return head;
}

int* remTail(int* list) {
    int* tail = (int*)list[2];
    list[2] = tail[1];
    int* new_tail = (int*)list[2];
    new_tail[0] = (int)&list[1];
    return tail;
}

int* insertAfter(int* list, int* r, int* n) {
    n[1] = (int)r;
    n[0] = r[0];
    int* next = (int*)r[0];
    next[1] = (int)n;
    r[0] = (int)n;
    return n;
}

int* removeNode(int* list, int* n) {
    int* prev = (int*)n[1];
    int* next = (int*)n[0];
    prev[0] = (int)next;
    next[1] = (int)prev;
    return n;
}

void dummy() {
    return;
}
