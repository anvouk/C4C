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

#include <stddef.h> /* for size_t */

/**
 * @file
 *
 * Inspired by C++ std::vector (somewhat similiar interface) this container has
 * been designed as a the de-facto C container (just like std::vector). Less
 * clunky than linked-lists yet just as powerful.
 *
 * <br><br>
 *
 * Features:
 * - Random access by index.
 * - push/pop elements wherever you want to.
 * - Heap allocation/deallocation ONLY upon initialization and freeing.
 * - Resizable.
 * - Copyable (to another vector).
 * - Extremely fast elements insertion and deletion without any sort of memory
 *   management (as long as you are ok with having some elements shuffled every
 *   time you call such functions)
 * - The same element may not be at the same index forever (see point above).
 *
 * @warning Beware of looping the vector with its size as the upper limit.
 *          Pushing and popping elements during such loops WILL change the
 *          vector's size and consequentially impact the loop behavior. It is
 *          recommended to store the vector's size in a temporary variable and
 *          use this one as the upper loop's limit. See vector example.
 */

 /*------------------------------------------------------------------------------
	params
 ------------------------------------------------------------------------------*/

 /*
 Parameters:

 #define C4C_PARAM_STRUCT_NAME 
 #define C4C_PARAM_PREFIX 
 #define C4C_PARAM_CONTENT_TYPE 
 */

 /*
 Optional parameters:

 #define C4C_PARAM_OPT_ALLOC_BLOCK 
 */

#ifndef C4C_PARAM_OPT_ALLOC_BLOCK
#  define C4C_PARAM_OPT_ALLOC_BLOCK 4
#endif

/*------------------------------------------------------------------------------
	vector struct definition
------------------------------------------------------------------------------*/

C4C_STRUCT_BEGIN(C4C_PARAM_STRUCT_NAME)
	size_t size;
	size_t capacity;
	C4C_PARAM_CONTENT_TYPE* data;
C4C_STRUCT_END(C4C_PARAM_STRUCT_NAME)

/*------------------------------------------------------------------------------
	vector functions
------------------------------------------------------------------------------*/

/**
 * Initialize a new dynamic vector.
 *
 * @param vec       The vector.
 * @param capacity  The vector's maximum size. If 0 malloc won't get called and
 *                  the function's return value will be 2.
 *
 * @retval 0  malloc failed.
 * @retval 1  Success.
 * @retval 2  Success but no allocation has been performed (capacity is set to
 *            0).
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _init, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t capacity);

/**
 * Free the vector's memory and prepare for new usage (must re-initialize first).
 *
 * @param vec  The vector.
 */
C4C_METHOD(C4C_PARAM_PREFIX, void, _free, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec);

/**
 * Resize the vector. Either shrink it or grow it (return value may change).
 *
 * @param vec       The vector.
 * @param capacity  The new capacity.
 * 
 * @note Ignores C4C_PARAM_OPT_ALLOC_BLOCK.
 *
 * @retval 0  realloc failed.
 * @retval 1  Success.
 * @retval 2  Success but, due to the shrinking of the vector, some elements
 *            were discarded.
 * @retval 3  Success but nothing happened (new capacity == old capacity).
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _resize, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t capacity);

/**
 * Copy the entire content of the first vector into the second one.
 * 
 * @note The destination vector may grow in case the source's size is bigger than 
 *       the destination's capacity.
 *
 * @param from  The source vector.
 * @param to    The destination vector.
 *
 * @retval 1  Success.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _copy, const C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* from, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* to);

/**
 * Add a new element to the vector's tail (if not already full).
 *
 * @param vec      The vector.
 * @param element  The element to add.
 *
 * @retval 0  Memory allocation/reallocation failed.
 * @retval 1  Success.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push_back, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, C4C_PARAM_CONTENT_TYPE element);

/**
 * Add a new element at the specified index position.
 *
 * @note Although this function might seem like a very expensive one to call, in
 *       reality no memory management operation will be performed, thus can be
 *       used with the only drawback that the old element at the index position
 *       will end up at the end of the vector.
 *
 * @param vec      The vector.
 * @param element  The element to add.
 * @param index    Where to add the new element.
 *
 * @retval -1  Index out of bounds.
 * @retval 0   Memory allocation/reallocation failed.
 * @retval 1   Success.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _push_at, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, C4C_PARAM_CONTENT_TYPE element, size_t index);

/**
 * Remove the last element of the vector.
 *
 * @note In reality this function will simply 'hide' it. If you manually
 *       increment the vector's size you'll still find it there unless it has
 *       already been overwritten.
 *
 * @param vec  The vector.
 *
 * @retval 1  Success.
 * @retval 2  Success but the vector was already empty.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _pop_back, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec);

/**
 * Remove the element at the specified index position in the vector.
 *
 * @note No memory management operation will be performed.
 *
 * @param vec    The vector.
 * @param index  The element's to remove index.
 *
 * @retval 0  Index out of bounds.
 * @retval 1  Success.
 */
C4C_METHOD(C4C_PARAM_PREFIX, c4c_res_t, _pop_at, C4C_STRUCT_DECLARE(C4C_PARAM_STRUCT_NAME)* vec, size_t index);

/*------------------------------------------------------------------------------
	undef header params
------------------------------------------------------------------------------*/

/* The vector struct name (name) (eg. my_int_vec, x_vector) */
#undef C4C_PARAM_STRUCT_NAME

/* The vector functions' prefix (name) (eg. my_vec, t1vec) */
#undef C4C_PARAM_PREFIX

/* The vector element type (type) (eg. int, char, or a custom struct) */
#undef C4C_PARAM_CONTENT_TYPE

/*------------------------------------------------------------------------------
	undef header optional params
------------------------------------------------------------------------------*/

/* Overcommit memory during allocations (size_t > 0) (eg. 1, 4, 10) */
#undef C4C_PARAM_OPT_ALLOC_BLOCK
