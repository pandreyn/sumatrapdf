/* Copyright 2014 the unarr project authors (see AUTHORS file).
   License: LGPLv3 */

#include "unarr-internals.h"

#ifdef _WIN32

#include <windows.h>

wchar16_t *ar_conv_utf8_to_utf16(const char *str)
{
    int res = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar16_t *wstr = malloc(res);
    if (wstr)
        MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, res);
    return wstr;
}

char *ar_conv_utf16_to_utf8(const wchar16_t *wstr)
{
    int res = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = malloc(res);
    if (str)
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, res, NULL, NULL);
    return str;
}

char *ar_conv_ansi_to_utf8_utf16(const char *astr, wchar16_t **wstr_opt)
{
    char *str = NULL;
    int res = MultiByteToWideChar(CP_ACP, 0, astr, -1, NULL, 0);
    wchar16_t *wstr = malloc(res * sizeof(wchar16_t));
    if (wstr) {
        MultiByteToWideChar(CP_ACP, 0, astr, -1, wstr, res);
        str = ar_conv_utf16_to_utf8(wstr);
    }
    if (wstr_opt)
        *wstr_opt = wstr;
    else
        free(wstr);
    return str;
}

#else

#error implement string conversion functions

#endif
