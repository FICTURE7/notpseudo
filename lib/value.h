#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdbool.h>

/* types of values */
enum value_type {
	VALUE_TYPE_BOOLEAN,
	VALUE_TYPE_INTEGER,
	VALUE_TYPE_REAL,
	VALUE_TYPE_OBJECT
};

/* represents a value */
struct value {
	enum value_type type; /* type of of the value */
	union {
		bool as_bool; /* value as a boolean */
		int as_int; /* value as an integer */
		float as_float; /* value as a real*/
		struct object *as_object; /* value as an object */
	};
};

/* represents the type of an object */
struct type {
	const char *ident; /* type identifier */
	unsigned int nfields; /* number of fields in the object */
};

/* type for array_object */
extern const struct type array_type;
/* type for string_object */
extern const struct type string_type;

/* 
 * represents an instance object
 * which is heap allocated
 */
struct object {
	unsigned int nrefs; /* number of refs for gc */
	struct type *type; /* type of object */
};

/* represents an array which is within a range */
struct array_object {
	struct object base; /* to be an object */

	unsigned int from; /* start index of the array */
	unsigned int to; /* end index of the array */
	struct value items[]; /* elements in the array */
};

/* represents a string object */
struct string_object {
	struct object base; /* to be an object */

	unsigned int hash; /* hash of the string */
	size_t len; /* length of the string */
	char *buf; /* pointer to the NULL terminated string */
};

/* represents a user defined object */
struct user_object {
	struct object base; /* to be an object */

	struct value fields[]; /* fields in the object */
};

struct user_object *object_new(struct type *type);
struct array_object *object_new_array(unsigned int from, unsigned int to);
struct string_object *object_new_string(char *buf, size_t len, unsigned int hash);

bool value_is_string(struct value *value);
bool value_is_array(struct value *value);

#endif /* OBJECT_H */