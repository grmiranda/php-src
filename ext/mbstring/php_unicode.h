/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Wez Furlong (wez@thebrainroom.com)                           |
   +----------------------------------------------------------------------+

	Based on code from ucdata-2.5, which has the following Copyright:

	Copyright 2001 Computing Research Labs, New Mexico State University

	Permission is hereby granted, free of charge, to any person obtaining a
	copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation
	the rights to use, copy, modify, merge, publish, distribute, sublicense,
	and/or sell copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
*/

#ifndef PHP_UNICODE_H
#define PHP_UNICODE_H

#if HAVE_MBSTRING

#define UC_MN  0 /* Mark, Non-Spacing          */
#define UC_MC  1 /* Mark, Spacing Combining    */
#define UC_ME  2 /* Mark, Enclosing            */
#define UC_ND  3 /* Number, Decimal Digit      */
#define UC_NL  4 /* Number, Letter             */
#define UC_NO  5 /* Number, Other              */
#define UC_ZS  6 /* Separator, Space           */
#define UC_ZL  7 /* Separator, Line            */
#define UC_ZP  8 /* Separator, Paragraph       */
#define UC_CC  9 /* Other, Control             */
#define UC_CF 10 /* Other, Format              */
#define UC_OS 11 /* Other, Surrogate           */
#define UC_CO 12 /* Other, Private Use         */
#define UC_CN 13 /* Other, Not Assigned        */
#define UC_LU 14 /* Letter, Uppercase          */
#define UC_LL 15 /* Letter, Lowercase          */
#define UC_LT 16 /* Letter, Titlecase          */
#define UC_LM 17 /* Letter, Modifier           */
#define UC_LO 18 /* Letter, Other              */
#define UC_PC 19 /* Punctuation, Connector     */
#define UC_PD 20 /* Punctuation, Dash          */
#define UC_PS 21 /* Punctuation, Open          */
#define UC_PE 22 /* Punctuation, Close         */
#define UC_PO 23 /* Punctuation, Other         */
#define UC_SM 24 /* Symbol, Math               */
#define UC_SC 25 /* Symbol, Currency           */
#define UC_SK 26 /* Symbol, Modifier           */
#define UC_SO 27 /* Symbol, Other              */
#define UC_L  28 /* Left-To-Right              */
#define UC_R  29 /* Right-To-Left              */
#define UC_EN 30 /* European Number            */
#define UC_ES 31 /* European Number Separator  */
#define UC_ET 32 /* European Number Terminator */
#define UC_AN 33 /* Arabic Number              */
#define UC_CS 34 /* Common Number Separator    */
#define UC_B  35 /* Block Separator            */
#define UC_S  36 /* Segment Separator          */
#define UC_WS 37 /* Whitespace                 */
#define UC_ON 38 /* Other Neutrals             */
/*
 * Implementation specific character properties.
 */
#define UC_CM 39 /* Composite                  */
#define UC_NB 40 /* Non-Breaking               */
#define UC_SY 41 /* Symmetric                  */
#define UC_HD 42 /* Hex Digit                  */
#define UC_QM 43 /* Quote Mark                 */
#define UC_MR 44 /* Mirroring                  */
#define UC_SS 45 /* Space, other               */
#define UC_CP 46 /* Defined                    */

/*
 * Added for UnicodeData-2.1.3.
 */
#define UC_PI 47 /* Punctuation, Initial       */
#define UC_PF 48 /* Punctuation, Final         */

MBSTRING_API int php_unicode_is_prop(unsigned long code, ...);
MBSTRING_API int php_unicode_is_prop1(unsigned long code, int prop);

MBSTRING_API char *php_unicode_convert_case(
		int case_mode, const char *srcstr, size_t srclen, size_t *retlen,
		const mbfl_encoding *src_encoding);

#define PHP_UNICODE_CASE_UPPER	0
#define PHP_UNICODE_CASE_LOWER	1
#define PHP_UNICODE_CASE_TITLE	2

/* Optimize the common ASCII case for lower/upper */

static inline int php_unicode_is_lower(unsigned long code) {
	if (code < 0x80) {
		return code >= 0x61 && code <= 0x7A;
	} else {
		return php_unicode_is_prop1(code, UC_LL);
	}
}

static inline int php_unicode_is_upper(unsigned long code) {
	if (code < 0x80) {
		return code >= 0x41 && code <= 0x5A;
	} else {
		return php_unicode_is_prop1(code, UC_LU);
	}
}

#define php_unicode_is_alpha(cc) php_unicode_is_prop(cc, UC_LU, UC_LL, UC_LM, UC_LO, UC_LT, -1)
#define php_unicode_is_digit(cc) php_unicode_is_prop1(cc, UC_ND)
#define php_unicode_is_alnum(cc) php_unicode_is_prop(cc, UC_LU, UC_LL, UC_LM, UC_LO, UC_LT, UC_ND, -1)
#define php_unicode_is_cntrl(cc) php_unicode_is_prop(cc, UC_CC, UC_CF, -1)
#define php_unicode_is_space(cc) php_unicode_is_prop(cc, UC_ZS, UC_SS, -1)
#define php_unicode_is_blank(cc) php_unicode_is_prop1(cc, UC_ZS)
#define php_unicode_is_punct(cc) php_unicode_is_prop(cc, UC_PD, UC_PS, UC_PE, UC_PO, UC_PI, UC_PF, -1)
#define php_unicode_is_graph(cc) php_unicode_is_prop(cc, UC_MN, UC_MC, UC_ME, UC_ND, UC_NL, UC_NO, \
                               UC_LU, UC_LL, UC_LT, UC_LM, UC_LO, UC_PC, UC_PD, \
                               UC_PS, UC_PE, UC_PO, UC_SM, UC_SM, UC_SC, UC_SK, \
                               UC_SO, UC_PI, UC_PF, -1)
