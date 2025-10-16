int process_character_remarks() {
    const char *names[4] = {"April", "Tam O'Shanter", "Emily", NULL};
    const char *remarks[4] = {"Bubbly: I'm > Tam and <= Emily", "Burns: \"When chapman billies leave the street ...\"", "Short & shrift", NULL};
    int a;
    const char **next;
    
    for (next = names, a = 0; *next != NULL; next = next + 1, a = a + 1) {
        if (remarks[a] != NULL) {
            continue;
        }
    }
    
    return;
}
