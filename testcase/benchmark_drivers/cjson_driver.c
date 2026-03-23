static int cjson_create_object(void) {
    return 1;
}

static int cjson_add_string(int object, const char *field_name, const char *field_value) {
    if (object > 0 && field_name != 0 && field_value != 0) {
        return 1;
    }
    return 0;
}

static int cjson_add_number(int object, const char *field_name, int number) {
    if (object > 0 && field_name != 0 && number >= 0) {
        return 1;
    }
    return 0;
}

int main(void) {
    int root = cjson_create_object();
    int ok_name = cjson_add_string(root, "name", "eppather");
    int ok_version = cjson_add_number(root, "version", 1);

    if (ok_name && ok_version) {
        return 0;
    }
    return 1;
}
