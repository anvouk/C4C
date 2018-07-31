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

/* 4. Magic happens. You can now use the container for your type :) */
int main(int argc, char* argv[])
{
	/* variables */
	size_t i, j;
	c4c_res_t res;
	TestVector vec;
	
	/* init the vector and allocate 64 int slots */
	if (!c4c_succeeded(res = tvec_init(&vec, 20))) {
		printf("couldn't init vector (%d)\n", res);
	}
	
	/* add elements */
	for (i = 0; i < vec.capacity; i++) {
		if (!c4c_succeeded(res = tvec_push_back(&vec, (int)i))) {
			printf("couldn't add element (%d)\n", res);
			break;
		}
	}

	printf("vec: %d/%d\n", vec.size, vec.capacity);
	for (i = 0; i < vec.size; i++) {
		printf("[%d] %d\n", i, vec.data[i]);
	}

	tvec_resize(&vec, 30);

	/* WARNING: remember to save the vector's size because every push/pop function 
	 * will automatically increment/decrement it and the loop might not end up 
	 * working as expected.
	 */
	j = vec.size;
	for (i = j; i < vec.capacity; i++) {
		if (!c4c_succeeded(res = tvec_push_back(&vec, i))) {
			printf("couldn't add element (%d)\n", res);
			break;
		}
	}

	tvec_pop_at(&vec, 15);
	tvec_pop_at(&vec, 20);

	printf("vec: %d/%d\n", vec.size, vec.capacity);
	for (i = 0; i < vec.size; i++) {
		printf("[%d] %d\n", i, vec.data[i]);
	}

	getchar();
	return EXIT_SUCCESS;
}
