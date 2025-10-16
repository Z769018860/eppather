#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void* generic_max(void* lhs, void* rhs, int (*compare)(void* lhs, void* rhs)) {
    if (compare(lhs, rhs) > 0) {         return lhs;
    } else {
        return rhs;
    }
}

void* generic_max3(void* lhs, void* mhs, void* rhs,
                   int (*compare)(void* lhs, void* rhs)) {
    return generic_max(generic_max(lhs, mhs, compare), rhs, compare);
}

void* generic_min(void* lhs, void* rhs, int (*compare)(void* lhs, void* rhs)) {
    if (compare(lhs, rhs) > 0) {         return rhs;
    } else {
        return lhs;
    }
}

enum RedBlackTreeColor {
    RBT_BLACK,
    RBT_RED
};

struct RedBlackTreeAugmentedData {
    int size;      int count; };

struct RedBlackTreeNode {
        struct RedBlackTreeNode* child[2];
    void* key;
    struct RedBlackTreeNode* p;
    enum RedBlackTreeColor color;
        struct RedBlackTreeAugmentedData data;


};

struct RedBlackTree {
    struct RedBlackTreeNode* root;
    struct RedBlackTreeNode* nil;

        int (*compare)(void* lhs, void* rhs);
    void* MAX;
    void* MIN;
};

void redblacktree_augmented_data_init(struct RedBlackTreeAugmentedData* data,
                                      int size,
                                      int count) {
    data -> size = size;
    data -> count = count;
}

void redblacktree_rotate_augment(struct RedBlackTreeNode* y,
                          struct RedBlackTreeNode* x) {
    y -> data.size = x -> data.size;
    x -> data.size = x -> child[0] -> data.size +
                     x -> child[1] -> data.size +
                     x -> data.count;
}

struct RedBlackTreeNode* redblacktree_node_init(void) {
    struct RedBlackTreeNode* node = malloc(sizeof(struct RedBlackTreeNode));
        node -> child[0] = NULL;
    node -> child[1] = NULL;
    node -> color = RBT_BLACK;
    node -> p = NULL;
    node -> key = NULL;
    

    redblacktree_augmented_data_init(&(node -> data), 0, 0);
    return node;
}
struct RedBlackTreeNode*
redblacktree_node_init2(void* key,
                        int size,
                        struct RedBlackTreeNode* left,
                        struct RedBlackTreeNode* right,
                        struct RedBlackTreeNode* p,
                        enum RedBlackTreeColor color) {
    struct RedBlackTreeNode* node = malloc(sizeof(struct RedBlackTreeNode));
        node -> child[0] = left;
    node -> child[1] = right;
    node -> color = color;
    node -> p = p;
    node -> key = malloc(size);
    memcpy(node -> key, key, size);
        redblacktree_augmented_data_init(&(node -> data), 1, 1);


    return node;
}
void redblacktree_node_deinit(struct RedBlackTreeNode* node) {
    free(node -> key);
    free(node);
}

void redblacktree_init(struct RedBlackTree* tree,
                       int (*compare)(void* lhs, void* rhs),
                       void* MAX,
                       void* MIN) {
    tree -> nil = redblacktree_node_init();
    


    tree -> root = tree -> nil;
    tree -> root -> p = tree -> nil;

    tree -> compare = compare;
    tree -> MAX = MAX;
    tree -> MIN = MIN;
}

void redblacktree_rotate(struct RedBlackTree* tree,
                         struct RedBlackTreeNode* x,
                         char is_right) {
    struct RedBlackTreeNode* y = x -> child[is_right ^ 1];
    x -> child[is_right ^ 1] = y -> child[is_right];
    if (y -> child[is_right] != tree -> nil) {
        y -> child[is_right] -> p = x;
    }
    y -> p = x -> p;
    if (x -> p == tree -> nil) {
        tree -> root = y;
    } else {
        x -> p -> child[x == x -> p -> child[1] ? 1 : 0] = y;
    }
    y -> child[is_right] = x;
    x -> p = y;
    

    redblacktree_rotate_augment(y, x);
}

