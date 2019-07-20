/* 
 * This file is part of WslInstall project
 * Licensed under the GNU General Public License version 3
 * Copyright (C) 2019 Biswapriyo Nath
 */

#include <Windows.h>
#include <shobjidl_core.h>
#include <shlguid.h>
#include <objidl.h>

HRESULT
WINAPI
CreateLink(PCWSTR LinkFileName)
{
    HRESULT hRes;
    IShellLinkW *pShellLink;
    IPersistFile *pPersistFile;

    hRes = CoInitialize(nullptr);
    hRes = CoCreateInstance(CLSID_ShellLink,
                            nullptr,
                            CLSCTX_INPROC_SERVER,
                            IID_IShellLinkW,
                            (void **)&pShellLink);
    if (hRes < 0)
        return 1;

    hRes = pShellLink->SetShowCmd(SW_SHOWNORMAL);
    hRes = pShellLink->SetIconLocation(L"%SystemRoot%\\System32\\imageres.dll", 137);
    hRes = pShellLink->SetPath(L"\\\\wsl$");

    hRes = pShellLink->QueryInterface(IID_IPersistFile, (void **)&pPersistFile);
    hRes = pPersistFile->Save(LinkFileName, true);

    /* Cleanup */
    pPersistFile->Release();
    pShellLink->Release();
    CoUninitialize();
    return 0;
}

int WINAPI main(void)
{
    HRESULT hRes;
    hRes = CreateLink(L"Distros.lnk");
    return 0;
}
