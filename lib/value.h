#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>
#include <stdbool.h>
#include "location.h"

/* types of values */
enum value_type {
	VALUE_TYPE_BOOLEAN,
	VALUE_TYPE_INTEGER,
	VALUE_TYPE_REAL,
	VALUE_TYPE_OBJECT,
	VALUE_TYPE_POINTER
};

/* represents a value */
struct value {
	enum value_type type; /* type of of the value */
	union {
		bool as_bool; /* value as a boolean */
		int as_int; /* value as an integer */
		float as_float; /* value as a real*/
		struct object *as_object; /* value as an object */
		struct value *as_pointer; /* value as a pointer */
	};
};

/* represents the type of an object */
struct type {
	const char *ident; /* type identifier */
	size_t nfields; /* number of fields in the object */
};

/* represents a variable */
struct variable {
	char *ident; /* identifier of the variable */
	struct type *type; /* type of the variable */
};

/*
 * represents a function prototype
 */
struct proto {
	char *ident; /* identifier of the function */
	size_t nparams; /* parameter count or arity */
	struct type *params; /* array of parameter types */
	struct type *rett; /* return type */
	struct location location; /* where in the source code the proto was definied */
};

/* type for void objects */
extern const struct type void_type;
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
	size_t length; /* length of the string */
	char buffer[]; /* pointer to the NULL terminated string */
};

/* represents a user defined object */
struct user_object {
	struct object base; /* to be an object */

	struct value fields[]; /* fields in the object */
};

struct user_object *object_new(struct type *type);
struct array_object *object_new_array(unsigned int from, unsigned int to);
struct string_object *object_new_string(char *buffer, size_t length, unsigned int hash);

bool value_is_number(struct value *value);
bool value_is_string(struct value *value);
bool value_is_array(struct value *value);

#endif /* VALUE_H */