void redblacktree_insert_fixup(struct RedBlackTree* tree,
                               struct RedBlackTreeNode* node) {
    struct RedBlackTreeNode* p;
    struct RedBlackTreeNode* gp;
    struct RedBlackTreeNode* y;
    struct RedBlackTreeNode* z = node;
    char is_left;
    while (z -> p -> color == RBT_RED) {
        p = z -> p;
        gp = p -> p;
        is_left = p == gp -> child[0] ? 1 : 0;
        y = gp -> child[is_left];
        if (y -> color == RBT_RED) {             y -> color = RBT_BLACK;
            p -> color = RBT_BLACK;
            gp -> color = RBT_RED;
            z = gp;
        } else {
            if (z == p -> child[is_left]) {                 z = p;
                redblacktree_rotate(tree, z, is_left ^ 1);
            }
                        z -> p -> color = RBT_BLACK;
            z -> p -> p -> color = RBT_RED;
            redblacktree_rotate(tree, gp, is_left);
        }
    }
    tree -> root -> color = RBT_BLACK;
}

void redblacktree_insert(struct RedBlackTree* tree, void* key, int size) {
    struct RedBlackTreeNode* x = tree -> root;
    struct RedBlackTreeNode* y = tree -> nil;
    struct RedBlackTreeNode* z = redblacktree_node_init2(key,
                                                         size,
                                                         tree -> nil,
                                                         tree -> nil,
                                                         tree -> nil,
                                                         RBT_RED);
        while (x != tree -> nil) {         y = x;
        y -> data.size += 1;
                if (tree -> compare(x -> key, key) == 0) {
            x -> data.count += 1;
            return;
        }
        x = x -> child[(tree -> compare(x -> key, key) < 0) ? 1 : 0];
    }
    z -> p = y;
    if (y == tree -> nil) {
        tree -> root = z;
    } else {
        y -> child[(tree -> compare(y -> key, key) < 0) ? 1 : 0] = z;
    }
    redblacktree_insert_fixup(tree, z);
}

struct RedBlackTreeNode* redblacktree_minimum(struct RedBlackTree tree,
                                              struct RedBlackTreeNode* node) {
    while (node -> child[0] != tree.nil) {
        node = node -> child[0];
    }
    return node;
}

void redblacktree_transplant(struct RedBlackTree* tree,
                struct RedBlackTreeNode* u,
                struct RedBlackTreeNode* v) {
    v -> p = u -> p;
    if (u -> p == tree -> nil) {
        tree -> root = v;
    } else {
        u -> p -> child[(u == u -> p -> child[1]) ? 1 : 0] = v;
    }
}

void redblacktree_delete_fixup(struct RedBlackTree* tree,
                 struct RedBlackTreeNode* node) {
    struct RedBlackTreeNode* x = node;
    struct RedBlackTreeNode* p;
    struct RedBlackTreeNode* w;
    char is_left = 0;
    while (x != tree -> root && x -> color == RBT_BLACK) {
        p = x -> p;
        is_left = x == x -> p -> child[0] ? 1 : 0;
        w = p -> child[is_left];
        if (w -> color == RBT_RED) {
            p -> color = RBT_RED;
            w -> color = RBT_BLACK;
            redblacktree_rotate(tree, p, is_left ^ 1);
            w = p -> child[is_left];
        }
        if (w -> child[0] -> color == RBT_BLACK &&
            w -> child[1] -> color == RBT_BLACK) {
            w -> color = RBT_RED;
            x = x -> p;
        } else {
            if (w -> child[is_left] -> color == RBT_BLACK) {
                w -> color = RBT_RED;
                w -> child[is_left ^ 1] -> color = RBT_BLACK;
                redblacktree_rotate(tree, w, is_left);
                w = p -> child[is_left];
            }
            w -> color = p -> color;
            p -> color = RBT_BLACK;
            w -> child[is_left] -> color = RBT_BLACK;
            redblacktree_rotate(tree, w -> p, is_left ^ 1);
            x = tree -> root;
        }
    }
    x -> color = RBT_BLACK;
}

