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

#ifndef __C4C_CONFIG_H__
#define __C4C_CONFIG_H__

/**
 * === C4C Introduction ===
 *
 * Containers structure:
 * - Containers are divided in folders.
 * - For a container type there might exist more than one implementation. In
 *   such cases consult the xxx_decl.inl file's documentation to see in what it
 *   differs from other variants.
 * - Files suffixed with a _decl.inl contain the container interface, function
 *   prototypes, and eventually function macros.
 * - Files suffixed with a _impl.inl contain the container implementation. Note
 *   that for every container (unless missig suffix) both _decl.inl and
 *   _impl.inl files are needed for it to compile and work properly.
 * - _decl.inl and _impl.inl files can either be #included in the same file or
 *   in different files as long as the C4C_PARAM_...s have the SAME values.
 *   Ideally you want to #include the _decl.inl file in a header file and the
 *   _impl.inl in the respective source file.
 * - Every container's function is wrapped inside a fully customizable
 *   C4C_METHOD macro and with its Doxygen format comment explaining how to
 *   properly use it.
 * - Note that EVERY container WILL NOT allocate elements upon insertion nor
 *   free them upon deletion. Is your responsability to handle their lifecycle
 *   making sure they don't run out of scope after inserted or freed without
 *   removing the pointer in the container. In the future I may implement some
 *   sort of generic customizable allocator/deallocator for the stored elements
 *   in order to lift this job off the programmer and to make a more seamless
 *   integration with the containers (something like C++ std allocators maybe?).
 *   For now the containers inside this library have ONE and only one purpose:
 *   to keep your variables/pointers/etc... organized inside a lightweight, fast
 *   and customizable structure making it easy for the programmer to access them
 *   whenever he wants to.
 *
 * Common macro structure:
 * - Macros starting with 'C4C_' can be custom defined before including the .h
 *   file to customize their behavior. Remember to manually #undefine them when
 *   no longer needed.
 * - Macros prefixed with '_C4C' are not to be modified.
 * - Macros prefixed with a double underscore are for internal usage.
 * - Macros prefixed and postfixed with a double underscore are header guards.
 * - Macros prefixed with 'C4C_PARAM_' MUST be defined before BOTH '_decl.inl'
 *   and '_impl.inl' with the SAME values.
 * - Macros prefixed with 'C4C_PARAM_OPT_' behave in the same way as the ones
 *   above but they can be omitted. This will create them with default values
 *   (see their respective file).
 * - Macros prefixed with 'C4C_FEATURE_' can be defined before including the
 *   header to enable/disable some frequently used pattern.
 * - Files with the .inl extension are 'template' headers. Include them in the
 *   project, look at the beginning of those files and you'll see macros like
 *   '#define C4C_PARAM_xxx'. Open the respective file in the internal/params
 *   subfolder to see how to correctly use it. These macros must be correctly
 *   #defined before including the .inl file. Note that these macros will
 *   automatically get #undefined after each include of the .inl file.
 *   C4C_PARAM_OPT_xxx like macros can be optionally defined to customize some
 *   other aspect of the container. If left undefined they will be automatically
 *   #defined and #undefined inside the .inl files with a default value.
 * - Note that currently, the only header with an include guard is config.h. Any
 *   other file can be included more than once (so you can customize macros) so
 *   the preprocessor might slow down a bit if they are excessively included
 *   everywhere (though not that much since they are all very small files).
 *
 * C4C errors API:
 * - See the end of config.h for more info.
 * - Functions with the return value of type c4c_res_t can have multiple
 *   success/failure return values.
 * - See each function's Doxygen comment in the xxx_decl.inl file to understand
 *   what each return value means.
 * - A return value of 1 states that the function succeeded without problems of
 *   any kind.
 * - A return value <= 0 indicates total failure of the function. The operation
 *   couldn't be completed so the function aborted its execution.
 * - A return value > 1 states a success but the function hit a corner case so
 *   certain (documented) particular behaviors may manifest themselves.
 * - Use the macro c4c_succeeded to get a boolean value when corner cases are
 *   negligible.
 *
 * Allocators:
 * - Some containers will support allocators (see if they include them and if in
 *   their description they have a big YES for the field 'Supports allocators:')
 * - These containers can have both dynamic allocations and a static memory pool
 *   depending on 2 macros: C4C_ALLOC_STATIC and C4C_ALLOC_DYNAMIC.
 * - C4C_ALLOC_STATIC: define this macro BEFORE the container's declaration and
 *   implementation files SPECIFING a number in the macro which will end up
 *   being the memory pool capacity.
 * - C4C_ALLOC_DYNAMIC: define this macro BEFORE the container's declaration and
 *   implementation files SPECIFING the number of elements to allocate foreach
 *   allocation call.
 * - By default these containers will have C4C_ALLOC_DYNAMIC defined with the
 *   value: 1.
 *
 * TODOs, FAQs, and stuff:
 * - I will add more and more containers as I need them. If you have created
 *   your own container please feel free to submit it. However when you do
 *   please submit also an example file and make sure your container's functions
 *   are properly documented.
 * - As you have probably already noticed, I'm not a native English speaker!
 *   from time to time I WILL make errors of some sort (from simple typing
 *   errors to completely mess up entire sentences). Pull requests with such
 *   corrections are VERY appreciated.
 * - When version 1.0.0 will be released? As of now, this library is still in
 *   beta. This means that, hypothetically, the entire library may change from a
 *   commit to another! (I'll try to not make it happen though). Version 1.0.0
 *   will be published when:
 *   - There will be enough container variants.
 *   - There will be enough examples (at least one for each container type).
 *   - Typing errors, bugs and such will be completely (mostly) debellated.
 *
 * @note This library uses <a href="https://semver.org/">Semantic Versioning
 *       2.0.0</a>
 */

