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

#ifndef __C4C_CONFIG_H__
#define __C4C_CONFIG_H__

/**
 * @file
 *
 * Common file patterns:
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
 * - Files with the literal_ prefix are to be used with non-nullable values (NO
 *   pointers).
 * - Files with the nullable_ prefix are to be used with pointers values
 *   (nullables).
 * - dyn_ prefixes indicates that the container WILL use malloc/free to
 *   allocate/deallocate memory at runtime. Otherwise you'll have a
 *   C4C_PARAM_MAX_SIZE or similiar to #define in order to specify the memory
 *   pool's capacity (cannot change at runtime).
 * - Every container's function is wrapped inside a fully customizable
 *   C4C_METHOD macro and with its Doxygen format comment explaining how to
 *   properly use it.
 * - Note that EVERY container WILL NOT allocate elements upon insertion nor
 *   free them upon deletion. Is your responsability to handle their lifecycle
 *   making sure they don't run out of scope after inserted or freed without
 *   removing the pointer in the container. In the future I may implement some
 *   sort of generic customizable allocator/deallocator in order to lift this
 *   job off the programmer and to make a more seamless integration with the
 *   containers (something like C++ std allocators maybe?). For now the
 *   containers inside this library have ONE and only one purpose: to keep your
 *   variables/pointers/etc... organized inside a lightweight, fast and
 *   customizable structure making it easy for the programmer to access them
 *   whenever he wants to.
 *
 * <br><br><br>
 *
 * Common macro patterns:
 * - Macros prefixed with an underscore are not to be modified.
 * - Macros postfixed with an underscore are for internal usage.
 * - Macros prefixed and postfixed with a double underscore are header guards.
 * - Macros prefixed with '_C4C_SETTINGS_' can be defined before including the
 *   header to enable some frequently used pattern.
 * - Files with the .inl extension are 'template' headers. Include them in the
 *   project, look at the end of those files and you'll see macros like '#undef
 *   C4C_PARAM_xxx' each with its own comment specifying what it does and what
 *   values you can put in (with some examples too). These macros must be
 *   correctly #defined before including the .inl file. Note that these macros
 *   will automatically get #undefined after each include of the .inl file.
 * - Macros starting with 'C4C_' can be custom defined before including the .h
 *   file to customize their behavior. Remember to manually #undefine them when
 *   no longer needed.
 * - Note that currently, the only header with an include guard is config.h. Any
 *   other file can be included more than once (so you can customize macros) so
 *   the preprocessor might slow down a bit if they are excessively included
 *   everywhere (though not that much since they are all very small files).
 *
 * <br><br><br>
 *
 * C4C errors API:
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
 * <br><br><br>
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
 * - As already said previously I plan to add some sort of generic
 *   allocator/deallocator system which will automically allocate on the heap
 *   your struct (and initialize it) every time you push to a container and free
 *   it whenever you call pop. Not sure when but I already have an idea although
 *   not sure it is going to be a good nor a working one.
 *
 * @note This library uses <a href="https://semver.org/">Semantic Versioning
 *       2.0.0</a>
 */

#define _C4C_STR_(x) #x
#define _C4C_STR _C4C_STR_

#define _C4C_CONCAT_(a, b) a##b
#define _C4C_CONCAT _C4C_CONCAT_

#define _C4C_VERSION_MAJOR 0
#define _C4C_VERSION_MINOR 3
#define _C4C_VERSION_PATCH 0
#define _C4C_VERSION_STATE "beta"

#define _C4C_VERSION_STR \
	_C4C_STR(_C4C_VERSION_MAJOR) "." \
	_C4C_STR(_C4C_VERSION_MINOR) "." \
	_C4C_STR(_C4C_VERSION_PATCH) "-" \
	_C4C_VERSION_STATE

#define _C4C_VERSION_MAKE(maj, min, patch) \
	((maj) << 16) | ((min) << 8) | (patch))

/*------------------------------------------------------------------------------
	C4C errors API
------------------------------------------------------------------------------*/

typedef enum {
	/* <= 0 is an error. Check the function's doc for more info. */
	c4c_success = 1
	/* > 1 is a success but a corner case happened.
	 * Might not get what you expected. Check the function's doc for more info.
	 */
} c4c_res_t;

#define c4c_succeeded(fn) \
	((fn) >= c4c_success)

#endif /* __C4C_CONFIG_H__ */