void redblacktree_delete(struct RedBlackTree* tree, void* key) {
    struct RedBlackTreeNode* z = tree -> root;
    struct RedBlackTreeNode* w = tree -> nil;
    struct RedBlackTreeNode* y;
    struct RedBlackTreeNode* x;
    struct RedBlackTreeNode* delta;
    enum RedBlackTreeColor old_color;
    while (z != tree -> nil) {
        w = z;
        w -> data.size -= 1;
        if (tree -> compare(key, z -> key) == 0) {
            break;
        }
        z = z -> child[tree -> compare(z -> key, key) < 0 ? 1 : 0];
    }
    if (z != tree -> nil) {
        if (z -> data.count > 1) {
            z -> data.count -= 1;
            return;
        }
        y = z;
        old_color = y -> color;
        if (z -> child[0] == tree -> nil) {
            x = z -> child[1];
            redblacktree_transplant(tree, z, z -> child[1]);
        } else if (z -> child[1] == tree -> nil) {
            x = z -> child[0];
            redblacktree_transplant(tree, z, z -> child[0]);
        } else {
            y = redblacktree_minimum(*tree, z -> child[1]);
            old_color = y -> color;
            x = y -> child[1];
            if (y -> p == z) {
                x -> p = y;
            } else {
                delta = y;
                while (delta != z) {
                    delta -> data.size -= y -> data.count;
                    delta = delta -> p;
                }
                redblacktree_transplant(tree, y, y -> child[1]);
                y -> child[1] = z -> child[1];
                y -> child[1] -> p = y;
            }
            redblacktree_transplant(tree, z, y);
            y -> child[0] = z -> child[0];
            y -> child[0] -> p = y;
            y -> color = z -> color;
            y -> data.size = y -> child[0] -> data.size +
                             y -> child[1] -> data.size + y -> data.count;
        }
        if (old_color == RBT_BLACK) {
            redblacktree_delete_fixup(tree, x);
        }
        redblacktree_node_deinit(z);
    } else {
        while (w != tree -> nil) {
            w -> data.size += 1;
            w = w -> p;
        }
    }
}

struct RedBlackTreeNode* redblacktree_search(struct RedBlackTree tree,
                                             void* key) {
    struct RedBlackTreeNode* x = tree.root;
    while (x != tree.nil) {
        if (tree.compare(x -> key, key) == 0) {
            return x;
        }
        x = x -> child[tree.compare(x -> key, key) < 0 ? 1 : 0];
    }
    return tree.nil;
}

struct RedBlackTreeNode* redblacktree_maximum(struct RedBlackTree tree,
                                              struct RedBlackTreeNode* node) {
    while (node -> child[1] != tree.nil) {
        node = node -> child[1];
    }
    return node;
}

void* redblacktree_successor(struct RedBlackTree tree,
                             struct RedBlackTreeNode* x,
                             void* key) {
    if (x == tree.nil) {
        return tree.MAX;
    } else if (tree.compare(x -> key, key) <= 0) {
        return redblacktree_successor(tree, x -> child[1], key);
    } else {
        return generic_min(redblacktree_successor(tree, x -> child[0], key),
                           x -> key, tree.compare);
    }
}


void* redblacktree_predecessor(struct RedBlackTree tree,
                               struct RedBlackTreeNode* x,
                               void* key) {
    if (x == tree.nil) {
        return tree.MIN;
    } else if (tree.compare(x -> key, key) >= 0) {
        return redblacktree_predecessor(tree, x -> child[0], key);
    } else {
        return generic_max(redblacktree_predecessor(tree, x -> child[1], key),
                           x -> key, tree.compare);
    }
}

