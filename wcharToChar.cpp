#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>
#include <locale.h> // for setlocale | selocale func encoding UTF-8
#pragma comment(lib, "User32.lib")


wchar_t* CharToWchar(const char* pstrSrc)
{
    assert(pstrSrc);
    int nLen = strlen(pstrSrc) + 1;

    wchar_t* pwstr = (LPWSTR)malloc(sizeof(wchar_t) * nLen);
    mbstowcs(pwstr, pstrSrc, nLen);

    return pwstr;
}

int main(void)
{
    _tprintf(TEXT(".txt = %s\n"), CharToWchar("txt"));
    _tprintf(TEXT(".docx = %s\n"), CharToWchar("docx"));
}