void process_passwd() {
    int passwd_list_account_0[6] = {'j','s','m','i','t','h'};
    int passwd_list_password_0[1] = {'x'};
    int passwd_list_uid_0 = 1001;
    int passwd_list_gid_0 = 1000;
    int passwd_list_gecos_fullname_0[9] = {'J','o','e',' ','S','m','i','t','h'};
    int passwd_list_gecos_office_0[9] = {'R','o','o','m',' ','1','0','0','7'};
    int passwd_list_gecos_extension_0[14] = {'(','2','3','4',')','5','5','5','-','8','9','1','7'};
    int passwd_list_gecos_homephone_0[14] = {'(','2','3','4',')','5','5','5','-','0','0','7','7'};
    int passwd_list_gecos_email_0[22] = {'j','s','m','i','t','h','@','r','o','s','e','t','t','a','c','o','d','e','.','o','r','g'};
    int passwd_list_directory_0[12] = {'/','h','o','m','e','/','j','s','m','i','t','h'};
    int passwd_list_shell_0[9] = {'/','b','i','n','/','b','a','s','h'};

    int passwd_list_account_1[4] = {'j','d','o','e'};
    int passwd_list_password_1[1] = {'x'};
    int passwd_list_uid_1 = 1002;
    int passwd_list_gid_1 = 1000;
    int passwd_list_gecos_fullname_1[8] = {'J','a','n','e',' ','D','o','e'};
    int passwd_list_gecos_office_1[9] = {'R','o','o','m',' ','1','0','0','4'};
    int passwd_list_gecos_extension_1[14] = {'(','2','3','4',')','5','5','5','-','8','9','1','4'};
    int passwd_list_gecos_homephone_1[14] = {'(','2','3','4',')','5','5','5','-','0','0','4','4'};
    int passwd_list_gecos_email_1[22] = {'j','d','o','e','@','r','o','s','e','t','t','a','c','o','d','e','.','o','r','g'};
    int passwd_list_directory_1[10] = {'/','h','o','m','e','/','j','d','o','e'};
    int passwd_list_shell_1[9] = {'/','b','i','n','/','b','a','s','h'};

    int new_rec_account[3] = {'x','y','z'};
    int new_rec_password[1] = {'x'};
    int new_rec_uid = 1003;
    int new_rec_gid = 1000;
    int new_rec_gecos_fullname[4] = {'X',' ','Y','z'};
    int new_rec_gecos_office[9] = {'R','o','o','m',' ','1','0','0','3'};
    int new_rec_gecos_extension[14] = {'(','2','3','4',')','5','5','5','-','8','9','1','3'};
    int new_rec_gecos_homephone[14] = {'(','2','3','4',')','5','5','5','-','0','0','3','3'};
    int new_rec_gecos_email[20] = {'x','y','z','@','r','o','s','e','t','t','a','c','o','d','e','.','o','r','g'};
    int new_rec_directory[9] = {'/','h','o','m','e','/','x','y','z'};
    int new_rec_shell[9] = {'/','b','i','n','/','b','a','s','h'};

    int passwd_buf[1000];
    int i;
    int j;
    int k;

    for (i = 0; i < 6; i = i + 1) {
        passwd_buf[i] = passwd_list_account_0[i];
    }
    passwd_buf[6] = ':';
    passwd_buf[7] = passwd_list_password_0[0];
    passwd_buf[8] = ':';
    
    int uid_str[4];
    int temp = passwd_list_uid_0;
    for (j = 3; j >= 0; j = j - 1) {
        uid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[9 + j] = uid_str[j];
    }
    passwd_buf[13] = ':';
    
    int gid_str[4];
    temp = passwd_list_gid_0;
    for (j = 3; j >= 0; j = j - 1) {
        gid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[14 + j] = gid_str[j];
    }
    passwd_buf[18] = ':';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[19 + j] = passwd_list_gecos_fullname_0[j];
    }
    passwd_buf[28] = ',';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[29 + j] = passwd_list_gecos_office_0[j];
    }
    passwd_buf[38] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[39 + j] = passwd_list_gecos_extension_0[j];
    }
    passwd_buf[53] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[54 + j] = passwd_list_gecos_homephone_0[j];
    }
    passwd_buf[68] = ',';
    
    for (j = 0; j < 22; j = j + 1) {
        passwd_buf[69 + j] = passwd_list_gecos_email_0[j];
    }
    passwd_buf[91] = ':';
    
    for (j = 0; j < 12; j = j + 1) {
        passwd_buf[92 + j] = passwd_list_directory_0[j];
    }
    passwd_buf[104] = ':';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[105 + j] = passwd_list_shell_0[j];
    }
    passwd_buf[114] = '\n';
    
    for (i = 0; i < 4; i = i + 1) {
        passwd_buf[115 + i] = passwd_list_account_1[i];
    }
    passwd_buf[119] = ':';
    passwd_buf[120] = passwd_list_password_1[0];
    passwd_buf[121] = ':';
    
    temp = passwd_list_uid_1;
    for (j = 3; j >= 0; j = j - 1) {
        uid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[122 + j] = uid_str[j];
    }
    passwd_buf[126] = ':';
    
    temp = passwd_list_gid_1;
    for (j = 3; j >= 0; j = j - 1) {
        gid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[127 + j] = gid_str[j];
    }
    passwd_buf[131] = ':';
    
    for (j = 0; j < 8; j = j + 1) {
        passwd_buf[132 + j] = passwd_list_gecos_fullname_1[j];
    }
    passwd_buf[140] = ',';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[141 + j] = passwd_list_gecos_office_1[j];
    }
    passwd_buf[150] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[151 + j] = passwd_list_gecos_extension_1[j];
    }
    passwd_buf[165] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[166 + j] = passwd_list_gecos_homephone_1[j];
    }
    passwd_buf[180] = ',';
    
    for (j = 0; j < 22; j = j + 1) {
        passwd_buf[181 + j] = passwd_list_gecos_email_1[j];
    }
    passwd_buf[203] = ':';
    
    for (j = 0; j < 10; j = j + 1) {
        passwd_buf[204 + j] = passwd_list_directory_1[j];
    }
    passwd_buf[214] = ':';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[215 + j] = passwd_list_shell_1[j];
    }
    passwd_buf[224] = '\n';
    
    for (i = 0; i < 3; i = i + 1) {
        passwd_buf[225 + i] = new_rec_account[i];
    }
    passwd_buf[228] = ':';
    passwd_buf[229] = new_rec_password[0];
    passwd_buf[230] = ':';
    
    temp = new_rec_uid;
    for (j = 3; j >= 0; j = j - 1) {
        uid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[231 + j] = uid_str[j];
    }
    passwd_buf[235] = ':';
    
    temp = new_rec_gid;
    for (j = 3; j >= 0; j = j - 1) {
        gid_str[j] = (temp % 10) + '0';
        temp = temp / 10;
    }
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[236 + j] = gid_str[j];
    }
    passwd_buf[240] = ':';
    
    for (j = 0; j < 4; j = j + 1) {
        passwd_buf[241 + j] = new_rec_gecos_fullname[j];
    }
    passwd_buf[245] = ',';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[246 + j] = new_rec_gecos_office[j];
    }
    passwd_buf[255] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[256 + j] = new_rec_gecos_extension[j];
    }
    passwd_buf[270] = ',';
    
    for (j = 0; j < 14; j = j + 1) {
        passwd_buf[271 + j] = new_rec_gecos_homephone[j];
    }
    passwd_buf[285] = ',';
    
    for (j = 0; j < 20; j = j + 1) {
        passwd_buf[286 + j] = new_rec_gecos_email[j];
    }
    passwd_buf[306] = ':';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[307 + j] = new_rec_directory[j];
    }
    passwd_buf[316] = ':';
    
    for (j = 0; j < 9; j = j + 1) {
        passwd_buf[317 + j] = new_rec_shell[j];
    }
    passwd_buf[326] = '\n';
    
    int found = 0;
    for (i = 225; i < 326; i = i + 1) {
        if (passwd_buf[i] == 'x' && passwd_buf[i + 1] == 'y' && passwd_buf[i + 2] == 'z') {
            found = 1;
            break;
        }
    }
    
    return;
}
