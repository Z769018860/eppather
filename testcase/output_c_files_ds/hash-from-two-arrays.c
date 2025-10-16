unsigned strhashkey(const char * key, int max) {
    unsigned h = 0;
    unsigned hl;
    unsigned hr;
    int i = 0;
    for (i = 0; key[i] != '\0'; i = i + 1) {
        h = h + key[i];
        hl = 0x5C5 ^ (h & 0xfff00000) >> 18;
        hr = (h & 0x000fffff);
        h = hl ^ hr ^ key[i];
    }
    return h % max;
}

void HashAddH(const char * key, int value, void (*copyKey)(const char **, const char *), void (*copyVal)(int *, int), unsigned (*hashKey)(const char *, int), int (*keySame)(const char *, const char *)) {
    unsigned hix = (*hashKey)(key, 4096);
    struct sHme * m_ent;
    struct sHme * last;
    struct sHme * hme;
    for (m_ent = hash[hix].first; m_ent && !(*keySame)(m_ent->key, key); m_ent = m_ent->link) {
    }
    if (m_ent) {
        (*copyVal)(&m_ent->value, value);
    } else {
        hme = malloc(sizeof(struct sHme));
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

int HashGetH(int * val, const char * key, unsigned (*hashKey)(const char *, int), int (*keySame)(const char *, const char *)) {
    unsigned hix = (*hashKey)(key, 4096);
    struct sHme * m_ent;
    for (m_ent = hash[hix].first; m_ent && !(*keySame)(m_ent->key, key); m_ent = m_ent->link) {
    }
    if (m_ent) {
        *val = m_ent->value;
    }
    return (m_ent != 0);
}

void copyStr(const char ** dest, const char * src) {
    *dest = src;
    return;
}

void copyInt(int * dest, int src) {
    *dest = src;
    return;
}

int strCompare(const char * key1, const char * key2) {
    int i = 0;
    for (i = 0; key1[i] != '\0' && key2[i] != '\0'; i = i + 1) {
        if (key1[i] != key2[i]) {
            return 0;
        }
    }
    return key1[i] == key2[i];
}

void HashAdd(const char * key, int value) {
    HashAddH(key, value, &copyStr, &copyInt, &strhashkey, &strCompare);
    return;
}

int HashGet(int * val, const char * key) {
    return HashGetH(val, key, &strhashkey, &strCompare);
}
