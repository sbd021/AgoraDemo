#ifndef _CRC32_H_
#define _CRC32_H_

#ifdef __cplusplus
extern "C"{
#endif

DWORD WINAPI GetDataCRC32(LPCVOID lpBuffer, DWORD dwBufferLen, DWORD dwLastCRC32);
DWORD WINAPI GetFileCRC32(LPCTSTR lpFilePath);
DWORD WINAPI GetStringCRC32A(LPCSTR lpString);
DWORD WINAPI GetStringCRC32W(LPCWSTR lpString);

#ifdef __cplusplus
}
#endif

#ifdef UNICODE
#define GetStringCRC32 GetStringCRC32W
#else
#define GetStringCRC32 GetStringCRC32A
#endif

#endif