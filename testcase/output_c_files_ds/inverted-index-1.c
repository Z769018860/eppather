int trie_trav(int root[][38], const char * str, int no_create, int chr_idx[256], int idx_chr[256]) {
    int c;
    for (; root; ) {
        c = str[0];
        if (c == '\0') {
            if (root[0][37] == 0 && no_create != 0) {
                return 0;
            }
            break;
        }
        c = chr_idx[c];
        if (c == 0) {
            str = str + 1;
            continue;
        }
        if (root[0][c] == 0) {
            if (no_create != 0) {
                return 0;
            }
            for (int i = 0; i < 38; i = i + 1) {
                root[0][c][i] = 0;
            }
        }
        root = root[0][c];
        str = str + 1;
    }
    return root;
}

void add_index(int root[][38], const char *word, const char *fname, int chr_idx[256], int idx_chr[256]) {
    int x = trie_trav(root, word, 0, chr_idx, idx_chr);
    x[0][37] = 1;
    if (x[0][0] == 0) {
        for (int i = 0; i < 38; i = i + 1) {
            x[0][0][i] = 0;
        }
    }
    x = trie_trav(x[0][0], fname, 0, chr_idx, idx_chr);
    x[0][37] = 1;
    return;
}

int trie_all(int root[][38], char path[1024], int depth, int (*callback)(char *), int idx_chr[256]) {
    if (root[0][37] != 0 && callback(path) == 0) {
        return 0;
    }
    for (int i = 1; i < 38; i = i + 1) {
        if (root[0][i] == 0) {
            continue;
        }
        path[depth] = idx_chr[i];
        path[depth + 1] = '\0';
        if (trie_all(root[0][i], path, depth + 1, callback, idx_chr) == 0) {
            return 0;
        }
    }
    return 1;
}

void init_tables(int root[][38], int chr_idx[256], int idx_chr[256]) {
    char chr_legal[38] = "abcdefghijklmnopqrstuvwxyz0123456789_-./";
    for (int i = 0; i < 38; i = i + 1) {
        chr_idx[(int)chr_legal[i]] = i + 1;
        idx_chr[i + 1] = chr_legal[i];
    }
    const char *files[3] = { "f1.txt", "source/f2.txt", "other_file" };
    const char *text[3][5] = {
        { "it", "is", "what", "it", "is" },
        { "what", "is", "it", 0, 0 },
        { "it", "is", "a", "banana", 0 }
    };
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (text[i][j] == 0) {
                break;
            }
            add_index(root, text[i][j], files[i], chr_idx, idx_chr);
        }
    }
    return;
}

void search_index(int root[][38], const char *word, int chr_idx[256], int idx_chr[256]) {
    char path[1024];
    int found = trie_trav(root, word, 1, chr_idx, idx_chr);
    if (found == 0) {
        return;
    } else {
        trie_all(found[0][0], path, 0, 0, idx_chr);
    }
    return;
}
