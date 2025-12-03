///                  CloakDll     -      by Darawk       -       RealmGX.com
//
//      The purpose of CloakDll is to allow the user to hide any loaded
//      module from the windows API.  It works by accessing the modules
//      list stored in the PEB, and subsequently unlinking the module
//      in question from all 4 of the doubly-linked lists that it's a
//      node of.  It then zeroes out the structure and the path/file
//      name of the module in memory.  So that even if the memory where
//      the data about this module used to reside is scanned there will
//      still be no conclusive evidence of it's existence.  At present
//      there is only one weakness that I have found in this method.
//      I'll describe how it may still be possible to discover at least
//      that a module has been hidden, after a brief introduction to how
//      the GetModuleHandle function works.
//
//      *The following information is not documented by Microsoft.  This
//       information consists of my findings while reverse-engineering
//       these functions and some of them may be incorrect and/or
//       subject to change at any time(and is almost definitely different
//       in different versions of windows, and maybe even in different
//       service packs).  I've tried to make my code as version independant
//       as possible but certain parts of it may not work on older versions
//       of windows.  I've tested it on XP SP2 and there i'll guarantee
//       that it works, but on any other versions of windows, it's anyone's
//       guess.*
//
//      GetModuleHandle eventually calls GetModuleHandleExW, which in
//      turn accesses the native API function GetDllHandle, which calls
//      GetDllHandleEx.  And it's not until here, that we actually see
//      anything even begin to look up information about loaded modules.
//      Whenever GetModuleHandle is called, it saves the address of the
//      last ModuleInfoNode structure that it found in a global variable
//      inside of ntdll.  This global variable is the first thing
//      checked on all subsequent calls to GetModuleHandle.  If the
//      handle being requested is not the one that was requested the last
//      time GetDllHandleEx calls the LdrpCheckForLoadedDll function.
//      LdrpCheckForLoadedDll begins by converting the first letter of the
//      module name being requested to uppercase, decrementing it by 1 and
//      AND'ing it with 0x1F.  This effectively creates a 0-based index
//      beginning with the letter 'A'.  The purpose of this is so that
//      the module can first be looked up in a hash table.  The hash table
//      consists entirely of LIST_ENTRY structures.  One for each letter
//      'A' through 'Z'.  The LIST_ENTRY structure points to the first
//      and last modules loaded that begin with the letter assigned to
//      that entry in the hash table.  The Flink member being the first
//      loaded beginning with that letter, and the Blink member being the
//      last.  The code scans through this list until it finds the module
//      that it's looking for.  On the off-chance that it doesn't find it
//      there, or if the boolean argument UseLdrpHashTable is set to false
//      it will begin going through one of the other three lists.  If, at
//      this point it still doesn't find it, it will admit defeat and return
//      0 for the module handle.
//
//      Weakness:  The global variable inside ntdll that caches the pointer
//      to the last module looked up could be used to at least detect the
//      fact that a module has been hidden.  The LdrUnloadDll() function
//      will set this value to 0 when it unloads a module, so if the cache
//      variable points to an empty structure, the only logical conclusion
//      would be a hidden module somewhere in the process.  This could be
//      resolved by using the static address of this variable and simply
//      zeroing it out.  However, this would make the code specific to only
//      one version of windows.  You could also scan the address space of
//      ntdll for any occurences of the base address(aka module handle)
//      of the module you're hiding.  However, this would be slow and it
//      would clutter up the CloakDll_stub function, because it'd have to
//      all be done manually.  And i'd have to either use a static base
//      address for ntdll...which would probably work on most versions
//      of windows, however I really don't like using static addresses.  
//      Or i'd have to manually locate it by writing my own unicode
//      string comparison code, to lookup ntdll in the list by it's name.
//      Realistically though anyone trying to detect this way would run
//      into the same problem.  That their code would not be version
//      independant.  So, it's unlikely to see any largescale deployment
//      of such a technique.  However, anyone who would like to solve
//      this problem themselves is perfectly free, and encouraged to do
//      so.
 
#include <windows.h>
#include <winnt.h>
#include <tlhelp32.h>
#include <shlwapi.h>
 
 
#pragma comment(lib, "shlwapi.lib")
 
