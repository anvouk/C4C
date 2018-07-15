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

#include "c4c/config.h"
#include "c4c/function.h"
#include "c4c/struct.h"

#include "c4c/container_helpers.h"

#include <stddef.h> /* For size_t */

/*
Parameters:

#define C4C_PARAM_STACK_STRUCT_NAME 
#define C4C_PARAM_STACK_PREFIX 
#define C4C_PARAM_STACK_CONTENT_TYPE 
#define C4C_PARAM_STACK_MAX_SIZE 
#define C4C_PARAM_STACK_NO_VALUE_TYPE 
#define C4C_PARAM_STACK_NO_VALUE 
*/

/*------------------------------------------------------------------------------
   stack struct definition
------------------------------------------------------------------------------*/

/**
 * LIFO stack.
 */
C4C_STRUCT_BEGIN(C4C_PARAM_STACK_STRUCT_NAME)
	size_t count;
	C4C_PARAM_STACK_CONTENT_TYPE elements[C4C_PARAM_STACK_MAX_SIZE];
C4C_STRUCT_END(C4C_PARAM_STACK_STRUCT_NAME)

/*------------------------------------------------------------------------------
    stack functions
------------------------------------------------------------------------------*/

/**
 * Clear the stack and prepare for new usage.
 * 
 * @warning Does NOT free the stack's elements.
 *
 * @param stack The LIFO stack.
 */
C4C_METHOD(C4C_PARAM_STACK_STRUCT_NAME, C4C_PARAM_STACK_PREFIX, void, _clear, stack);

/**
 * Add a new tile to the end of the stack.
 *
 * @param stack         The LIFO stack.
 * @param new_element   The element to add.
 * 
 * @retval 0 if the stack is already full.
 * @retval 1 if the new_element was added successfully to the stack.
 */
C4C_METHOD(C4C_PARAM_STACK_STRUCT_NAME, C4C_PARAM_STACK_PREFIX, int, _push, stack, C4C_PARAM_STACK_CONTENT_TYPE new_element);

/**
 * Remove the element at the top of the stack and return it.
 *
 * @param stack The LIFO stack.
 *
 * @return The element at the top of the stack.
 *         C4C_PARAM_STACK_NO_VALUE if the stack is empty.
 */
C4C_METHOD(C4C_PARAM_STACK_STRUCT_NAME, C4C_PARAM_STACK_PREFIX, C4C_PARAM_STACK_CONTENT_TYPE, _pop, stack);

/**
 * Get the stack maximum capacity.
 * 
 * @return The stack max size.
 */
C4C_METHOD_INLINE(C4C_PARAM_STACK_PREFIX, size_t, _capacity, void)
{
	return (size_t)C4C_PARAM_STACK_MAX_SIZE;
}

/**
 * Get the stack's content invalid value.
 * 
 * @return A value that signals that the stack is currently empty.
 */
C4C_METHOD_INLINE(C4C_PARAM_STACK_PREFIX, C4C_PARAM_STACK_NO_VALUE_TYPE, _null_val, void)
{
	return (C4C_PARAM_STACK_NO_VALUE_TYPE)C4C_PARAM_STACK_NO_VALUE;
}

/*------------------------------------------------------------------------------
    undef header params
------------------------------------------------------------------------------*/

/* The stack struct name (name) (eg. my_int_stack, x_stack) */
#undef C4C_PARAM_STACK_STRUCT_NAME

/* The stack functions' prefix (name) (eg. my_stack) */
#undef C4C_PARAM_STACK_PREFIX

/* The stack element type (type) (eg. int, char, or a custom struct */
#undef C4C_PARAM_STACK_CONTENT_TYPE

/* The stack max size (size_t) (eg. 256, 400) */
#undef C4C_PARAM_STACK_MAX_SIZE

/* The type of C4C_PARAM_STACK_NO_VALUE (type) (eg. void*, int) */
#undef C4C_PARAM_STACK_NO_VALUE_TYPE

/* The value that indicates that there's no value (value) (eg. NULL, -1, -9999) */
#undef C4C_PARAM_STACK_NO_VALUE
