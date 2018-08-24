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
#define C4C_PARAM_STRUCT_NAME TestVector
#define C4C_PARAM_PREFIX tvec
#define C4C_PARAM_CONTENT_TYPE int
#include "c4c/vector/dyn_vector_decl.inl"

/* 3. Declare the container implementation in a .c file or in wherever you
 *    want it to be. Make sure the macro params for the implementation have the
 *    same values as the interface ones.
 */
#define C4C_PARAM_STRUCT_NAME TestVector
#define C4C_PARAM_PREFIX tvec
#define C4C_PARAM_CONTENT_TYPE int
#include "c4c/vector/dyn_vector_impl.inl"

void dump_vec(const TestVector* vec);

/* 4. Magic happens. You can now use the container for your type :) */
int main(int argc, char* argv[])
{
	/* variables */
	size_t i;
	c4c_res_t res;
	TestVector vec;

	printf("C4C %s | examples/example_dyn_vector_c89.c\n", _C4C_VERSION_STR);
	
	/* init the vector and allocate 20 int slots */
	if (!c4c_succeeded(res = tvec_init(&vec, 20))) {
		printf("couldn't init vector (%d)\n", res);
	}
	
	/* fill vector (no allocations performed) */
	for (i = 0; i < vec.capacity; i++) {
		if (!c4c_succeeded(res = tvec_push_back(&vec, (int)i))) {
			printf("couldn't add element (%d)\n", res);
			break;
		}
	}

	dump_vec(&vec);

	/* since the vector's allocated slots have been filled, grow the vector by 
	 * the number of elements specified in the optional header param 
	 * C4C_PARAM_OPT_ALLOC_BLOCK (default is set to 4 so allocate 4 new slots).
	 */
	if (!c4c_succeeded(res = tvec_push_back(&vec, (int)100))) {
		printf("couldn't add element (%d)\n", res);
	}

	/* If C4C_PARAM_OPT_ALLOC_BLOCK > 1 this won't allocate */
	if (!c4c_succeeded(res = tvec_push_back(&vec, (int)101))) {
		printf("couldn't add element (%d)\n", res);
	}

	dump_vec(&vec);

	tvec_resize(&vec, 30);

	/* remove some elements */
	tvec_pop_at(&vec, 6);
	tvec_pop_at(&vec, 15);

	dump_vec(&vec);

	tvec_free(&vec);

	getchar();
	return EXIT_SUCCESS;
}

void dump_vec(const TestVector* vec)
{
	size_t i;
	printf("\nvec: %d/%d\n", vec->size, vec->capacity);
	for (i = 0; i < vec->size; i++) {
		printf("[%.2d] %d\n", i, vec->data[i]);
	}
}