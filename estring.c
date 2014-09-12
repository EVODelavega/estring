#include <stdlib.h>
#include <string.h>
#include "estring.h"

#define INLINE_DESTROY(s) do { \
        free((s)->self); \
        (s)->self = NULL; \
        (s)->length = 0; \
    } while(0)

static String * concat_string(String *this, const String *from)
{
    this->length += from->length;
    this->self = realloc(
        this->self,
        sizeof *this->self * (this->length + 1)
    );
    if (this->self == NULL)
        return NULL;
    strncat(
        this->self,
        from->self,
        from->length
    );
    return this;
}

static String * concat_char(String *this, const char *add)
{
    size_t add_len = strlen(add);
    this->length += add_len;
    this->self = realloc(
        this->self,
        sizeof *this->self * (this->length + 1)
    );
    if (this->self == NULL)
        return NULL;
    strncat(
        this->self,
        add,
        add_len
    );
    return this;
}

static String * prepend_string( String *this, const String *from)
{
    size_t new_len = this->length + from->length;
    this->self = realloc(
        this->self,
        sizeof *this->self * (new_len + 1)
    );
    if (this->self == NULL)
        return NULL;
    memmove(
        this->self + from->length,
        this->self,
        this->length
    );
    memcpy(
        this->self,
        from->self,
        from->length
    );
    this->length = new_len;
    return this;
}

String * prepend_char(String *this, const char *val)
{
    size_t val_len = strlen(val);
    this->self = realloc(
        this->self,
        sizeof *this->self * (this->length + val_len + 1)
    );
    if (this->self == NULL)
        return NULL;
    memmove(
        this->self + val_len,
        this->self,
        this->length
    );
    memcpy(
        this->self,
        val,
        val_len
    );
    this->length += val_len;
    return this;
}

String * new_string(const char *val)
{
    String *s = malloc(sizeof *s);
    if (s == NULL)
        return NULL;
    s->length = strlen(val);
    s->self = malloc(sizeof *s->self * s->length);
    if (s->self == NULL) {
        free(s);
        return NULL;
    }
    s->self[0] = '\0';
    strncat(
        s->self,
        val,
        s->length
    );
    s->concat_string = &concat_string;
    s->concat_char = &concat_char;
    s->prepend_string = &prepend_string;
    s->prepend_char = &prepend_char;
    return s;
}

String make_string(const char *val)
{
    String s = {
        .self = NULL,
        .length = strlen(val),
        .concat_string = &concat_string,
        .concat_char = &concat_char,
        .prepend_string = &prepend_string,
        .prepend_char = &prepend_char
    };
    s.self = malloc(sizeof s.self * s.length);
    if (s.self == NULL) {
        s.self = NULL;
        return s;
    }
    s.self[0] = '\0';
    strncat(
        s.self,
        val,
        s.length
    );
    return s;
}

void string_init(String *str)
{
    str->self = NULL;
    str->length = 0;
    str->concat_string = &concat_string;
    str->concat_char = &concat_char;
    str->prepend_string = &prepend_string;
    str->prepend_char = &prepend_char;
}

void destroy_string(String *s_ptr)
{
    INLINE_DESTROY(s_ptr);
}

void delete_string(String **str)
{
    INLINE_DESTROY(*str);
    free(*str);
    *str = NULL;
}
