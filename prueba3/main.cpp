#ifndef WLAN_PROFILE_GET_PLAINTEXT_KEY
#define WLAN_PROFILE_GET_PLAINTEXT_KEY 4 // Dont have the latest platform SDK on this box
#endif

#pragma comment(lib, "wlanapi.lib")

#include <stdio.h>
#include <windows.h>
#include <wlanapi.h>

BOOL IsElevated()
{
    DWORD dwSize = 0;
    HANDLE hToken = NULL;
    BOOL bReturn = FALSE;

    TOKEN_ELEVATION tokenInformation;

    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
        return FALSE;

    if(GetTokenInformation(hToken, TokenElevation, &tokenInformation, sizeof(TOKEN_ELEVATION), &dwSize))
    {
        bReturn = (BOOL)tokenInformation.TokenIsElevated;
    }

    CloseHandle(hToken);
    return bReturn;
}

bool IsVistaOrHigher()
{
    OSVERSIONINFO osVersion; ZeroMemory(&osVersion, sizeof(OSVERSIONINFO));
    osVersion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if(!GetVersionEx(&osVersion))
        return false;

    if(osVersion.dwMajorVersion >= 6)
        return true;
    return false;
}

int main(int argc, char *argv[])
{
    HANDLE hWlan = NULL;

    DWORD dwError = 0;
    DWORD dwSupportedVersion = 0;
    DWORD dwClientVersion = (IsVistaOrHigher() ? 2 : 1);

    GUID guidInterface; ZeroMemory(&guidInterface, sizeof(GUID));

    WLAN_INTERFACE_INFO_LIST *wlanInterfaceList = (WLAN_INTERFACE_INFO_LIST*)WlanAllocateMemory(sizeof(WLAN_INTERFACE_INFO_LIST));
    ZeroMemory(wlanInterfaceList, sizeof(WLAN_INTERFACE_INFO_LIST));

    WLAN_PROFILE_INFO_LIST *wlanProfileList = (WLAN_PROFILE_INFO_LIST*)WlanAllocateMemory(sizeof(WLAN_PROFILE_INFO_LIST));
    ZeroMemory(wlanProfileList, sizeof(WLAN_PROFILE_INFO_LIST));

    if(!IsElevated()) printf("[!] Running without administrative rights\n");
    try
    {
        if(dwError = WlanOpenHandle(dwClientVersion, NULL, &dwSupportedVersion, &hWlan) != ERROR_SUCCESS)
            throw("[x] Unable access wireless interface");

        if(dwError = WlanEnumInterfaces(hWlan, NULL, &wlanInterfaceList) != ERROR_SUCCESS)
            throw("[x] Unable to enum wireless interfaces");

        if(wlanInterfaceList->dwNumberOfItems == 0) // Almost missed this before posting
            throw("[x] No wireless adapters detected");

        if(dwError = WlanGetProfileList(hWlan, &guidInterface, NULL, &wlanProfileList) != ERROR_SUCCESS)
            throw("[x] Unable to get profile list");

        LPWSTR profileXML;

        printf("\nNetwork\t\t\t\t\tPassword\n\n");
        for(int i = 0; i < wlanProfileList->dwNumberOfItems; i++)
        {
            DWORD dwFlags = WLAN_PROFILE_GET_PLAINTEXT_KEY, dwAccess = 0;

            wprintf(L"%s", wlanProfileList->ProfileInfo[i].strProfileName);
            int j = 20 - wcslen(wlanProfileList->ProfileInfo[i].strProfileName);

            for(int k = 0; k < j; k++)
                printf(" ");

            if(IsElevated())
            {
                if(WlanGetProfile(hWlan, &guidInterface, wlanProfileList->ProfileInfo[i].strProfileName,
                                  NULL, &profileXML, &dwFlags, &dwAccess) == ERROR_SUCCESS)
                {

                    // This is really half assed but I'm really hungover
                    WCHAR *pszStr = wcstok(profileXML, L"<>");
                    while(pszStr) {
                        if(!wcscmp(pszStr, L"keyMaterial")) {
                            pszStr = wcstok(NULL, L"<>");
                            wprintf(L"\t\t\t%s\n", pszStr);
                            break;
                        }
                        pszStr = wcstok(NULL, L"<>");
                    }
                    WlanFreeMemory(profileXML);
                }
            }
            else
            {
                printf("\t\t\tAccess Denied.\n");
            }
        }

    }
    catch(char *szError)
    {
        printf("%s (0x%X)\nQuitting...\n", szError);
    }

    if(wlanProfileList)
        WlanFreeMemory(wlanProfileList);
    if(wlanInterfaceList)
        WlanFreeMemory(wlanInterfaceList);
    if(hWlan)
        WlanCloseHandle(hWlan, NULL);

    return dwError;
}