#define php_unicode_is_print(cc) php_unicode_is_prop(cc, UC_MN, UC_MC, UC_ME, UC_ND, UC_NL, UC_NO, \
                               UC_LU, UC_LL, UC_LT, UC_LM, UC_LO, UC_PC, UC_PD, \
                               UC_PS, UC_PE, UC_PO, UC_SM, UC_SM, UC_SC, UC_SK, \
                               UC_SO, UC_ZS, UC_PI, UC_PF, -1)
#define php_unicode_is_title(cc) php_unicode_is_prop1(cc, UC_LT)
#define php_unicode_is_xdigit(cc) php_unicode_is_prop1(cc, UC_HD)

#define php_unicode_is_isocntrl(cc) php_unicode_is_prop1(cc, UC_CC)
#define php_unicode_is_fmtcntrl(cc) php_unicode_is_prop1(cc, UC_CF)

#define php_unicode_is_symbol(cc) php_unicode_is_prop(cc, UC_SM, UC_SC, UC_SO, UC_SK, -1)
#define php_unicode_is_number(cc) php_unicode_is_prop(cc, UC_ND, UC_NO, UC_NL, -1)
#define php_unicode_is_nonspacing(cc) php_unicode_is_prop1(cc, UC_MN)
#define php_unicode_is_openpunct(cc) php_unicode_is_prop1(cc, UC_PS)
#define php_unicode_is_closepunct(cc) php_unicode_is_prop1(cc, UC_PE)
#define php_unicode_is_initialpunct(cc) php_unicode_is_prop1(cc, UC_PI)
#define php_unicode_is_finalpunct(cc) php_unicode_is_prop1(cc, UC_PF)

#define php_unicode_is_composite(cc) php_unicode_is_prop1(cc, UC_CM)
#define php_unicode_is_hex(cc) php_unicode_is_prop1(cc, UC_HD)
#define php_unicode_is_quote(cc) php_unicode_is_prop1(cc, UC_QM)
#define php_unicode_is_symmetric(cc) php_unicode_is_prop1(cc, UC_SY)
#define php_unicode_is_mirroring(cc) php_unicode_is_prop1(cc, UC_MR)
#define php_unicode_is_nonbreaking(cc) php_unicode_is_prop1(cc, UC_NB)

/*
 * Directionality macros.
 */
#define php_unicode_is_rtl(cc) php_unicode_is_prop1(cc, UC_R)
#define php_unicode_is_ltr(cc) php_unicode_is_prop1(cc, UC_L)
#define php_unicode_is_strong(cc) php_unicode_is_prop(cc, UC_L, UC_R, -1)
#define php_unicode_is_weak(cc) php_unicode_is_prop(cc, UC_EN, UC_ES, UC_ET, UC_AN, UC_CS, -1)
#define php_unicode_is_neutral(cc) php_unicode_is_prop(cc, UC_B, UC_S, UC_WS, UC_ON, -1)
#define php_unicode_is_separator(cc) php_unicode_is_prop(cc, UC_B, UC_S, -1)

/*
 * Other macros inspired by John Cowan.
 */
#define php_unicode_is_mark(cc) php_unicode_is_prop(cc, UC_MN, UC_MC, UC_ME, -1)
#define php_unicode_is_modif(cc) php_unicode_is_prop1(cc, UC_LM)
#define php_unicode_is_letnum(cc) php_unicode_is_prop1(cc, UC_NL)
#define php_unicode_is_connect(cc) php_unicode_is_prop1(cc, UC_PC)
#define php_unicode_is_dash(cc) php_unicode_is_prop1(cc, UC_PD)
#define php_unicode_is_math(cc) php_unicode_is_prop1(cc, UC_SM)
#define php_unicode_is_currency(cc) php_unicode_is_prop1(cc, UC_SC)
#define php_unicode_is_modifsymbol(cc) php_unicode_is_prop1(cc, UC_SK)
#define php_unicode_is_nsmark(cc) php_unicode_is_prop1(cc, UC_MN)
#define php_unicode_is_spmark(cc) php_unicode_is_prop1(cc, UC_MC)
#define php_unicode_is_enclosing(cc) php_unicode_is_prop1(cc, UC_ME)
#define php_unicode_is_private(cc) php_unicode_is_prop1(cc, UC_CO)
#define php_unicode_is_surrogate(cc) php_unicode_is_prop1(cc, UC_OS)
#define php_unicode_is_lsep(cc) php_unicode_is_prop1(cc, UC_ZL)
#define php_unicode_is_psep(cc) php_unicode_is_prop1(cc, UC_ZP)

#define php_unicode_is_identstart(cc) php_unicode_is_prop(cc, UC_LU, UC_LL, UC_LT, UC_LO, UC_NL, -1)
#define php_unicode_is_identpart(cc) php_unicode_is_prop(cc, UC_LU, UC_LL, UC_LT, UC_LO, UC_NL, \
                                   UC_MN, UC_MC, UC_ND, UC_PC, UC_CF, -1)

#define php_unicode_is_defined(cc) php_unicode_is_prop1(cc, UC_CP)
#define php_unicode_is_undefined(cc) !php_unicode_is_prop1(cc, UC_CP)

/*
 * Other miscellaneous character property macros.
 */
#define php_unicode_is_han(cc) (((cc) >= 0x4e00 && (cc) <= 0x9fff) ||\
                     ((cc) >= 0xf900 && (cc) <= 0xfaff))
#define php_unicode_is_hangul(cc) ((cc) >= 0xac00 && (cc) <= 0xd7ff)


#endif


#endif /* PHP_UNICODE_H */



