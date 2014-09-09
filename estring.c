#include <stdlib.h>
#include <string.h>
#include "estring.h"

static String * concat_string(String *this, const String *from)
{
    this->length += from->length;
    this->self = realloc(
        this->self,
        sizeof *this->self * this->length + 1
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
        sizeof *this->self * this->length + 1
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
    return s;
}

String make_string(const char *val)
{
    String s = {
        .self = NULL,
        .length = strlen(val),
        .concat_string = &concat_string,
        .concat_char = &concat_char
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
}

void destroy_string(String *s_ptr)
{
    free(s_ptr->self);
    s_ptr->self = NULL;
    s_ptr->length = 0;
}

void delete_string(String **str)
{
    destroy_string(*str);
    free(*str);
    *str = NULL;
}
