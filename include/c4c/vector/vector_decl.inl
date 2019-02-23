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
 * 		Vector.
 *
 * Brief description:
 * 		Inspired by C++ std::vector (somewhat similiar interface) this container
 * 		has been designed as a the de-facto C container (just like std::vector).
 * 		Less clunky than linked-lists yet just as powerful.
 * 		By defining C4C_ALLOC_STATIC this container won't perform ANY allocation.
 *
 * Supports allocators: YES
 * Container type:      STATIC/DYNAMIC
 * 
 * Features:
 * - Random access by index.
 * - push/pop elements wherever you want to.
 * - Heap allocation/deallocation ONLY upon initialization and freeing (if dynamic).
 * - Resizable (if dynamic).
 * - Copyable (to another vector).
 * - Extremely fast elements insertion and deletion without any sort of memory
 *   management (as long as you are ok with having some elements shuffled every
 *   time you call such functions)
 * - The same element may not be at the same index forever (see point above).
 */

#include "c4c/internal/allocators_decl.h"
#include "c4c/internal/common_headers.h"

/*------------------------------------------------------------------------------
	params
------------------------------------------------------------------------------*/

/*
Parameters:

#define C4C_PARAM_STRUCT_NAME 
#define C4C_PARAM_PREFIX 
#define C4C_PARAM_CONTENT_TYPE 
*/

#include "c4c/internal/params/default.h"
#include "c4c/internal/params/contenttype.h"

/*------------------------------------------------------------------------------
	vector struct definition
------------------------------------------------------------------------------*/

C4C_STRUCT_BEGIN(C4C_PARAM_STRUCT_NAME)
	size_t size;
	size_t capacity;
	C4C_RAW_ARRAY(C4C_PARAM_CONTENT_TYPE, data);
C4C_STRUCT_END(C4C_PARAM_STRUCT_NAME)

/*------------------------------------------------------------------------------
	vector functions
------------------------------------------------------------------------------*/

/**
 * Initialize a new dynamic vector.
 *
 * @param vec       The vector.
 * @param capacity  The vector maximum size. Ignored if C4C_ALLOC_STATIC has
 *                  been defined.
 *
 * @retval C4CE_INVALID_ARG  Capacity is an invalid number (zero?). No
 *                           allocation has been performed.
 * @retval C4CE_MALLOC_FAIL  C4C_ALLOC() failed.
 * @retval C4CE_SUCCESS      Success.
 */
C4C_METHOD(c4c_res_t, init, C4C_THIS vec, size_t capacity);

/**
 * Free the vector's memory and prepare for new usage (must re-initialize first).
 *
 * @param vec  The vector.
 */
C4C_METHOD(void, free, C4C_THIS vec);

/**
 * Resize the vector. Either shrink or grow (return value may change).
 *
 * @param vec       The vector.
 * @param capacity  The new capacity.
 *
 * @retval C4CE_REALLOC_FAIL      Memory reallocation failed.
 * @retval C4CE_CANT_DO           C4C_ALLOC_STATIC is defined. Cannot resize a
 *                                static array.
 * @retval C4CE_SUCCESS           Success.
 * @retval C4CEW_ELEMS_DISCARDED  Success but, due to the shrinking of the
 *                                vector, some elements were discarded.
 * @retval C4CEW_NOTHING          The new capacity is the same as the current one.
 */
C4C_METHOD(c4c_res_t, resize, C4C_THIS vec, size_t capacity);

/**
 * Copy the entire content of the first vector into the second one. Resize if
 * neccesary.
 *
 * @note The destination vector may grow in case the source's size is bigger
 *       than the destination's capacity.
 *
 * @param from  The source vector.
 * @param to    The destination vector.
 *
 * @retval C4CE_SUCCESS  Success.
 * @retval resize()'s    error codes.
 */
C4C_METHOD(c4c_res_t, copy, const C4C_THIS from, C4C_THIS to);

/**
 * Insert a new element at the end of the vector (if not already full).
 *
 * @param vec      The vector.
 * @param element  The element to add.
 *
 * @retval C4CE_FULL     The vector is full and can't be expanded
 *                       (C4C_ALLOC_STATIC has been defined).
 * @retval resize()'s    error codes.
 * @retval C4CE_SUCCESS  Success.
 */
C4C_METHOD(c4c_res_t, push_back, C4C_THIS vec, C4C_PARAM_CONTENT_TYPE element);

/**
 * Insert a new element at the specified index position.
 *
 * @note Although this function might seem like a very expensive one to call, in
 *       reality no memory management operation is be performed, thus it can be
 *       used with the only drawback that the old element at the index position
 *       will end up at the end of the vector.
 *
 * @param vec      The vector.
 * @param element  The element to add.
 * @param index    Where to add the new element.
 *
 * @retval C4CE_FULL                 The vector is full and can't be expanded
 *                                   (C4C_ALLOC_STATIC has been defined).
 * @retval C4CE_INDEX_OUT_OF_BOUNDS  Index is out of bounds.
 * @retval resize()'s                error codes.
 * @retval C4CE_SUCCESS              Success.
 */
C4C_METHOD(c4c_res_t, push_at, C4C_THIS vec, C4C_PARAM_CONTENT_TYPE element, size_t index);

/**
 * Remove the last element of the vector.
 *
 * @note In reality this function simply 'hides' it. If you manually
 *       increment the vector's size you'll still find it there unless it has
 *       already been overwritten.
 *
 * @param vec  The vector.
 *
 * @retval C4CE_EMPTY    The vector is already empty.
 * @retval C4CE_SUCCESS  Success.
 */
C4C_METHOD(c4c_res_t, pop_back, C4C_THIS vec);

/**
 * Remove the element at the specified index position in the vector.
 *
 * @note No memory management operation is be performed.
 *
 * @param vec    The vector.
 * @param index  The position of the element to remove.
 * 
 * @retval C4CE_EMPTY                The vector is already empty.
 * @retval C4CE_INDEX_OUT_OF_BOUNDS  Index is out of bounds (index >= size).
 * @retval C4CE_SUCCESS              Success.
 */
C4C_METHOD(c4c_res_t, pop_at, C4C_THIS vec, size_t index);

/*------------------------------------------------------------------------------
	undef header params
------------------------------------------------------------------------------*/

#include "c4c/internal/common_headers_undef.h"

#include "c4c/internal/params/default_undef.h"
#include "c4c/internal/params/contenttype_undef.h"

#include "c4c/internal/allocators_undef.h"