#define _C4C_STR_(x) #x
#define _C4C_STR _C4C_STR_

#define _C4C_CONCAT_(a, b) a##b
#define _C4C_CONCAT _C4C_CONCAT_

#define _C4C_CONCAT3_(a, b, c) a##b##c
#define _C4C_CONCAT3 _C4C_CONCAT3_

#define _C4C_VERSION_MAJOR 0
#define _C4C_VERSION_MINOR 6
#define _C4C_VERSION_PATCH 1
#define _C4C_VERSION_STATE "beta"

#define _C4C_MAKE_VERSION_STR(major, minor, patch) \
	_C4C_STR(major) "." \
	_C4C_STR(minor) "." \
	_C4C_STR(patch) "-" \
	_C4C_VERSION_STATE

#define _C4C_VERSION_STR \
	_C4C_MAKE_VERSION_STR(_C4C_VERSION_MAJOR, _C4C_VERSION_MINOR, _C4C_VERSION_PATCH)

#define _C4C_MAKE_VERSION(major, minor, patch) \
	((major) << 16) | ((minor) << 8) | (patch))

#define _C4C_VERSION \
	_C4C_MAKE_VERSION(_C4C_VERSION_MAJOR, _C4C_VERSION_MINOR, _C4C_VERSION_PATCH)

/*------------------------------------------------------------------------------
	C4C errors API
------------------------------------------------------------------------------*/

/**
 * Error codes.
 * 
 * C4CE prefixes indicate the function's couldn't do its job.
 * C4CEW prefixes indicate the function's may have behaved slightly different from 
 * what you may have expected.
 */
typedef enum {
	/**
	 * The container is already empty.
	 */
	C4CE_EMPTY 							= -7,

	/**
	 * The container is already full. Try resizing it (if dynamic).
	 */
	C4CE_FULL 							= -6,

	/**
	 * C4C_ALLOC_STATIC/DYNAMIC can generate this error.
	 * Creating a static container with C4C_ALLOC_STATIC and trying to resize it 
	 * is the classic example of this behavior (can't resize a static array).
	 */
	C4CE_CANT_DO 						= -5,

	/**
	 * The function has been called with an invalid argument.
	 * Check the function's documentation for more info.
	 */
	C4CE_INVALID_ARG 					= -4,

	/**
	 * Index > capacity.
	 */
	C4CE_INDEX_OUT_OF_BOUNDS 			= -3,

	/**
	 * C4C_REALLOC() failed.
	 */
	C4CE_REALLOC_FAIL 					= -2,

	/**
	 * C4C_ALLOC() failed.
	 */
	C4CE_MALLOC_FAIL 					= -1,

	/**
	 * Generic error code.
	 * 
	 * @note Try not to use this pls.
	 */
	C4CE_GENERIC_ERROR 					=  0,

/*----------------------------------------------------------------------------*/

	/**
	 * Everything went ok.
	 */
	C4CE_SUCCESS 						=  1,

/*----------------------------------------------------------------------------*/

	/**
	 * Nothig happened in this function (i.e. the function returned immediately 
	 * because there was no need to do something that has already be done for 
	 * example).
	 * Check the function's documentation to see why and when this can happen.
	 */
	C4CEW_NOTHING 						=  2,

	/**
	 * Due to resizing, some elements were discarded in the process.
	 * See the function's documentation for more info.
	 */
	C4CEW_ELEMS_DISCARDED 				=  3,
} c4c_res_t;

#define c4c_succeeded(fn) \
	((fn) >= C4CE_SUCCESS)

#endif /* __C4C_CONFIG_H__ */
