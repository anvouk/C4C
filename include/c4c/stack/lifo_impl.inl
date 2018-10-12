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

#include <stddef.h> /* for NULL */
#include <string.h> /* for memset() */

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

#ifndef C4C_PARAM_OPT_NO_VALUE
#  define C4C_PARAM_OPT_NO_VALUE NULL
#endif

/*------------------------------------------------------------------------------
    stack functions implementation
------------------------------------------------------------------------------*/

C4C_METHOD(C4C_PARAM_PREFIX, void, _clear, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack)
{
	if (stack->count != 0) {
		stack->count = 0;
		memset(stack->elements, 0, sizeof(C4C_PARAM_CONTENT_TYPE) * C4C_PARAM_MAX_SIZE);
	}
}

C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack, C4C_PARAM_CONTENT_TYPE new_element)
{
	if (stack->count >= C4C_PARAM_MAX_SIZE)
		return 0;
	stack->elements[stack->count] = new_element;
	++stack->count;
	return 1;
}

C4C_METHOD(C4C_PARAM_PREFIX, C4C_PARAM_CONTENT_TYPE, _pop, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack)
{
	if (stack->count == 0)
		return (C4C_PARAM_CONTENT_TYPE)C4C_PARAM_OPT_NO_VALUE;
	--stack->count;
	C4C_PARAM_CONTENT_TYPE bottom = stack->elements[stack->count];
	stack->elements[stack->count] = (C4C_PARAM_CONTENT_TYPE)C4C_PARAM_OPT_NO_VALUE;
	return bottom;
}

/*------------------------------------------------------------------------------
    undef header params (see declaration file for docs)
------------------------------------------------------------------------------*/

#undef C4C_PARAM_STRUCT_NAME
#undef C4C_PARAM_PREFIX
#undef C4C_PARAM_CONTENT_TYPE
#undef C4C_PARAM_MAX_SIZE

/*------------------------------------------------------------------------------
	undef header optional params (see declaration file for docs)
------------------------------------------------------------------------------*/

#undef C4C_PARAM_OPT_NO_VALUE
