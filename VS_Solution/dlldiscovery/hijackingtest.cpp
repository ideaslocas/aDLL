#include "adll.h"

BOOL CopyHDLL(LPCWSTR HDllPath, LPWSTR TestPath)
{
    BOOL CheckCpy = CopyFile(HDllPath, TestPath, TRUE);
    if (CheckCpy == 0)
    {
        PrintError("CopyFile() copying the DLL into the application");
        return FALSE;
    }
    return TRUE;
}

BOOL LoadExecutable(LPCWSTR FilePath)
{
    PROCESS_INFORMATION Pinfo;
    STARTUPINFO         Sinfo;
    BOOL                check;
    DWORD               ExitCode;

    SecureZeroMemory(&Sinfo, sizeof(STARTUPINFO));
    SecureZeroMemory(&Pinfo, sizeof(PROCESS_INFORMATION));
    Sinfo.cb = sizeof(STARTUPINFO);
    Sinfo.dwFlags = STARTF_USESHOWWINDOW;
    Sinfo.wShowWindow = SW_HIDE;
    check = CreateProcess(
        FilePath,
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &Sinfo,
        &Pinfo);
    if (!check)
    {
        PrintError("TestInformer - CreateProcess()");
        return FALSE;
    }
    ResumeThread(Pinfo.hThread);
    Sleep(2500);
    GetExitCodeProcess(Pinfo.hProcess, &ExitCode);
    TerminateProcess(Pinfo.hProcess, ExitCode);
    CloseHandle(&Sinfo);
    CloseHandle(&Pinfo);
    return TRUE;
}

BOOL CheckTmpExist()
{
    WCHAR	PathFile[512] = { 0 };
    WCHAR	PathBuff[MAX_PATH] = { 0 };
    LPCWSTR	TmpName = L"informer.tmp";

    GetTempPathW(MAX_PATH, PathBuff);
    wcscpy_s(PathFile, 512, PathBuff);
    wcscat_s(PathFile, 512, TmpName);
    if (!(PathFileExistsW(PathFile)))
        return FALSE;
    else
        DeleteFileW(PathFile);
    return TRUE;
}

BOOL HijackingTest(ARGS Args, WORD Arch, LPWSTR NotFoundBuff)
{
    LPCWSTR HDllPath;

    // If user did not set a custom dll aDLL will use the informer.dll
    if (!Args.DPath)
        HDllPath = Arch == 32 ? _wcsdup(L".\\informer32.dll") : _wcsdup(L".\\informer64.dll");
    else
        HDllPath = _wcsdup(Args.DPath);
    // Parse the NotFoundBuff to get a DLL name to test with and the DLL path where it was not found
    LPWSTR Token = NULL;
    LPWSTR NextToken = NULL;
    WCHAR DllName[_MAX_FNAME] = { 0 };
    WCHAR NotFoundPath[MAX_PATH] = { 0 };

    // Split each line in NotFoundBuff. Format of each line is "- DLLname NOT FOUND in DLLPath"
    Token = wcstok_s(NotFoundBuff, L" ", &NextToken);
    while (Token)
    {
        Token = wcstok_s(NULL, L" ", &NextToken);   //Token = DLLname
        wcscpy_s(DllName, _MAX_FNAME, Token);
        Token = wcstok_s(NULL, L" ", &NextToken);   //Token = "Not"
        Token = wcstok_s(NULL, L" ", &NextToken);   //Token = "Found"
        Token = wcstok_s(NULL, L" ", &NextToken);   //Token = "in"
        Token = wcstok_s(NULL, L"\n", &NextToken);  //Token = DLLPath
        wcscpy_s(NotFoundPath, MAX_PATH, Token);
        Token = wcstok_s(NULL, L" ", &NextToken);   //Token = "-"

        // Copy the malicious DLL into the directory where legit DLL was not found and execute the program
        printf("[+] Testing DLL Hijacking with %ws as %ws\n", HDllPath, NotFoundPath);
        CopyHDLL(HDllPath, NotFoundPath);
        LoadExecutable(Args.EPath);

        // When testing with informer.dll check if the temporary file was created as a proof of execution
        if (!(Args.DPath))
        {
            if (CheckTmpExist())
                printf("[+] [SUCCESS] - %ws is vulnerable to simple DLL Hijacking\n\n", DllName);
            else
                printf("[-] [FAILED] - %ws does not seem vulnerable to simple DLL Hijacking\n\n", DllName);
        }
        Sleep(500);
        DeleteFileW(NotFoundPath);
    }
    if (HDllPath)
    {
        free((PVOID)HDllPath);
    }
    return TRUE;
}
