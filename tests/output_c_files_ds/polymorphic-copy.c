int obj_copy(int s, int c) {
    int clo;
    int parent;
    parent = *((int*)(c + 4));
    if (parent) {
        clo = obj_copy(s, parent);
    } else {
        clo = *((int*)(*((int*)s)) + 0);
    }
    if (clo) {
        int clone_fctn;
        clone_fctn = *((int*)(c + 12));
        ((void (*)(int, int))clone_fctn)(s, clo);
    }
    return clo;
}

void obj_del(int s, int c) {
    int del_fctn;
    del_fctn = *((int*)(c + 20));
    if (del_fctn) {
        ((void (*)(int))del_fctn)(s);
    }
    int parent;
    parent = *((int*)(c + 4));
    if (parent) {
        obj_del(s, parent);
    } else {
    }
}

int ObjClone(int s) {
    int class;
    class = *((int*)s);
    return obj_copy(s, class);
}

int ObjSpeak(int s) {
    int speak_fctn;
    speak_fctn = *((int*)(*((int*)s) + 16));
    return ((int (*)(int))speak_fctn)(s);
}

void ObjDestroy(int s) {
    if (s) {
        int class;
        class = *((int*)s);
        obj_del(s, class);
    }
    return;
}

void baseClone(int s, int clone) {
    *((int*)clone) = *((int*)s);
    return;
}

int baseSpeak(int s) {
    return (int)"Hello, I'm base object";
}

int boc[6] = {4, (int)"BaseObj", 0, (int)baseClone, (int)baseSpeak, 0};

void dogClone(int s, int c) {
    *((int*)(c + 4)) = *((int*)(s + 4));
    *((int*)(c + 8)) = *((int*)(s + 8));
    *((int*)(c + 12)) = *((int*)(s + 12));
    *((int*)(c + 16)) = *((int*)(s + 16));
    *((int*)(c + 20)) = *((int*)(s + 20));
    *((int*)(c + 24)) = *((int*)(s + 24));
    *((int*)(c + 28)) = *((int*)(s + 28));
    *((int*)(c + 32)) = *((int*)(s + 32));
    *((int*)(c + 36)) = *((int*)(s + 36));
    *((int*)(c + 40)) = *((int*)(s + 40));
    *((int*)(c + 44)) = *((int*)(s + 44));
    *((int*)(c + 48)) = *((int*)(s + 48));
    *((int*)(c + 52)) = *((int*)(s + 52));
    *((int*)(c + 56)) = *((int*)(s + 56));
    *((int*)(c + 60)) = *((int*)(s + 60));
    return;
}

int dogSpeak(int s) {
    return (int)"woof! woof! My name is . I'm a  Dog";
}

int dogc[6] = {60, (int)"Dog", (int)boc, (int)dogClone, (int)dogSpeak, 0};

void ferretClone(int s, int c) {
    *((int*)(c + 4)) = *((int*)(s + 4));
    *((int*)(c + 8)) = *((int*)(s + 8));
    *((int*)(c + 12)) = *((int*)(s + 12));
    *((int*)(c + 16)) = *((int*)(s + 16));
    *((int*)(c + 20)) = *((int*)(s + 20));
    *((int*)(c + 24)) = *((int*)(s + 24));
    *((int*)(c + 28)) = *((int*)(s + 28));
    *((int*)(c + 32)) = *((int*)(s + 32));
    *((int*)(c + 36)) = *((int*)(s + 36));
    *((int*)(c + 40)) = *((int*)(s + 40));
    *((int*)(c + 44)) = *((int*)(s + 44));
    *((int*)(c + 48)) = *((int*)(s + 48));
    *((int*)(c + 52)) = *((int*)(s + 52));
    *((int*)(c + 56)) = *((int*)(s + 56));
    *((int*)(c + 60)) = *((int*)(s + 60));
    return;
}

int ferretSpeak(int s) {
    return (int)"My name is . I'm a 0 mo. old  wiley Ferret";
}

int ferretc[6] = {60, (int)"Ferret", (int)boc, (int)ferretClone, (int)ferretSpeak, 0};

return;
