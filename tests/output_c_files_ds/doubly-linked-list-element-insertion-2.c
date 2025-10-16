struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void func() {
    struct Node a;
    struct Node b;
    struct Node c;
    a.next = &b;
    a.prev = 0;
    a.data = 1;
    b.next = 0;
    b.prev = &a;
    b.data = 3;
    c.data = 2;
    return;
}
