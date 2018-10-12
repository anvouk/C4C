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

/*
 * This file is part of the C4C library (https://github.com/QwertyQaz414/C4C).
 */

#include "c4c/config.h"
#include "c4c/function.h"
#include "c4c/struct.h"

#include "c4c/container_helpers.h"

#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for malloc(), realloc(), free() */

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

#ifndef C4C_PARAM_OPT_ALLOC_BLOCK
#  define C4C_PARAM_OPT_ALLOC_BLOCK 4
#endif

/*------------------------------------------------------------------------------
    vector functions implementation
------------------------------------------------------------------------------*/

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _init, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t capacity)
{
	vec->size = 0;
	vec->capacity = capacity;
	if (capacity == 0) {
		vec->data = NULL;
		return 2;
	}
	vec->data = malloc(sizeof(C4C_PARAM_CONTENT_TYPE) * capacity);
	if (!vec->data) {
		vec->capacity = 0;
		return 0;
	}
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, void, _free, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec)
{
	vec->size = 0;
	vec->capacity = 0;
	free(vec->data);
	vec->data = NULL;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _resize, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t capacity)
{
	size_t old_capacity = vec->capacity;
	if (vec->capacity == capacity)
		return 3;
	vec->data = realloc(vec->data, sizeof(C4C_PARAM_CONTENT_TYPE) * capacity);
	if (!vec->data)
		return 0;
	vec->capacity = capacity;
	if (old_capacity > capacity) {
		vec->size = capacity;
		return 2;
	}
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _copy, const C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* from, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* to)
{
	size_t i;
	if (from->size >= to->capacity)
		C4C_METHOD_CALL(C4C_PARAM_PREFIX, _resize, to, from->size);
	for (i = 0; i < from->size; ++i) {
		to->data[i] = from->data[i];
	}
	to->size = from->size;
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push_back, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, C4C_PARAM_CONTENT_TYPE element)
{
	if (vec->size >= vec->capacity)
		if (!c4c_succeeded(C4C_METHOD_CALL(C4C_PARAM_PREFIX, _resize, vec, vec->capacity + C4C_PARAM_OPT_ALLOC_BLOCK)))
			return 0;
	vec->data[vec->size] = element;
	++vec->size;
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push_at, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, C4C_PARAM_CONTENT_TYPE element, size_t index)
{
	if (index >= vec->capacity)
		return -1;
	if (vec->size >= vec->capacity)
		if (!c4c_succeeded(C4C_METHOD_CALL(C4C_PARAM_PREFIX, _resize, vec, vec->capacity + C4C_PARAM_OPT_ALLOC_BLOCK)))
			return 0;
	/* Move the element at the specified index to the new last place the insert
	 * the new element in the right spot. */
	vec->data[vec->size] = vec->data[index];
	vec->data[index] = element;
	++vec->size;
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _pop_back, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec)
{
	if (vec->size == 0)
		return 2;
	--vec->size;
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _pop_at, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t index)
{
	if (index >= vec->capacity)
		return 0;
	/* Replace the element to 'remove' with the last one, then decrement size. */
	vec->data[index] = vec->data[vec->size - 1];
	--vec->size;
	return 1;
}

/*------------------------------------------------------------------------------
	undef header params (see declaration file for docs)
------------------------------------------------------------------------------*/

#undef C4C_PARAM_STRUCT_NAME
#undef C4C_PARAM_PREFIX
#undef C4C_PARAM_CONTENT_TYPE

/*------------------------------------------------------------------------------
	undef header optional params (see declaration file for docs)
------------------------------------------------------------------------------*/

#undef C4C_PARAM_OPT_ALLOC_BLOCK
