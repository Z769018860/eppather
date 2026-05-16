typedef unsigned long size_t;
typedef long ssize_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef struct _IO_FILE FILE;
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t n, size_t size);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strncpy(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int fputc(int c, FILE *stream);
FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
int ferror(FILE *stream);
char *fgets(char *str, int num, FILE *stream);
int isspace(int c);
int isalpha(int c);
int isdigit(int c);
int isalnum(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);
double strtod(const char *nptr, char **endptr);
typedef int (*ini_handler)(void* user, const char* section,
                           const char* name, const char* value);
typedef char* (*ini_reader)(char* str, int num, void* stream);
 int ini_parse(const char* filename, ini_handler handler, void* user);
 int ini_parse_file(FILE* file, ini_handler handler, void* user);
 int ini_parse_stream(ini_reader reader, void* stream, ini_handler handler,
                     void* user);
 int ini_parse_string(const char* string, ini_handler handler, void* user);
 int ini_parse_string_length(const char* string, size_t length, ini_handler handler, void* user);
typedef struct {
    const char* ptr;
    size_t num_left;
} ini_parse_string_ctx;
static char* ini_rstrip(char* s, char* end)
{
    while (end > s && isspace((unsigned char)(*--end)))
        *end = '\0';
    return s;
}
static char* ini_lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}
static char* ini_find_chars_or_comment(const char* s, const char* chars)
{
    int was_space = 0;
    while (*s && (!chars || !strchr(chars, *s)) &&
           !(was_space && strchr(";", *s))) {
        was_space = isspace((unsigned char)(*s));
        s++;
    }
    return (char*)s;
}
static char* ini_strncpy0(char* dest, const char* src, size_t size)
{
    size_t i;
    for (i = 0; i < size - 1 && src[i]; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}
int ini_parse_stream(ini_reader reader, void* stream, ini_handler handler,
                     void* user)
{
    char line[200];
    size_t max_line = 200;
    char section[50] = "";
    char prev_name[50] = "";
    size_t offset;
    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;
    char abyss[16];
    size_t abyss_len;
    ((void)0);
    ((void)0);
    ((void)0);
    while (reader(line, (int)max_line, stream) != ((void*)0)) {
        offset = strlen(line);
        lineno++;
        if (offset == max_line - 1 && line[offset - 1] != '\n') {
            while (reader(abyss, sizeof(abyss), stream) != ((void*)0)) {
                if (!error)
                    error = lineno;
                abyss_len = strlen(abyss);
                if (abyss_len > 0 && abyss[abyss_len - 1] == '\n')
                    break;
            }
        }
        start = line;
        if (lineno == 1 && (unsigned char)start[0] == 0xEF &&
                           (unsigned char)start[1] == 0xBB &&
                           (unsigned char)start[2] == 0xBF) {
            start += 3;
        }
        start = ini_rstrip(ini_lskip(start), line + offset);
        if (strchr(";#", *start)) {
        }
        else if (*prev_name && *start && start > line) {
            end = ini_find_chars_or_comment(start, ((void*)0));
            *end = '\0';
            ini_rstrip(start, end);
            if (!handler(user, section, prev_name, start) && !error)
                error = lineno;
        }
        else if (*start == '[') {
            end = ini_find_chars_or_comment(start + 1, "]");
            if (*end == ']') {
                *end = '\0';
                ini_strncpy0(section, start + 1, sizeof(section));
                *prev_name = '\0';
            }
            else if (!error) {
                error = lineno;
            }
        }
        else if (*start) {
            end = ini_find_chars_or_comment(start, "=:");
            if (*end == '=' || *end == ':') {
                *end = '\0';
                name = ini_rstrip(start, end);
                value = end + 1;
                end = ini_find_chars_or_comment(value, ((void*)0));
                *end = '\0';
                value = ini_lskip(value);
                ini_rstrip(value, end);
                ini_strncpy0(prev_name, name, sizeof(prev_name));
                if (!handler(user, section, name, value) && !error)
                    error = lineno;
            }
            else {
                if (!error)
                    error = lineno;
            }
        }
    }
    return error;
}
int ini_parse_file(FILE* file, ini_handler handler, void* user)
{
    return ini_parse_stream((ini_reader)fgets, file, handler, user);
}
int ini_parse(const char* filename, ini_handler handler, void* user)
{
    FILE* file;
    int error;
    file = fopen(filename, "r");
    if (!file)
        return -1;
    error = ini_parse_file(file, handler, user);
    fclose(file);
    return error;
}
static char* ini_reader_string(char* str, int num, void* stream) {
    ini_parse_string_ctx* ctx = (ini_parse_string_ctx*)stream;
    const char* ctx_ptr = ctx->ptr;
    size_t ctx_num_left = ctx->num_left;
    char* strp = str;
    char c;
    if (ctx_num_left == 0 || num < 2)
        return ((void*)0);
    while (num > 1 && ctx_num_left != 0) {
        c = *ctx_ptr++;
        ctx_num_left--;
        *strp++ = c;
        if (c == '\n')
            break;
        num--;
    }
    *strp = '\0';
    ctx->ptr = ctx_ptr;
    ctx->num_left = ctx_num_left;
    return str;
}
int ini_parse_string(const char* string, ini_handler handler, void* user) {
    return ini_parse_string_length(string, strlen(string), handler, user);
}
int ini_parse_string_length(const char* string, size_t length,
                            ini_handler handler, void* user) {
    ini_parse_string_ctx ctx;
    ctx.ptr = string;
    ctx.num_left = length;
    return ini_parse_stream((ini_reader)ini_reader_string, &ctx, handler,
                            user);
}
