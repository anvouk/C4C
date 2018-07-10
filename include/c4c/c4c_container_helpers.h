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

#ifndef __C4C_CONTAINER_HELPERS_H__
#define __C4C_CONTAINER_HELPERS_H__

#include "c4c/c4c_config.h"
#include "c4c/c4c_function.h"
#include "c4c/c4c_struct.h"

#ifndef C4C_METHOD
#define C4C_METHOD(struct_raw_name, rettype, method_suffix, ...) \
	C4C_FUNCTION(rettype, _C4C_CONCAT(struct_raw_name, method_suffix), C4C_STRUCT_DECLARE(struct_raw_name)* __VA_ARGS__)
#endif

#ifndef C4C_METHOD_CALL
#define C4C_METHOD_CALL(struct_raw_name, method_suffix, ...) \
	C4C_FUNCTION_CALL(_C4C_CONCAT(struct_raw_name, method_suffix), __VA_ARGS__)
#endif

#endif /* __C4C_CONTAINER_HELPERS_H__ */
