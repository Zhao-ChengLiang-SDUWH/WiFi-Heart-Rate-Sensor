/* Copyright (C) ARM Ltd., 1999,2014 */
/* All rights reserved */

/*
 * RCS $Revision$
 * Checkin $Date$
 * Revising $Author: agrant $
 */

#ifndef __stdint_h
#define __stdint_h
#define __ARMCLIB_VERSION 5060037

  #ifdef __INT64_TYPE__
    /* armclang predefines '__INT64_TYPE__' and '__INT64_C_SUFFIX__' */
    #define __INT64 __INT64_TYPE__
  #else
    /* armcc has builtin '__int64' which can be used in --strict mode */
    #define __INT64 __int64
    #define __INT64_C_SUFFIX__ ll
  #endif
  #define __PASTE2(x, y) x ## y
  #define __PASTE(x, y) __PASTE2(x, y)
  #define __INT64_C(x)  __ESCAPE__(__PASTE(x, __INT64_C_SUFFIX__))
  #define __UINT64_C(x)  __ESCAPE__(__PASTE(x ## u, __INT64_C_SUFFIX__))
  #if defined(__clang__) || (defined(__ARMCC_VERSION) && !defined(__STRICT_ANSI__))
    /* armclang and non-strict armcc allow 'long long' in system headers */
    #define __LONGLONG long long
  #else
    /* strict armcc has '__int64' */
    #define __LONGLONG __int64
  #endif

  #ifndef __STDINT_DECLS
  #define __STDINT_DECLS

    #undef __CLIBNS

    #ifdef __cplusplus
      namespace std {
          #define __CLIBNS std::
          extern "C" {
    #else
      #define __CLIBNS
    #endif  /* __cplusplus */


/*
 * 'signed' is redundant below, except for 'signed char' and if
 * the typedef is used to declare a bitfield.
 */

    /* 7.18.1.1 */

    /* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;

    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;


    /* 7.18.1.2 */

    /* smallest type of at least n bits */
    /* minimum-width signed integer types */
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;


    /* minimum-width unsigned integer types */
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;


    /* 7.18.1.3 */

    /* fastest minimum-width signed integer types */
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;


    /* fastest minimum-width unsigned integer types */
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;


    /* 7.18.1.4 integer types capable of holding object pointers */

