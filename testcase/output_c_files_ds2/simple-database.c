int dao(int cmd, int in_db_title[26], int in_db_first_name[26], int in_db_last_name[26], int in_db_date, int in_db_publ[100], int sortby) {
    int pdb[5][5];
    int rec[5][5];
    int hd[5][5];
    int i = 0;
    int ret = 0;
    int buf[100];
    
    if (cmd == 0) {
        for (i = 0; i < 5; i = i + 1) {
            pdb[i][0] = 0;
            rec[i][0] = 0;
            hd[i][0] = 0;
        }
    }
    else if (cmd == 1) {
        for (i = 0; i < 5; i = i + 1) {
            if (in_db_title[i] != 0) {
                in_db_title[i] = in_db_title[i];
            }
            if (in_db_first_name[i] != 0) {
                in_db_first_name[i] = in_db_first_name[i];
            }
            if (in_db_last_name[i] != 0) {
                in_db_last_name[i] = in_db_last_name[i];
            }
            if (in_db_publ[i] != 0) {
                in_db_publ[i] = in_db_publ[i];
            }
        }
    }
    else if (cmd == 2) {
        for (i = 0; i < 5; i = i + 1) {
            if (in_db_title[i] != 0) {
                in_db_title[i] = in_db_title[i];
            }
            if (in_db_first_name[i] != 0) {
                in_db_first_name[i] = in_db_first_name[i];
            }
            if (in_db_last_name[i] != 0) {
                in_db_last_name[i] = in_db_last_name[i];
            }
            if (buf[i] != 0) {
                buf[i] = buf[i];
            }
            if (in_db_publ[i] != 0) {
                in_db_publ[i] = in_db_publ[i];
            }
        }
    }
    else if (cmd == 3) {
        for (i = 0; i < 5; i = i + 1) {
            rec[i][0] = in_db_title[i];
            rec[i][1] = in_db_first_name[i];
            rec[i][2] = in_db_last_name[i];
            rec[i][3] = in_db_date;
            rec[i][4] = in_db_publ[i];
            hd[i][0] = rec[i][0];
            hd[i][1] = rec[i][1];
            hd[i][2] = rec[i][2];
            hd[i][3] = rec[i][3];
            hd[i][4] = rec[i][4];
            i = i + 1;
        }
    }
    else if (cmd == 4) {
        for (i = 0; i < 5; i = i + 1) {
            pdb[i][0] = in_db_title[i];
            pdb[i][1] = in_db_first_name[i];
            pdb[i][2] = in_db_last_name[i];
            pdb[i][3] = in_db_date;
            pdb[i][4] = in_db_publ[i];
        }
        for (i = 0; i < 5; i = i + 1) {
            pdb[i][4] = 0;
        }
        for (i = 4; i > 0; i = i - 1) {
            pdb[i - 1][4] = pdb[i][0];
        }
        rec[0][0] = pdb[0][0];
        rec[0][1] = pdb[0][1];
        rec[0][2] = pdb[0][2];
        rec[0][3] = pdb[0][3];
        rec[0][4] = pdb[0][4];
    }
    else if (cmd == 5) {
        for (i = 0; i < 5; i = i + 1) {
            rec[i][0] = 0;
            rec[i][1] = 0;
            rec[i][2] = 0;
            rec[i][3] = 0;
            rec[i][4] = 0;
        }
    }
    return;
}