void* redblacktree_select(struct RedBlackTree tree, int i) {
    struct RedBlackTreeNode* x = tree.root;
    while (x != tree.nil) {
        if (x -> child[0] -> data.size + 1 <= i &&
            x -> child[0] -> data.size + x -> data.count >= i) {
            return x -> key;
        } else {
            if (x -> child[0] -> data.size + x -> data.count < i) {
                i -= x -> child[0] -> data.size + x -> data.count;
                x = x -> child[1];
            } else {
                x = x -> child[0];
            }
        }
    }
    return NULL;
}

int redblacktree_rank(struct RedBlackTree tree, void* key) {
    struct RedBlackTreeNode* x = tree.root;
    int rank = 0;

    while (x != tree.nil) {
        if (tree.compare(x -> key, key) < 0) {
            rank += x -> child[0] -> data.size + x -> data.count;
            x = x -> child[1];
        } else {
            x = x -> child[0];
        }
    }
    return rank;
}

char *buf, *p;
off_t size;
void io_init(void) {
    int fd = fileno(stdin);
    struct stat sb;
    fstat(fd, &sb);
    size = sb.st_size;
    buf = mmap(0, size, PROT_READ, MAP_PRIVATE, fileno(stdin), 0);
    p = buf;
}
char io_next_char(void) {
    return (p == buf + size || *p == -1) ? -1 : *p++;
}

void io_read_int(int* x) {
    bool iosig;
    static char c;
    for (iosig = false, c = io_next_char(); !isdigit(c); c = io_next_char()) {
        if (c == '-') iosig = true;
        if (c == -1) return;
    }
    for (*x = 0; isdigit(c); c = io_next_char())
        *x = ((*x + (*x << 2)) << 1) + (c ^ '0');
    if (iosig) *x = -(*x);
}

int cmp(void* lhs, void* rhs) {
    return (*(int*)lhs) - (*(int*)rhs);
}

void
redblacktree_test_inorder_tree_traversal(struct RedBlackTree tree,
                                         struct RedBlackTreeNode* node) {
    if (node != tree.nil) {
        redblacktree_test_inorder_tree_traversal(tree, node -> child[0]);
        printf("(%d|%d|%c) ", *(int*)(node -> key),
                              node -> data.size,
                              node -> color == RBT_RED ? 'R' : 'B');
        redblacktree_test_inorder_tree_traversal(tree, node -> child[1]);
    }
}

int main() {
    io_init();
        int __ = 1000000000 + 1;
    int ___ = -1 - 1;
    struct RedBlackTree tree;
    redblacktree_init(&tree, cmp, &__, &___);

    int n = 0;
    io_read_int(&n);

    int opt = 0;
    int opd = 0;
    for (int _ = 0; _ < n; _ += 1) {
        
        io_read_int(&opt);
        io_read_int(&opd);



        if (opt == 0) {
            redblacktree_insert(&tree, &opd, sizeof(int));
        } else if (opt == 1) {
            redblacktree_delete(&tree, &opd);
        } else if (opt == 2) {
            printf("%d\n", *(int*)(redblacktree_select(tree, opd)));
        } else if (opt == 3) {
            printf("%d\n", redblacktree_rank(tree, &opd));
        } else if (opt == 4) {
            __auto_type a = *(int*)redblacktree_predecessor(tree,
                                                            tree.root,
                                                            &opd);
            if (a == ___) {
                printf("-1\n");
            } else {
                printf("%d\n", a);
            }
        } else if (opt == 5) {
            __auto_type a = *(int*)redblacktree_successor(tree,
                                                          tree.root,
                                                          &opd);
            if (a == __) {
                printf("-1\n");
            } else {
                printf("%d\n", a);
            }
        }
    }

    return 0;
}
