int link_next[100];
int link_data[100];
int first;

void traverse_list() {
    int iter;
    for (iter = first; iter != 0; iter = link_next[iter]) {
        int data = link_data[iter];
    }
    return;
}
