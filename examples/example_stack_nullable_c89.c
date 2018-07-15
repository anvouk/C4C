/*
 * The MIT License
 *
 * Copyright 2018 Andrea Vouk.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 1. Define your custom type. */
typedef struct my_type {
	int a, b;
} my_type;

/* 1.1 FAC: Define custom implementations for some c4c macros. */
/*
#define C4C_FUNCTION(rettype, name, ...) \
rettype __stdcall name(__VA_ARGS__)
*/

/* 1.2 FAC: Enable/Disable/Change certain features by defining c4c settings macros. */
/* Define this to disable typedeffing structs. */
/*
#define _C4C_SETTINGS_STRUCT_NO_ALIAS
*/

/* 2. Declare the container interface in a .h file. */
#define C4C_PARAM_STACK_STRUCT_NAME MY_TYPE_STACK
#define C4C_PARAM_STACK_PREFIX my_type_stack
#define C4C_PARAM_STACK_CONTENT_TYPE my_type*
#define C4C_PARAM_STACK_MAX_SIZE 32
#include "c4c/stack/nullable_decl.inl"

/* 3. Declare the container implementation in a .c file or in wherever you
*     want it to be. Make sure the macro params for the implementation have the
*     same values as the interface ones.
*/
#define C4C_PARAM_STACK_STRUCT_NAME MY_TYPE_STACK
#define C4C_PARAM_STACK_PREFIX my_type_stack
#define C4C_PARAM_STACK_CONTENT_TYPE my_type*
#define C4C_PARAM_STACK_MAX_SIZE 32
#include "c4c/stack/nullable_impl.inl"

/* 4. Magic happens. You can now use the container for your type :) */
int main(int argc, char* argv[])
{
	/* variables */
	my_type* popt;
	my_type t1, t2, t3;
	MY_TYPE_STACK stack;

	/* init some custom types */
	t1.a = 1;   t1.b = 2;
	t2.a = 10;  t2.b = 20;
	t3.a = 100; t3.b = 200;

	/* print max stack size */
	printf("stack max size: %d\n", my_type_stack_capacity());

	/* prepare the stack for usage */
	my_type_stack_clear(&stack);

	/* push your custom types in the stack (if there is enough space) */
	assert(my_type_stack_push(&stack, &t1) && "t1 discarded: the stack is full");
	assert(my_type_stack_push(&stack, &t2) && "t2 discarded: the stack is full");
	assert(my_type_stack_push(&stack, &t3) && "t3 discarded: the stack is full");

	/* pop the content until the stack is empty */
	while (1) {
		popt = my_type_stack_pop(&stack);
		/* check if popt has a valid value */
		if (popt /* or popt != my_type_stack_null_val() */) {
			printf("popt (a: %d, b: %d)\n", popt->a, popt->b);
		} else {
			printf("popt is NULL thus the stack is surely empty.\n");
			break;
		}
	}

	getchar();
	return EXIT_SUCCESS;
}
