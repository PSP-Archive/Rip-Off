/* SCE CONFIDENTIAL
 PSP(TM) Programmer Tool Runtime Library Release 5.5.0
 *
 *      Copyright (C) 2005 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 */

#ifndef _SCE_LOAD_MODULES_H_
#define _SCE_LOAD_MODULES_H_

#define DEVKIT_PATH "host0:assets/"
#define MODULE_PATH DEVKIT_PATH "psp_module/"

#define LIBFONT_PRX MODULE_PATH "libfont.prx"

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

int load_required_modules(void);
int unload_required_modules(void);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _SCE_LOAD_MODULES_H_ */