#define UPPERCASE(x) if((x) >= 'a' && (x) <= 'z') (x) -= 'a' - 'A'
#define UNLINK(x) (x).Blink->Flink = (x).Flink; \
        (x).Flink->Blink = (x).Blink;
       
#pragma pack(push, 1)

 
 
#pragma pack(pop)
 
bool CloakDll_stub(HMODULE);
void _fastcall CD_stubend();
 
bool CloakDll(char *, char *);
unsigned long GetProcessIdFromProcname(char *);
HMODULE GetRemoteModuleHandle(unsigned long, char *);
 

 
bool CloakDll(char *process, char *dllName)
{
        PathStripPath(dllName);
 
        unsigned long procId;
        procId = GetProcessIdFromProcname(process);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
 
        //      Calculate the length of the stub by subtracting it's address
        //      from the beginning of the function directly ahead of it.
        //
        //      NOTE: If the compiler compiles the functions in a different
        //      order than they appear in the code, this will not work as
        //      it's supposed to.  However, most compilers won't do that.
        unsigned int stubLen = (unsigned long)CD_stubend - (unsigned long)CloakDll_stub;
 
        //      Allocate space for the CloakDll_stub function
        void _fastcall *stubAddress = VirtualAllocEx(hProcess,
                NULL,
                stubLen,
                MEM_RESERVE | MEM_COMMIT,
                PAGE_EXECUTE_READWRITE);
 
        //      Write the stub's code to the page we allocated for it
        WriteProcessMemory(hProcess, stubAddress, CloakDll_stub, stubLen, NULL);
 
        HMODULE hMod = GetRemoteModuleHandle(procId, dllName);
 
        //      Create a thread in the remote process to execute our code
        CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)stubAddress, hMod, 0, NULL);
 
        //      Clean up after ourselves, so as to leave as little impact as possible
        //      on the remote process
        VirtualFreeEx(hProcess, stubAddress, stubLen, MEM_RELEASE);
        return true;
}
 
bool CloakDll_stub(HMODULE hMod)
{
        ProcessModuleInfo *pmInfo;
        ModuleInfoNode *module;
 
        _asm
        {
                mov eax, fs:[18h]               // TEB
                mov eax, [eax + 30h]    // PEB
                mov eax, [eax + 0Ch]    // PROCESS_MODULE_INFO
                mov pmInfo, eax
        }
 
    module = (ModuleInfoNode *)(pmInfo->LoadOrder.Flink);
       
        while(module->baseAddress && module->baseAddress != hMod)
                module = (ModuleInfoNode *)(module->LoadOrder.Flink);
 
        if(!module->baseAddress)
                return false;
 
        //      Remove the module entry from the list here
        ///////////////////////////////////////////////////    
        //      Unlink from the load order list
        UNLINK(module->LoadOrder);
        //      Unlink from the init order list
        UNLINK(module->InitOrder);
        //      Unlink from the memory order list
        UNLINK(module->MemoryOrder);
        //      Unlink from the hash table
        UNLINK(module->HashTable);
 
        //      Erase all traces that it was ever there
        ///////////////////////////////////////////////////
 
        //      This code will pretty much always be optimized into a rep stosb/stosd pair
        //      so it shouldn't cause problems for relocation.
        //      Zero out the module name
        memset(module->fullPath.Buffer, 0, module->fullPath.Length);
        //      Zero out the memory of this module's node
        memset(module, 0, sizeof(ModuleInfoNode));     
 
        return true;
}
 
__declspec(naked) void _fastcall CD_stubend() { }
 
unsigned long GetProcessIdFromProcname(char *procName)
{
   PROCESSENTRY32 pe;
   HANDLE thSnapshot;
   BOOL retval, ProcFound = false;
 
   thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
 
   if(thSnapshot == INVALID_HANDLE_VALUE)
   {
      MessageBox(NULL, "Error: unable to create toolhelp snapshot", "Loader", NULL);
      return false;
   }
 
   pe.dwSize = sizeof(PROCESSENTRY32);
 
    retval = Process32First(thSnapshot, &pe);
 
   while(retval)
   {
      if(StrStrI(pe.szExeFile, procName) )
      {
         ProcFound = true;
         break;
      }
 
      retval    = Process32Next(thSnapshot,&pe);
      pe.dwSize = sizeof(PROCESSENTRY32);
   }
 
   return pe.th32ProcessID;
}
 
