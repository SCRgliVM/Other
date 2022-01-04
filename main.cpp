#include <stdio.h>

#include "KOL.h"
#include "user.h"

namespace SysInit {
    void InitExe(PackageInfo InitTable);
    void InitializeModule();
    void RegisterModule(PLibModule LibModule);
    void StartExe(PackageInfo InitTable, PLibModule Module);
}

PackageUnitEntry UnitEntryTable[31] = {0};
PackageInfoTable InitTable = {31, UnitEntryTable};
int TlsIndex = -1;
TLibModule Module = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    0
};
PLibModule LibModuleList = NULL;

HMODULE HInstance;
Chunk::TInitContext InitContext;
void (*pRaiseException)(DWORD dwExceptionCode,
                        DWORD dwExceptionFlags,
                        DWORD nNumberOfArguments,
                        const ULONG_PTR *lpArguments);
void (*pRtlUnwind)(PVOID TargetFrame,
                   PVOID TargetIp,
                   PEXCEPTION_RECORD ExceptionRecord,
                   PVOID ReturnValue);
HMODULE MainInstance;

int main(){
    SysInit::InitExe(&InitTable);
}

void SysInit::InitExe(PackageInfo InitTable){
    TlsIndex = 0;
    HInstance = GetModuleHandleW(NULL);
    Module.Instance = HInstance;
    Module.CodeInstance = NULL;
    Module.DataInstance = NULL;
    SysInit::InitializeModule();
    SysInit::StartExe(InitTable, &Module);
}

void SysInit::InitializeModule()
/* Create linked list and append current module how first element  */
{
    SysInit::RegisterModule(&Module);
}

void SysInit::RegisterModule(PLibModule LibModule)
/* Create linked list and append module how first element */
{
  LibModule->Next = LibModuleList;
  LibModuleList = LibModule->Next;
}

void SysInit::StartExe(PackageInfo InitTable, PLibModule Module){
    pRaiseException = RaiseException;
    pRtlUnwind = RtlUnwind;
    InitContext.InitTable = InitTable;
    InitContext.InitCount = 0;
    InitContext.Module = Module;
    MainInstance = Module->Instance;
}