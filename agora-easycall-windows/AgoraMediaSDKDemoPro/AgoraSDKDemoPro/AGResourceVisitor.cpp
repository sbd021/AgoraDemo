#include "StdAfx.h"
#include "AGResourceVisitor.h"

CAGResourceVisitor::CAGResourceVisitor(void)
{
}

CAGResourceVisitor::~CAGResourceVisitor(void)
{
}

BOOL PASCAL CAGResourceVisitor::SaveResourceToFile(LPCTSTR lpResourceType, WORD wResourceID, LPCTSTR lpFilePath)
{	
	HMODULE hModule = ::GetModuleHandle(NULL);

	if(hModule == NULL)
		return FALSE;

	HRSRC hResrc = ::FindResource(hModule, MAKEINTRESOURCE(wResourceID), lpResourceType);
	if( hResrc == NULL)
		return FALSE;

	HGLOBAL	hGlobal = ::LoadResource(hModule, hResrc);   
	if( hGlobal == NULL )
		return FALSE;

	LPBYTE lpPointer = (LPBYTE)::LockResource( hGlobal );   
	DWORD dwResSize = ::SizeofResource(hModule, hResrc);

	HANDLE hFile = ::CreateFile(lpFilePath, GENERIC_ALL, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwBytesWritten = 0;
	::WriteFile(hFile, lpPointer, dwResSize, &dwBytesWritten, NULL);
	::CloseHandle(hFile);

	return (dwBytesWritten == dwResSize) ? TRUE:FALSE;
}