/*
** KOL LIB
*/
#ifndef _KOL_H_
#define _KOL_H_

#include <windows.h>
#include <cstdint>
#include "user.h"

struct PackageUnitEntry{
    void *Init;  // initializing
    void *FInit; // finalizing 
};

typedef struct PackageInfoTable{
    uint32_t UnitCount;
    PackageUnitEntry *UnitEntryTable;
} PackageInfoTable, *PackageInfo;

typedef struct TLibModule {
	TLibModule *Next;
	HMODULE Instance;
	HINSTANCE CodeInstance;
	HINSTANCE DataInstance;
	HINSTANCE ResInstance;
	uint32_t Reserved;
} TLibModule, *PLibModule;

typedef struct TExcFrame {
  TExcFrame *next;
  void *TExcDest;
  void *stackFrame;
} TExcFrame, *PExcFrame;


namespace Chunk {

	typedef struct TInitContext	{
		TInitContext *OuterContext;
		PExcFrame ExcFrame;
		PackageInfo InitTable;
		uint32_t InitCount;
		PLibModule Module;
	} TInitContext, *PInitContext;

}
/*
struct Info {
  void *ExceptProc;
  void *ErrorProc;
  void *ExceptClsProc;
  void *ExceptObjProc;
  stubptr ExceptionClass; 
  void *SafeCallErrorProc;
  void *AssertErrorProc;
  void *AbstractErrorProc;
  HMODULE HPrevInst;    
  HMODULE MainInstance; 
  stubptr MainThreadID; 
  bool IsLibrary;     
};*/
#endif
