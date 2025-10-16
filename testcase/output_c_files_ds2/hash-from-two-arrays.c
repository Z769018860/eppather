int strhashkey(const char * key, int max) {
    unsigned h = 0;
    unsigned hl;
    unsigned hr;
    int i = 0;
    for (i = 0; key[i] != 0; i = i + 1) {
        h = h + key[i];
        hl = 1477 ^ (h & 4293918720) >> 18;
        hr = (h & 1048575);
        h = hl ^ hr ^ key[i];
    }
    return h % max;
}

void HashAddH(KeyType key, ValType value, void (*copyKey)(KeyType *kdest, KeyType ksrc), void (*copyVal)(ValType *vdest, ValType vsrc), unsigned (*hashKey)(KeyType key, int upperBound), int (*keySame)(KeyType key1, KeyType key2)) {
    unsigned hix = (*hashKey)(key, 4096);
    MapEntry m_ent;
    for (m_ent = hash[hix].first; m_ent && !(*keySame)(m_ent->key, key); m_ent = m_ent->link) {}
    if (m_ent) {
        (*copyVal)(&m_ent->value, value);
    } else {
        MapEntry last;
        MapEntry hme = malloc(sizeof(struct sHme));
        (*copyKey)(&hme->key, key);
        (*copyVal)(&hme->value, value);
        hme->link = 0;
        last = hash[hix].last;
        if (last) {
            last->link = hme;
        } else {
            hash[hix].first = hme;
        }
        hash[hix].last = hme;
    }
    return;
}

int HashGetH(ValType *val, KeyType key, unsigned (*hashKey)(KeyType key, int upperBound), int (*keySame)(KeyType key1, KeyType key2)) {
    unsigned hix = (*hashKey)(key, 4096);
    MapEntry m_ent;
    for (m_ent = hash[hix].first; m_ent && !(*keySame)(m_ent->key, key); m_ent = m_ent->link) {}
    if (m_ent) {
        *val = m_ent->value;
    }
    return (m_ent != 0);
}

void copyStr(const char **dest, const char *src) {
    *dest = strdup(src);
    return;
}

void copyInt(int *dest, int src) {
    *dest = src;
    return;
}

int strCompare(const char *key1, const char *key2) {
    int i = 0;
    for (i = 0; key1[i] != 0 && key2[i] != 0; i = i + 1) {
        if (key1[i] != key2[i]) {
            return 0;
        }
    }
    return key1[i] == key2[i];
}

void HashAdd(KeyType key, ValType value) {
    HashAddH(key, value, &copyStr, &copyInt, &strhashkey, &strCompare);
    return;
}

int HashGet(ValType *val, KeyType key) {
    return HashGetH(val, key, &strhashkey, &strCompare);
}
