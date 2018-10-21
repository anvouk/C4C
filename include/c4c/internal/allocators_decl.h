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

/*------------------------------------------------------------------------------
	parameters
------------------------------------------------------------------------------*/

/**
 * Description:
 *		The container will NOT perform any memory allocations/deallocations and 
 *		cannot be resized.
 *		The container's capacity must be specified in this macro. It won't change 
 *		at runtime.
 *		
 * Expected type:
 * 		<size_t> (MUST be > 0)
 *
 * Examples:
 * 		20
 * 		32
 * 		1600
 */
/*
#define C4C_ALLOC_STATIC  <capacity > 0>
*/

/**
 * Description:
 *		The container will perform memory allocations/deallocations and may be 
 *		resized.
 * 		Every time the container performs an allocation it will allocate C4C_ALLOC_DYNAMIC
 * 		new objects of the specified type.
 * 		A higher value might result in fewer allocations in the long run but more
 * 		memory consumption.
 *
 * Expected type:
 * 		<size_t> (MUST be > 0)
 *
 * Default value:
 * 		1
 *
 * Examples:
 * 		1
 * 		4
 * 		10
 */
/*
#define C4C_ALLOC_DYNAMIC <alloc_blocks > 0>
*/

/*------------------------------------------------------------------------------
	parameters checks
------------------------------------------------------------------------------*/

#if !defined(C4C_ALLOC_STATIC) && !defined(C4C_ALLOC_DYNAMIC)
#  define C4C_ALLOC_DYNAMIC 1
#else
#  if defined(C4C_ALLOC_STATIC) && (C4C_ALLOC_STATIC <= 0)
#    error C4C_ALLOC_STATIC must be greater than zero.
#  endif
#  if defined(C4C_ALLOC_DYNAMIC) && (C4C_ALLOC_DYNAMIC <= 0)
#    error C4C_ALLOC_DYNAMIC must be greater than zero.
#  endif
#endif

/*------------------------------------------------------------------------------
	macros
------------------------------------------------------------------------------*/

#ifdef C4C_ALLOC_DYNAMIC
#  ifndef C4C_RAW_ARRAY
#    define C4C_RAW_ARRAY(type_, name_) type_* name_
#  endif
#else /* C4C_ALLOC_STATIC */
#  ifndef C4C_RAW_ARRAY
#    define C4C_RAW_ARRAY(type_, name_) type_ name_[C4C_ALLOC_STATIC]
#  endif
#endif
