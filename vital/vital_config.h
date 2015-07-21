/*ckwg +29
 * Copyright 2015 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VITAL_VITAL_CONFIG_H
#define VITAL_VITAL_CONFIG_H

// Support macros.
#if defined(_WIN32) || defined(_WIN64)
#define VITAL_NO_RETURN __declspec(noreturn)
// Unsupported.
#define VITAL_MUST_USE_RESULT
// Unsupported.
#define VITAL_UNUSED
#elif defined(__GNUC__)
#define VITAL_NO_RETURN __attribute__((__noreturn__))
#define VITAL_MUST_USE_RESULT __attribute__((__warn_unused_result__))
#define VITAL_UNUSED __attribute__((__unused__))
#else
// Unsupported.
#define VITAL_NO_RETURN
// Unsupported.
#define VITAL_MUST_USE_RESULT
// Unsupported.
#define VITAL_UNUSED
#endif

#if __cplusplus < 201103L
#define VITAL_NOTHROW throw ()
#define VITAL_DEFAULT_DTOR {}
#else
#define VITAL_NOTHROW noexcept
#define VITAL_DEFAULT_DTOR = default

#endif

#endif // VITAL_VITAL_CONFIG_H
