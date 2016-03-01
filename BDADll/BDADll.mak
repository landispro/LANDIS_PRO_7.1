# Microsoft Developer Studio Generated NMAKE File, Based on BDADll.dsp
!IF "$(CFG)" == ""
CFG=BDADll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to BDADll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "BDADll - Win32 Release" && "$(CFG)" != "BDADll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BDADll.mak" CFG="BDADll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BDADll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "BDADll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "BDADll - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BDADll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Release" "$(OUTDIR)\BDADll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BDA.OBJ"
	-@erase "$(INTDIR)\BDAS.obj"
	-@erase "$(INTDIR)\BDASExport.obj"
	-@erase "$(INTDIR)\BDASites.obj"
	-@erase "$(INTDIR)\MERSENNE.OBJ"
	-@erase "$(INTDIR)\PosList.obj"
	-@erase "$(INTDIR)\STOC1.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BDADll.dll"
	-@erase "$(OUTDIR)\BDADll.exp"
	-@erase "$(OUTDIR)\BDADll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BDADLL_EXPORTS" /Fp"$(INTDIR)\BDADll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BDADll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\BDADll.pdb" /machine:I386 /def:"..\Landis40Core\baddll.def" /out:"$(OUTDIR)\BDADll.dll" /implib:"$(OUTDIR)\BDADll.lib" 
DEF_FILE= \
	"..\Landis40Core\baddll.def"
LINK32_OBJS= \
	"$(INTDIR)\BDA.OBJ" \
	"$(INTDIR)\BDAS.obj" \
	"$(INTDIR)\BDASExport.obj" \
	"$(INTDIR)\BDASites.obj" \
	"$(INTDIR)\MERSENNE.OBJ" \
	"$(INTDIR)\PosList.obj" \
	"$(INTDIR)\STOC1.OBJ" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\BDADll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\BDADll.dll" "$(OUTDIR)\BDADll.bsc"

!ELSE 

ALL : "Landis40Core - Win32 Debug" "$(OUTDIR)\BDADll.dll" "$(OUTDIR)\BDADll.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BDA.OBJ"
	-@erase "$(INTDIR)\BDA.SBR"
	-@erase "$(INTDIR)\BDAS.obj"
	-@erase "$(INTDIR)\BDAS.sbr"
	-@erase "$(INTDIR)\BDASExport.obj"
	-@erase "$(INTDIR)\BDASExport.sbr"
	-@erase "$(INTDIR)\BDASites.obj"
	-@erase "$(INTDIR)\BDASites.sbr"
	-@erase "$(INTDIR)\MERSENNE.OBJ"
	-@erase "$(INTDIR)\MERSENNE.SBR"
	-@erase "$(INTDIR)\PosList.obj"
	-@erase "$(INTDIR)\PosList.sbr"
	-@erase "$(INTDIR)\STOC1.OBJ"
	-@erase "$(INTDIR)\STOC1.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BDADll.bsc"
	-@erase "$(OUTDIR)\BDADll.dll"
	-@erase "$(OUTDIR)\BDADll.exp"
	-@erase "$(OUTDIR)\BDADll.ilk"
	-@erase "$(OUTDIR)\BDADll.lib"
	-@erase "$(OUTDIR)\BDADll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BDADll_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BDADll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BDADll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BDA.SBR" \
	"$(INTDIR)\BDAS.sbr" \
	"$(INTDIR)\BDASExport.sbr" \
	"$(INTDIR)\BDASites.sbr" \
	"$(INTDIR)\MERSENNE.SBR" \
	"$(INTDIR)\PosList.sbr" \
	"$(INTDIR)\STOC1.SBR"

"$(OUTDIR)\BDADll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\BDADll.pdb" /debug /machine:I386 /def:"..\Landis40Core\baddll.def" /out:"$(OUTDIR)\BDADll.dll" /implib:"$(OUTDIR)\BDADll.lib" /pdbtype:sept 
DEF_FILE= \
	"..\Landis40Core\baddll.def"
LINK32_OBJS= \
	"$(INTDIR)\BDA.OBJ" \
	"$(INTDIR)\BDAS.obj" \
	"$(INTDIR)\BDASExport.obj" \
	"$(INTDIR)\BDASites.obj" \
	"$(INTDIR)\MERSENNE.OBJ" \
	"$(INTDIR)\PosList.obj" \
	"$(INTDIR)\STOC1.OBJ" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\BDADll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("BDADll.dep")
!INCLUDE "BDADll.dep"
!ELSE 
!MESSAGE Warning: cannot find "BDADll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BDADll - Win32 Release" || "$(CFG)" == "BDADll - Win32 Debug"
SOURCE=.\source\BDA.CPP

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\BDA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\BDA.OBJ"	"$(INTDIR)\BDA.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\BDAS.cpp

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\BDAS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\BDAS.obj"	"$(INTDIR)\BDAS.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\BDASExport.cpp

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\BDASExport.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\BDASExport.obj"	"$(INTDIR)\BDASExport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\BDASites.cpp

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\BDASites.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\BDASites.obj"	"$(INTDIR)\BDASites.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\MERSENNE.CPP

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\MERSENNE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\MERSENNE.OBJ"	"$(INTDIR)\MERSENNE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PosList.cpp

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\PosList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\PosList.obj"	"$(INTDIR)\PosList.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\STOC1.CPP

!IF  "$(CFG)" == "BDADll - Win32 Release"


"$(INTDIR)\STOC1.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"


"$(INTDIR)\STOC1.OBJ"	"$(INTDIR)\STOC1.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "BDADll - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\BDADll"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\BDADll"

!ELSEIF  "$(CFG)" == "BDADll - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\BDADll"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\BDADll"

!ENDIF 


!ENDIF 

