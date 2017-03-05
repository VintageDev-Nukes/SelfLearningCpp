#import "Skype4COM.dll"

int _tmain(int argc, _TCHAR* argv[])
{
 // Initialize COM
 CoInitialize(NULL);

 // Create Skype object
 SKYPE4COMLib::ISkypePtr pSkype(__uuidof(SKYPE4COMLib::Skype));

 // Connect to API
 pSkype->Attach(6,VARIANT_TRUE);

 // Print Skype version
 _bstr_t bstrSkypeVersion = pSkype->GetVersion();
 printf("Skype client version %s/n", (char*)bstrSkypeVersion);

 // Print COM wrapper version
 _bstr_t bstrWrapperVersion = pSkype->GetApiWrapperVersion();
 printf("COM wrapper version %s/n", (char*)bstrWrapperVersion);

 // Cleanup
 pSkype = NULL;
 CoUninitialize();

 return 0;
}
