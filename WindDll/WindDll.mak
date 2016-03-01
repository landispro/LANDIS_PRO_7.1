# Microsoft Developer Studio Generated NMAKE File, Based on WindDll.dsp
!IF "$(CFG)" == ""
CFG=WindDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WindDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WindDll - Win32 Release" && "$(CFG)" != "WindDll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WindDll.mak" CFG="WindDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WindDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WindDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WindDll - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\WindDll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Release" "$(OUTDIR)\WindDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\PILE.OBJ"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WIND.OBJ"
	-@erase "$(INTDIR)\WindExport.obj"
	-@erase "$(OUTDIR)\WindDll.dll"
	-@erase "$(OUTDIR)\WindDll.exp"
	-@erase "$(OUTDIR)\WindDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WINDDLL_EXPORTS" /Fp"$(INTDIR)\WindDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WindDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\WindDll.pdb" /machine:I386 /def:".\source\Wind.def" /out:"$(OUTDIR)\WindDll.dll" /implib:"$(OUTDIR)\WindDll.lib" 
DEF_FILE= \
	".\source\Wind.def"
LINK32_OBJS= \
	"$(INTDIR)\PILE.OBJ" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\WIND.OBJ" \
	"$(INTDIR)\WindExport.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\WindDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\WindDll.dll" "$(OUTDIR)\WindDll.bsc"

!ELSE 

ALL : "Landis40Core - Win32 Debug" "$(OUTDIR)\WindDll.dll" "$(OUTDIR)\WindDll.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\PILE.OBJ"
	-@erase "$(INTDIR)\PILE.SBR"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\POINT.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WIND.OBJ"
	-@erase "$(INTDIR)\WIND.SBR"
	-@erase "$(INTDIR)\WindExport.obj"
	-@erase "$(INTDIR)\WindExport.sbr"
	-@erase "$(OUTDIR)\WindDll.bsc"
	-@erase "$(OUTDIR)\WindDll.dll"
	-@erase "$(OUTDIR)\WindDll.exp"
	-@erase "$(OUTDIR)\WindDll.ilk"
	-@erase "$(OUTDIR)\WindDll.lib"
	-@erase "$(OUTDIR)\WindDll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WINDDLL_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WindDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WindDll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\PILE.SBR" \
	"$(INTDIR)\POINT.SBR" \
	"$(INTDIR)\WIND.SBR" \
	"$(INTDIR)\WindExport.sbr"

"$(OUTDIR)\WindDll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\WindDll.pdb" /debug /machine:I386 /def:".\source\Wind.def" /out:"$(OUTDIR)\WindDll.dll" /implib:"$(OUTDIR)\WindDll.lib" /pdbtype:sept 
DEF_FILE= \
	".\source\Wind.def"
LINK32_OBJS= \
	"$(INTDIR)\PILE.OBJ" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\WIND.OBJ" \
	"$(INTDIR)\WindExport.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\WindDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WindDll.dep")
!INCLUDE "WindDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "WindDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WindDll - Win32 Release" || "$(CFG)" == "WindDll - Win32 Debug"
SOURCE=.\source\PILE.CPP

!IF  "$(CFG)" == "WindDll - Win32 Release"


"$(INTDIR)\PILE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"


"$(INTDIR)\PILE.OBJ"	"$(INTDIR)\PILE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\POINT.CPP

!IF  "$(CFG)" == "WindDll - Win32 Release"


"$(INTDIR)\POINT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"


"$(INTDIR)\POINT.OBJ"	"$(INTDIR)\POINT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\WIND.CPP

!IF  "$(CFG)" == "WindDll - Win32 Release"


"$(INTDIR)\WIND.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"


"$(INTDIR)\WIND.OBJ"	"$(INTDIR)\WIND.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\WindExport.cpp

!IF  "$(CFG)" == "WindDll - Win32 Release"


"$(INTDIR)\WindExport.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"


"$(INTDIR)\WindExport.obj"	"$(INTDIR)\WindExport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "WindDll - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\WindDll"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\WindDll"

!ELSEIF  "$(CFG)" == "WindDll - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\WindDll"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\WindDll"

!ENDIF 


!ENDIF 

