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

#include "c4c/internal/allocators_impl.h"
#include "c4c/internal/common_headers.h"

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

#include "c4c/internal/params/default.h"
#include "c4c/internal/params/contenttype.h"

/*------------------------------------------------------------------------------
    vector functions implementation
------------------------------------------------------------------------------*/

C4C_METHOD(c4c_res_t, init, C4C_THIS vec, size_t capacity)
{
	vec->size = 0;
#ifdef C4C_ALLOC_DYNAMIC
	vec->capacity = capacity;
	if (capacity == 0) {
		vec->data = NULL;
		return C4CE_INVALID_ARG;
	}
	vec->data = C4C_ALLOC(sizeof(C4C_PARAM_CONTENT_TYPE) * capacity);
	if (!vec->data) {
		vec->capacity = 0;
		return C4CE_MALLOC_FAIL;
	}
#else
	vec->capacity = C4C_ALLOC_STATIC;
#endif
	return C4CE_SUCCESS;
}

C4C_METHOD(void, free, C4C_THIS vec)
{
	vec->size = 0;
	vec->capacity = 0;
#ifdef C4C_ALLOC_STATIC
	return;
#else
	C4C_FREE(vec->data);
	vec->data = NULL;
#endif
}

C4C_METHOD(c4c_res_t, resize, C4C_THIS vec, size_t capacity)
{
#ifdef C4C_ALLOC_STATIC
	return C4CE_CANT_DO;
#else
	size_t old_capacity = vec->capacity;
	if (vec->capacity == capacity)
		return C4CEW_NOTHING;
	vec->data = C4C_REALLOC(vec->data, sizeof(C4C_PARAM_CONTENT_TYPE) * capacity);
	if (!vec->data)
		return C4CE_REALLOC_FAIL;
	vec->capacity = capacity;
	if (old_capacity > capacity) {
		vec->size = capacity;
		return C4CEW_ELEMS_DISCARDED;
	}
	return C4CE_SUCCESS;
#endif
}

C4C_METHOD(c4c_res_t, copy, const C4C_THIS from, C4C_THIS to)
{
	c4c_res_t err = C4CE_SUCCESS;
	size_t i;
#ifdef C4C_ALLOC_DYNAMIC
	if (from->size >= to->capacity) {
		err = C4C_METHOD_CALL(resize, to, from->size);
		if (!c4c_succeeded(err))
			return err;
	}
#endif
	for (i = 0; i < from->size; ++i) {
		to->data[i] = from->data[i];
	}
	to->size = from->size;
	return C4CE_SUCCESS;
}

C4C_METHOD(c4c_res_t, push_back, C4C_THIS vec, C4C_PARAM_CONTENT_TYPE element)
{
	c4c_res_t err = C4CE_SUCCESS;
	if (vec->size >= vec->capacity)
#ifdef C4C_ALLOC_STATIC
		return C4CE_FULL;
#else
		if (!c4c_succeeded(err = C4C_METHOD_CALL(resize, vec, vec->capacity + C4C_ALLOC_DYNAMIC)))
			return err;
#endif
	vec->data[vec->size] = element;
	++vec->size;
	return C4CE_SUCCESS;
}

C4C_METHOD(c4c_res_t, push_at, C4C_THIS vec, C4C_PARAM_CONTENT_TYPE element, size_t index)
{
	c4c_res_t err = C4CE_SUCCESS;
	if (index >= vec->capacity)
		return C4CE_INDEX_OUT_OF_BOUNDS;
	if (vec->size >= vec->capacity)
#ifdef C4C_ALLOC_STATIC
		return C4CE_FULL;
#else
		if (!c4c_succeeded(err = C4C_METHOD_CALL(resize, vec, vec->capacity + C4C_ALLOC_DYNAMIC)))
			return err;
#endif
	/* Move the element at the specified index to the new last place the insert
	 * the new element in the right spot. */
	vec->data[vec->size] = vec->data[index];
	vec->data[index] = element;
	++vec->size;
	return C4CE_SUCCESS;
}

C4C_METHOD(c4c_res_t, pop_back, C4C_THIS vec)
{
	if (vec->size == 0)
		return C4CE_EMPTY;
	--vec->size;
	return C4CE_SUCCESS;
}

C4C_METHOD(c4c_res_t, pop_at, C4C_THIS vec, size_t index)
{
	if (vec->size == 0)
		return C4CE_EMPTY;
	if (index >= vec->size)
		return C4CE_INDEX_OUT_OF_BOUNDS;
	/* Replace the element to 'remove' with the last one, then decrement size. */
	vec->data[index] = vec->data[vec->size - 1];
	--vec->size;
	return C4CE_SUCCESS;
}

/*------------------------------------------------------------------------------
	undef header params
------------------------------------------------------------------------------*/

#include "c4c/internal/common_headers_undef.h"

#include "c4c/internal/params/default_undef.h"
#include "c4c/internal/params/contenttype_undef.h"

#include "c4c/internal/allocators_undef.h"
