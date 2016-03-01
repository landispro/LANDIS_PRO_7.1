# Microsoft Developer Studio Generated NMAKE File, Based on FireDll.dsp
!IF "$(CFG)" == ""
CFG=FireDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FireDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FireDll - Win32 Release" && "$(CFG)" != "FireDll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FireDll.mak" CFG="FireDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FireDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FireDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FireDll - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FireDll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Release" "$(OUTDIR)\FireDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FIRE.OBJ"
	-@erase "$(INTDIR)\FireExport.obj"
	-@erase "$(INTDIR)\FireRegimeUnit.obj"
	-@erase "$(INTDIR)\FireRegimeUnits.obj"
	-@erase "$(INTDIR)\FireSites.obj"
	-@erase "$(INTDIR)\MERSENNE.OBJ"
	-@erase "$(INTDIR)\PILE.OBJ"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\STOC1.OBJ"
	-@erase "$(INTDIR)\STOC2.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FireDll.dll"
	-@erase "$(OUTDIR)\FireDll.exp"
	-@erase "$(OUTDIR)\FireDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FIREDLL_EXPORTS" /Fp"$(INTDIR)\FireDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FireDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FireDll.pdb" /machine:I386 /def:".\source\Fire.def" /out:"$(OUTDIR)\FireDll.dll" /implib:"$(OUTDIR)\FireDll.lib" 
DEF_FILE= \
	".\source\Fire.def"
LINK32_OBJS= \
	"$(INTDIR)\FIRE.OBJ" \
	"$(INTDIR)\FireExport.obj" \
	"$(INTDIR)\FireRegimeUnit.obj" \
	"$(INTDIR)\FireRegimeUnits.obj" \
	"$(INTDIR)\FireSites.obj" \
	"$(INTDIR)\MERSENNE.OBJ" \
	"$(INTDIR)\PILE.OBJ" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\STOC1.OBJ" \
	"$(INTDIR)\STOC2.OBJ" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\FireDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FireDll.dll" "$(OUTDIR)\FireDll.bsc"

!ELSE 

ALL : "Landis40Core - Win32 Debug" "$(OUTDIR)\FireDll.dll" "$(OUTDIR)\FireDll.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\FIRE.OBJ"
	-@erase "$(INTDIR)\FIRE.SBR"
	-@erase "$(INTDIR)\FireExport.obj"
	-@erase "$(INTDIR)\FireExport.sbr"
	-@erase "$(INTDIR)\FireRegimeUnit.obj"
	-@erase "$(INTDIR)\FireRegimeUnit.sbr"
	-@erase "$(INTDIR)\FireRegimeUnits.obj"
	-@erase "$(INTDIR)\FireRegimeUnits.sbr"
	-@erase "$(INTDIR)\FireSites.obj"
	-@erase "$(INTDIR)\FireSites.sbr"
	-@erase "$(INTDIR)\MERSENNE.OBJ"
	-@erase "$(INTDIR)\MERSENNE.SBR"
	-@erase "$(INTDIR)\PILE.OBJ"
	-@erase "$(INTDIR)\PILE.SBR"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\POINT.SBR"
	-@erase "$(INTDIR)\STOC1.OBJ"
	-@erase "$(INTDIR)\STOC1.SBR"
	-@erase "$(INTDIR)\STOC2.OBJ"
	-@erase "$(INTDIR)\STOC2.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FireDll.bsc"
	-@erase "$(OUTDIR)\FireDll.dll"
	-@erase "$(OUTDIR)\FireDll.exp"
	-@erase "$(OUTDIR)\FireDll.ilk"
	-@erase "$(OUTDIR)\FireDll.lib"
	-@erase "$(OUTDIR)\FireDll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FIREDLL_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\FireDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FireDll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\FIRE.SBR" \
	"$(INTDIR)\FireExport.sbr" \
	"$(INTDIR)\FireRegimeUnit.sbr" \
	"$(INTDIR)\FireRegimeUnits.sbr" \
	"$(INTDIR)\FireSites.sbr" \
	"$(INTDIR)\MERSENNE.SBR" \
	"$(INTDIR)\PILE.SBR" \
	"$(INTDIR)\POINT.SBR" \
	"$(INTDIR)\STOC1.SBR" \
	"$(INTDIR)\STOC2.SBR"

"$(OUTDIR)\FireDll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\FireDll.pdb" /debug /machine:I386 /def:".\source\Fire.def" /out:"$(OUTDIR)\FireDll.dll" /implib:"$(OUTDIR)\FireDll.lib" /pdbtype:sept 
DEF_FILE= \
	".\source\Fire.def"
LINK32_OBJS= \
	"$(INTDIR)\FIRE.OBJ" \
	"$(INTDIR)\FireExport.obj" \
	"$(INTDIR)\FireRegimeUnit.obj" \
	"$(INTDIR)\FireRegimeUnits.obj" \
	"$(INTDIR)\FireSites.obj" \
	"$(INTDIR)\MERSENNE.OBJ" \
	"$(INTDIR)\PILE.OBJ" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\STOC1.OBJ" \
	"$(INTDIR)\STOC2.OBJ" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\FireDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FireDll.dep")
!INCLUDE "FireDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "FireDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FireDll - Win32 Release" || "$(CFG)" == "FireDll - Win32 Debug"
SOURCE=.\source\FIRE.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\FIRE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\FIRE.OBJ"	"$(INTDIR)\FIRE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FireExport.cpp

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\FireExport.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\FireExport.obj"	"$(INTDIR)\FireExport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FireRegimeUnit.cpp

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\FireRegimeUnit.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\FireRegimeUnit.obj"	"$(INTDIR)\FireRegimeUnit.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FireRegimeUnits.cpp

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\FireRegimeUnits.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\FireRegimeUnits.obj"	"$(INTDIR)\FireRegimeUnits.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FireSites.cpp

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\FireSites.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\FireSites.obj"	"$(INTDIR)\FireSites.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\MERSENNE.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\MERSENNE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\MERSENNE.OBJ"	"$(INTDIR)\MERSENNE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PILE.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\PILE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\PILE.OBJ"	"$(INTDIR)\PILE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\POINT.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\POINT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\POINT.OBJ"	"$(INTDIR)\POINT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\STOC1.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\STOC1.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\STOC1.OBJ"	"$(INTDIR)\STOC1.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\STOC2.CPP

!IF  "$(CFG)" == "FireDll - Win32 Release"


"$(INTDIR)\STOC2.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"


"$(INTDIR)\STOC2.OBJ"	"$(INTDIR)\STOC2.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "FireDll - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\FireDll"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FireDll"

!ELSEIF  "$(CFG)" == "FireDll - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\FireDll"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FireDll"

!ENDIF 


!ENDIF 

