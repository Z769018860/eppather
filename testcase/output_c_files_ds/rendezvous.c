int print(int pnt_main_id, int pnt_main_ink, int pnt_backup_id, int pnt_backup_ink, const char * text, const char **error) {
    int p_id = pnt_main_id;
    int p_ink = pnt_main_ink;
    if (p_ink == 0) {
        p_id = pnt_backup_id;
        p_ink = pnt_backup_ink;
    }
    if (p_ink == 0) {
        *error = "Out of ink";
    } else {
        *error = 0;
        p_ink = p_ink - 1;
        if (p_id == pnt_main_id) {
            pnt_main_ink = p_ink;
        } else {
            pnt_backup_ink = p_ink;
        }
        for (; *text != '\0'; text = text + 1) {
        }
    }
    return *error != 0;
}
