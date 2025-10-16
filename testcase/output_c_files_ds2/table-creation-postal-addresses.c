void sqlite_rewritten(int addrID, int addrStreet, int addrCity, int addrState, int addrZIP) {
    int db[5];
    int errmsg[5];
    int sqlite3_open_result[5];
    int sqlite3_exec_result[5];
    
    sqlite3_open_result[0] = 0;
    if (sqlite3_open_result[0] == 0) {
        sqlite3_exec_result[0] = 0;
        if (sqlite3_exec_result[0] != 0) {
            sqlite3_close_result[0] = 0;
            return;
        }
        sqlite3_close_result[0] = 0;
    } else {
        sqlite3_close_result[0] = 0;
        return;
    }
    return;
}
