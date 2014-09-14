#ifndef __ESTRING_H_
#define __ESTRING_H_ 1
#include <string.h>
#define P_TO_STRING(sp) (sp)->self
#define TO_STRING(s) s.self
#define CONCAT_STRING(to, from) (to)->concat_string((to), (from))
#define CONCAT_CHAR(to, str) (to)->concat_char((to), str)
#define PREPEND_CHAR(to, str) (to)->prepend_char((to), str)
#define PREPEND_STRING(to, from) (to)->prepend_string((to), (from))
#define S_TO_NUM(s, num, t) (s).to_num(&(s), num, t)
#define SP_TO_NUM(sp, num, t) (sp)->to_num(sp, num, t)
#define NUM_DOUBLE "%f"
#define NUM_INT "%d"
#define NUM_SIZE "%zu"
#define NUN_LL "%p"
#define NUM_ULL "%u"


typedef struct string_t {
    char *self;
    size_t length;
    struct string_t *(*concat_string)();
    struct string_t *(*concat_char)();
    struct string_t *(*prepend_string)();
    struct string_t *(*prepend_char)();
    int (*to_num)();
} String;

extern void string_init(String *str);

extern String* new_string(const char *val);

extern String make_string(const char *val);

extern void destroy_string(String *s_ptr);

extern void delete_string(String **str);
#endif
