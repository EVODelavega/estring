#ifndef __ESTRING_H_
#define __ESTRING_H_ 1
#include <string.h>
#define CONCAT_STRING(to, from) (to)->concat_string((to), (from))
#define CONCAT_CHAR(to, str) (to)->concat_char((to), str)

typedef struct string_t {
    char *self;
    size_t length;
    struct string_t *(*concat_string)();
    struct string_t *(*concat_char)();
} String;

extern void string_init(String *str);

extern String* new_string(const char *val);

extern String make_string(const char *val);

extern void delete_string(String **str);
#endif
