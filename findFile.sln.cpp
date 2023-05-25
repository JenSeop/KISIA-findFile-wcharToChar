#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h> 
#include <string.h> // for string func
#include <stdio.h> // for input ouput func
#include <locale.h> // for setlocale | selocale func encoding UTF-8
#include <strsafe.h> // for Windows API
#include <windows.h> // for Windows API
#pragma comment(lib, "User32.lib") // for Windwos API

const TCHAR* path[] = {
    TEXT("C:\\Users\\user\\Documents"),
    TEXT("C:\\Users\\user\\Desktop"),
    TEXT("C:\\Users\\user\\Downloads")
};
#define Documents path[0]
#define Desktop path[1]
#define Downloads path[2]
#define FILE_ATTSTR_TXT L".txt"
#define FILE_ATTSTR_DOCX L".docx"

BOOL IsDirectory(const TCHAR* path)
{
    WIN32_FIND_DATA findFileData;
    HANDLE findFile = FindFirstFile(path, &findFileData);
    FindClose(findFile);

    return (BOOL)(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
} // for Directory Exist

BOOL FindDirectory(const TCHAR* path)
{
    WIN32_FIND_DATA ffd;
    /*
        typedef struct _WIN32_FIND_DATAW {
          DWORD    dwFileAttributes;
          FILETIME ftCreationTime;
          FILETIME ftLastAccessTime;
          FILETIME ftLastWriteTime;
          DWORD    nFileSizeHigh;
          DWORD    nFileSizeLow;
          DWORD    dwReserved0;
          DWORD    dwReserved1;
          WCHAR    cFileName[MAX_PATH];
          WCHAR    cAlternateFileName[14];
          DWORD    dwFileType; // Obsolete. Do not use.
          DWORD    dwCreatorType; // Obsolete. Do not use
          WORD     wFinderFlags; // Obsolete. Do not use
        } WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
    */
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    StringCchLength(path, 260, &length_of_arg);

    if (length_of_arg > (MAX_PATH - 3))
    {
        _tprintf(TEXT("\nDirectory path is too long.\n"));
        return (-1);
    }

    _tprintf(TEXT("\nTarget directory is %s\n\n"), path);

    StringCchCopy(szDir, MAX_PATH, path);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFile(szDir, &ffd);

    do
    {
        if ( wcsstr(ffd.cFileName, FILE_ATTSTR_TXT) 
            || wcsstr(ffd.cFileName, FILE_ATTSTR_DOCX))
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            //_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
            _tprintf(TEXT("  %s\n"), ffd.cFileName);
        }
    } while (FindNextFile(hFind, &ffd) != 0);

    FindClose(hFind);
}

int _tmain(int argc, TCHAR* argv[])
{
    typedef struct TargetFile {
        WCHAR name[MAX_PATH];
        WCHAR path[MAX_PATH];
    };
    setlocale(LC_ALL, "ko-KR"); // UTF-8 Encoding for Korean

    if (IsDirectory(Documents))
        FindDirectory(Documents);
    if (IsDirectory(Desktop))
        FindDirectory(Desktop);
    if (IsDirectory(Downloads))
        FindDirectory(Downloads);
    return (0);
}