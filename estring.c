#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estring.h"

#define INLINE_DESTROY(s) do { \
        free((s)->self); \
        (s)->self = NULL; \
        (s)->length = 0; \
    } while(0)

static String * concat_string(String *this, const String *from);
static String * concat_char(String *this, const char *add);
static String * prepend_string( String *this, const String *from);
static String * prepend_char(String *this, const char *val);
static int to_num(const String *this, void *destination, const char *type);

/**
 * String "methods", these static functions will be assigned to String members
 * You will be able to access them directly, but estring.h offers some macro's
 * That make the interface just a bit more consistent
 */

//concat the value of from to the end of this
String * concat_string(String *this, const String *from)
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

//concat a literal, or char[] to an existing string
String * concat_char(String *this, const char *add)
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

//prepend from to this
String * prepend_string( String *this, const String *from)
{
    size_t new_len = this->length + from->length;
    this->self = realloc(
        this->self,
        sizeof *this->self * (new_len + 1)
    );
    if (this->self == NULL)
        return NULL;
    //move this' value forward, to make way for from's value
    memmove(
        this->self + from->length,
        this->self,
        this->length
    );
    //prepend from value
    memcpy(
        this->self,
        from->self,
        from->length
    );
    this->length = new_len;
    return this;
}

//prepend literal, or char[] to existing string
String * prepend_char(String *this, const char *val)
{
    size_t val_len = strlen(val);
    this->self = realloc(
        this->self,
        sizeof *this->self * (this->length + val_len + 1)
    );
    if (this->self == NULL)
        return NULL;
    //same as above: make way for val
    memmove(
        this->self + val_len,
        this->self,
        this->length
    );
    //prepend val
    memcpy(
        this->self,
        val,
        val_len
    );
    this->length += val_len;
    return this;
}

//convert string to int, float double...
//TODO: use format, or macro's to cast the destination
//instead of guessing the destination type
int to_num(const String *this, void *destination, const char *type)
{
	*(int *)destination = 0;//int should be safe?
	if (this->self == NULL)
		return -1;
	int dec_sep = 0;
	size_t sub_len=0;
	char *val = this->self;//shortcut...
	while(isspace(*val))
		++val;
	while (isdigit(*(val +sub_len)) || *(val +sub_len) == '.')
	{
		if (*(val + sub_len) == '.')
		{
			if (dec_sep)
				break;
			dec_sep = 1;
		}
		++sub_len;
	}
	if (sub_len == 0)
		return 0;
	switch (type[1])
	{
		case 'd':
			*(int *)destination = atoi(val);
			break;
		case 'f':
			*(double *)destination = strtod(val, NULL);
			break;
		case 'z':
			*(size_t *)destination = strtoul(val, NULL, 10);
			break;
		case 'u':
			*(unsigned long long *)destination = strtoul(val, NULL, 10);
			break;
		default://default to bigger type?
			*(long long *)destination = strtol(val, NULL, 10);

	}
	return sub_len;
}

/*
 * End of "methods"
 **/

/**
 * Extern funciton definitions here
 */

//Create new String instance from string (literal or char[])
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
    //init first char to \0, so we can call strncat
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
    s->to_num = &to_num;
    return s;
}

//make string returns a stack String instance
String make_string(const char *val)
{
    String s = {
        .self = NULL,
        .length = strlen(val),
        .concat_string = &concat_string,
        .concat_char = &concat_char,
        .prepend_string = &prepend_string,
        .prepend_char = &prepend_char,
        .to_num = &to_num
    };
    s.self = malloc(sizeof s.self * s.length);
    if (s.self == NULL)
    {
        s.self = NULL;
        s.length = 0;
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

//initializer for created String
void string_init(String *str)
{
    str->self = NULL;
    str->length = 0;
    str->concat_string = &concat_string;
    str->concat_char = &concat_char;
    str->prepend_string = &prepend_string;
    str->prepend_char = &prepend_char;
    str->to_num = &to_num;
}

/**
 * destroy_string takes String *, delete_string takes String **
 * Reasoning behind this is that stack String can be "deleted" using:
 *    destroy_string(&string); where string is of type String
 *    delete_string(&str_ptr); where str_ptr is of type String *
 */

//destroy means: free self, restore String as if it were returned by string_init
void destroy_string(String *s_ptr)
{
    INLINE_DESTROY(s_ptr);
}

//delete: frees all memory, AND sets str to null, too
void delete_string(String **str)
{
    INLINE_DESTROY(*str);
    free(*str);
    *str = NULL;
}
