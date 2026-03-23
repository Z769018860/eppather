#include <stdio.h>
#include "cJSON.h"

int main(void) {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "eppather");
    cJSON_AddNumberToObject(root, "version", 1);

    char *printed = cJSON_PrintUnformatted(root);
    if (printed == NULL) {
        cJSON_Delete(root);
        return 1;
    }

    puts(printed);
    cJSON_free(printed);
    cJSON_Delete(root);
    return 0;
}