HMODULE GetRemoteModuleHandle(unsigned long pId, char *module)
{
        MODULEENTRY32 modEntry;
        HANDLE tlh = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);
 
        modEntry.dwSize = sizeof(MODULEENTRY32);
    Module32First(tlh, &modEntry);
 
        do
        {
                if(!stricmp(modEntry.szModule, module))
                        return modEntry.hModule;
                modEntry.dwSize = sizeof(MODULEENTRY32);
        }
        while(Module32Next(tlh, &modEntry));
 
        return NULL;
}
 
void _fastcall DumpExports(string libname);
 
 
PIMAGE_EXPORT_DIRECTORY GetExportTable(HMODULE hMod)
{
 
    IMAGE_DOS_HEADER* DOSHeader = (IMAGE_DOS_HEADER*)hMod;
 
    if(DOSHeader->e_magic != 0x5A4D)
        return NULL;
 
    IMAGE_OPTIONAL_HEADER* optionalHeader = (IMAGE_OPTIONAL_HEADER*)((BYTE*)hMod + DOSHeader->e_lfanew + 24);
 
    return (PIMAGE_EXPORT_DIRECTORY)((BYTE*)hMod + optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
 
}
 
int upper(int c)
{
    return toupper((unsigned char)c);
 
}
 
void _fastcall DumpExports(string libname)
{
    string deffilename = libname;
    deffilename.replace(deffilename.end()-3, deffilename.end(), "def");
 
    string cppfilename = libname;
    cppfilename.replace(cppfilename.end()-3, cppfilename.end(), "cpp");
 
    ofstream deffile(deffilename);
    ofstream cppfile(cppfilename);
 
    HMODULE hMod = LoadLibrary(libname.c_str());
    if(!hMod)
        return;
    
    PIMAGE_EXPORT_DIRECTORY expDesc = GetExportTable(hMod);
 
    DWORD number = expDesc->NumberOfFunctions;
    DWORD addrnames = (DWORD)(expDesc->AddressOfNames + (DWORD)hMod);
    DWORD addr = (DWORD)(expDesc->AddressOfNameOrdinals + (DWORD)hMod);
    PWORD ordinals = (PWORD)((DWORD)expDesc->AddressOfNameOrdinals + (DWORD)hMod);
    PSTR* names = (PSTR*)((DWORD)addrnames);
 
   //transform(libname.begin(), libname.end(), libname.begin(), upper);
    
    deffile << "LIBRARY   " << libname.substr(0, libname.length() - 4) << endl;
    deffile << "EXPORTS" << endl;
 
    cppfile << "FARPROC orig[" << expDesc->NumberOfFunctions << "];\n";
    cppfile << "HMODULE hMod = LoadLibrary(\"" << libname << "\");\n";
 
    cppfile << "BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPvoid _fastcall)\n{\n     if (reason == DLL_PROCESS_ATTACH)\n     {\n";
    
    for(int i = 0; i < number; i++)
    {
        for ( int j=0; j < expDesc->NumberOfNames; j++ )
        {
            WORD wOrd = i + expDesc->Base;
            char *pName = (char*)names[j] + (DWORD)hMod;
 
            if ( ordinals[j] == i )
                cppfile << "    orig[" << wOrd << "] = (FARPROC)GetProcAddress(hMod,\"" << pName << "\");\n";
        }
    }
 
    cppfile << "     }\n}" << endl;
 
    for(int i = 0; i < number; i++)
    {
        for ( int j=0; j < expDesc->NumberOfNames; j++ )
        {
            WORD wOrd = i + expDesc->Base;
            char *pName = (char*)names[j] + (DWORD)hMod;
 
            if ( ordinals[j] == i )
            {
                deffile << pName << "=__" << pName << "   @" << wOrd << endl;
 
                cppfile << "extern \"C\" __declspec(naked) void _fastcall __stdcall __";
                cppfile << pName << "()" << endl;
                cppfile << "{" << endl << "    __asm\n" << "    {\n        jmp orig[4*" << wOrd << "];" << endl << "    }" << endl << "}" << endl;
                cout << wOrd << "    " << names[j] + (DWORD)hMod << endl;
            }
        }
 
    }
 
    cppfile.close();
    deffile.close();
}