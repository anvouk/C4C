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
#define C4C_PARAM_STACK_STRUCT_NAME MY_STACK
#define C4C_PARAM_STACK_PREFIX my_stack
#define C4C_PARAM_STACK_CONTENT_TYPE int
#define C4C_PARAM_STACK_MAX_SIZE 64
#define C4C_PARAM_STACK_NO_VALUE_TYPE int
#define C4C_PARAM_STACK_NO_VALUE -1
#include "c4c/stack/literal_decl.inl"

/* 3. Declare the container implementation in a .c file or in wherever you
 *    want it to be. Make sure the macro params for the implementation have the
 *    same values as the interface ones.
 */
#define C4C_PARAM_STACK_STRUCT_NAME MY_STACK
#define C4C_PARAM_STACK_PREFIX my_stack
#define C4C_PARAM_STACK_CONTENT_TYPE int
#define C4C_PARAM_STACK_MAX_SIZE 64
#define C4C_PARAM_STACK_NO_VALUE_TYPE int
#define C4C_PARAM_STACK_NO_VALUE -1
#include "c4c/stack/literal_impl.inl"

/* 4. Magic happens. You can now use the container for your type :) */
int main(int argc, char* argv[])
{
	/* variables */
	int popt;
	int t1, t2, t3;
	MY_STACK stack;

	/* init some custom types */
	t1 = 1;
	t2 = 10;
	t3 = 100;

	/* print max stack size */
	printf("stack max size: %d\n", my_stack_capacity());

	/* prepare the stack for usage */
	my_stack_clear(&stack);

	/* push your custom types in the stack (if there is enough space) */
	assert(my_stack_push(&stack, t1) && "t1 discarded: the stack is full");
	assert(my_stack_push(&stack, t2) && "t2 discarded: the stack is full");
	assert(my_stack_push(&stack, t3) && "t3 discarded: the stack is full");

	/* pop the content until the stack is empty */
	while (1) {
		popt = my_stack_pop(&stack);
		/* check if popt has a valid value */
		if (popt != my_stack_null_val()) {
			printf("popt (a: %d)\n", popt);
		} else {
			printf("popt is %d thus the stack is surely empty.\n", my_stack_null_val());
			break;
		}
	}

	getchar();
	return EXIT_SUCCESS;
}
