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

/**
 * Container:
 * 		LIFO stack.
 *
 * Brief description:
 * 		A standard and minimal LIFO stack implementation.
 * 		
 * Supports allocators: NO
 * Container type:      STATIC
 *
 * Features:
 * - Very lightweight and fast with a minimal yet expandable interface.
 * - Fixed push/pop.
 * - LIFO stack.
 */

#include "c4c/internal/common_headers.h"

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

/*
Parameters:

#define C4C_PARAM_STRUCT_NAME 
#define C4C_PARAM_PREFIX 
#define C4C_PARAM_CONTENT_TYPE 
#define C4C_PARAM_CAPACITY 
#define C4C_PARAM_OPT_NO_VALUE
*/

#include "c4c/internal/params/default.h"
#include "c4c/internal/params/contenttype.h"
#include "c4c/internal/params/capacity.h"
#include "c4c/internal/params/optnovalue.h"

/*------------------------------------------------------------------------------
   stack struct definition
------------------------------------------------------------------------------*/

C4C_STRUCT_BEGIN(C4C_PARAM_STRUCT_NAME)
	size_t count;
	C4C_PARAM_CONTENT_TYPE elements[C4C_PARAM_CAPACITY];
C4C_STRUCT_END(C4C_PARAM_STRUCT_NAME)

/*------------------------------------------------------------------------------
    stack functions
------------------------------------------------------------------------------*/

/**
 * Clear the stack and prepare for new usage.
 *
 * @warning Does NOT free the stack's elements.
 *
 * @param stack  The LIFO stack.
 */
C4C_METHOD(C4C_PARAM_PREFIX, void, _clear, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack);

/**
 * Add a new tile to the end of the stack.
 *
 * @param new_element  The element to add.
 * @param stack  The LIFO stack.
 *
 * @retval C4CE_FULL     The stack is already full.
 * @retval C4CE_SUCCESS  Success.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack, C4C_PARAM_CONTENT_TYPE new_element);

/**
 * Remove the element at the top of the stack and return it.
 *
 * @param stack  The LIFO stack.
 *
 * @return The element at the top of the stack. C4C_PARAM_OPT_NO_VALUE if the stack
 *         is empty.
 */
C4C_METHOD(C4C_PARAM_PREFIX, C4C_PARAM_CONTENT_TYPE, _pop, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* stack);

/**
 * Get the stack maximum capacity.
 *
 * @return The stack max size.
 */
C4C_METHOD_INLINE(C4C_PARAM_PREFIX, size_t, _capacity, void)
{
	return (size_t)C4C_PARAM_CAPACITY;
}

/**
 * Get the stack's content invalid value.
 *
 * @return A value that signals that the stack is currently empty.
 */
C4C_METHOD_INLINE(C4C_PARAM_PREFIX, C4C_PARAM_CONTENT_TYPE, _null_val, void)
{
	return (C4C_PARAM_CONTENT_TYPE)C4C_PARAM_OPT_NO_VALUE;
}

/*------------------------------------------------------------------------------
    undef header params
------------------------------------------------------------------------------*/

#include "c4c/internal/params/default_undef.h"
#include "c4c/internal/params/contenttype_undef.h"
#include "c4c/internal/params/capacity_undef.h"
#include "c4c/internal/params/optnovalue_undef.h"
