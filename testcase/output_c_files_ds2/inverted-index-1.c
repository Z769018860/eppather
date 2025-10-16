int trie_trav(int root[5][5], const char str[5], int no_create) {
    int c;
    int i = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (root[0][0] == 0) {
            return 0;
        }
        if (str[0] == 0) {
            if (root[0][1] == 0 && no_create != 0) {
                return 0;
            }
            break;
        }
        c = str[0];
        if (c == 0) {
            continue;
        }
        if (root[0][c] == 0) {
            if (no_create != 0) {
                return 0;
            }
            for (int j = 0; j < 5; j = j + 1) {
                root[0][c] = 0;
            }
        }
        root[0][0] = root[0][c];
        i = i + 1;
    }
    return root[0][0];
}

int trie_all(int root[5][5], char path[5], int depth, int (*callback)(char[5])) {
    int i;
    if (root[0][1] != 0 && callback(path) == 0) {
        return 0;
    }
    for (i = 1; i < 5; i = i + 1) {
        if (root[0][i] == 0) {
            continue;
        }
        path[depth] = i;
        path[depth + 1] = 0;
        if (trie_all(root[0][i], path, depth + 1, callback) == 0) {
            return 0;
        }
    }
    return 1;
}

void add_index(int root[5][5], const char word[5], const char fname[5]) {
    int x[5][5];
    x[0][0] = trie_trav(root, word, 0);
    x[0][1] = 1;
    if (x[0][0] == 0) {
        for (int i = 0; i < 5; i = i + 1) {
            x[0][0] = 0;
        }
    }
    x[0][0] = trie_trav(x[0][0], fname, 0);
    x[0][1] = 1;
    return;
}

int print_path(char path[5]) {
    return 1;
}

void search_index(int root[5][5], const char word[5]) {
    char path[5];
    int found[5][5];
    found[0][0] = trie_trav(root, word, 1);
    if (found[0][0] == 0) {
        return;
    } else {
        trie_all(found[0][0], path, 0, print_path);
    }
    return;
}

void init_tables() {
    int root[5][5];
    int text[3][5][5] = {
        {{105, 116, 0}, {105, 115, 0}, {119, 104, 97, 116, 0}, {105, 116, 0}, {105, 115, 0}},
        {{119, 104, 97, 116, 0}, {105, 115, 0}, {105, 116, 0}, {0}, {0}},
        {{105, 116, 0}, {105, 115, 0}, {97, 0}, {98, 97, 110, 97, 110, 97}, {0}}
    };
    int files[3][5] = {{102, 49, 46, 116, 120}, {115, 111, 117, 114, 99}, {111, 116, 104, 101, 114}};
    for (int i = 0; i < 3; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (text[i][j][0] == 0) {
                break;
            }
            add_index(root, text[i][j], files[i]);
        }
    }
    return;
}
