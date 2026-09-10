int probmems_pointer_two_element(int *p, int key) {
    int result = p[0];
    if (p[1] == key) {
        result = result + p[1];
    }
    return result;
}
