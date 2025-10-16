void rewrite_passwd() {
    int passwd_list_account_0[5] = {0};
    int passwd_list_password_0[5] = {0};
    int passwd_list_uid_0[5] = {1001};
    int passwd_list_gid_0[5] = {1000};
    int passwd_list_gecos_fullname_0[5] = {0};
    int passwd_list_gecos_office_0[5] = {0};
    int passwd_list_gecos_extension_0[5] = {0};
    int passwd_list_gecos_homephone_0[5] = {0};
    int passwd_list_gecos_email_0[5] = {0};
    int passwd_list_directory_0[5] = {0};
    int passwd_list_shell_0[5] = {0};
    int passwd_list_account_1[5] = {0};
    int passwd_list_password_1[5] = {0};
    int passwd_list_uid_1[5] = {1002};
    int passwd_list_gid_1[5] = {1000};
    int passwd_list_gecos_fullname_1[5] = {0};
    int passwd_list_gecos_office_1[5] = {0};
    int passwd_list_gecos_extension_1[5] = {0};
    int passwd_list_gecos_homephone_1[5] = {0};
    int passwd_list_gecos_email_1[5] = {0};
    int passwd_list_directory_1[5] = {0};
    int passwd_list_shell_1[5] = {0};
    int new_rec_account[5] = {0};
    int new_rec_password[5] = {0};
    int new_rec_uid[5] = {1003};
    int new_rec_gid[5] = {1000};
    int new_rec_gecos_fullname[5] = {0};
    int new_rec_gecos_office[5] = {0};
    int new_rec_gecos_extension[5] = {0};
    int new_rec_gecos_homephone[5] = {0};
    int new_rec_gecos_email[5] = {0};
    int new_rec_directory[5] = {0};
    int new_rec_shell[5] = {0};
    int passwd_buf[5] = {0};
    int rec_num;
    for (rec_num = 0; rec_num < 5; rec_num = rec_num + 1) {
        if (rec_num < 2) {
            passwd_list_uid_0[rec_num] = passwd_list_uid_0[0];
            passwd_list_gid_0[rec_num] = passwd_list_gid_0[0];
            passwd_list_uid_1[rec_num] = passwd_list_uid_1[0];
            passwd_list_gid_1[rec_num] = passwd_list_gid_1[0];
        }
    }
    for (rec_num = 0; rec_num < 5; rec_num = rec_num + 1) {
        if (rec_num < 2) {
            new_rec_uid[rec_num] = new_rec_uid[0];
            new_rec_gid[rec_num] = new_rec_gid[0];
        }
    }
    return;
}
