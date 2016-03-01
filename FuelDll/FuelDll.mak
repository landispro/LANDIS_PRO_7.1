# Microsoft Developer Studio Generated NMAKE File, Based on FuelDll.dsp
!IF "$(CFG)" == ""
CFG=FuelDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to FuelDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FuelDll - Win32 Release" && "$(CFG)" != "FuelDll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FuelDll.mak" CFG="FuelDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FuelDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FuelDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "FuelDll - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FuelDll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Release" "$(OUTDIR)\FuelDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CohortRemovalMask.obj"
	-@erase "$(INTDIR)\FuelGlobalFuncs.obj"
	-@erase "$(INTDIR)\FuelManage.obj"
	-@erase "$(INTDIR)\FuelManEvent.obj"
	-@erase "$(INTDIR)\FuelRule.obj"
	-@erase "$(INTDIR)\FuelSites.obj"
	-@erase "$(INTDIR)\FuelStand.obj"
	-@erase "$(INTDIR)\FuelStands.obj"
	-@erase "$(INTDIR)\FuelTrack.obj"
	-@erase "$(INTDIR)\FuelTreatmentRank.obj"
	-@erase "$(INTDIR)\HarvestReport.obj"
	-@erase "$(INTDIR)\IntArray.obj"
	-@erase "$(INTDIR)\ManagementArea.obj"
	-@erase "$(INTDIR)\ManagementAreaIterator.obj"
	-@erase "$(INTDIR)\ManagementAreas.obj"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\Reclass4.obj"
	-@erase "$(INTDIR)\SiteHarvester.obj"
	-@erase "$(INTDIR)\SiteRemovalMask.obj"
	-@erase "$(INTDIR)\StandIterator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\FuelDll.dll"
	-@erase "$(OUTDIR)\FuelDll.exp"
	-@erase "$(OUTDIR)\FuelDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /Fp"$(INTDIR)\FuelDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FuelDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\FuelDll.pdb" /machine:I386 /def:".\source\Fuel.def" /out:"$(OUTDIR)\FuelDll.dll" /implib:"$(OUTDIR)\FuelDll.lib" 
DEF_FILE= \
	".\source\Fuel.def"
LINK32_OBJS= \
	"$(INTDIR)\CohortRemovalMask.obj" \
	"$(INTDIR)\FuelGlobalFuncs.obj" \
	"$(INTDIR)\FuelManage.obj" \
	"$(INTDIR)\FuelManEvent.obj" \
	"$(INTDIR)\FuelRule.obj" \
	"$(INTDIR)\FuelSites.obj" \
	"$(INTDIR)\FuelStand.obj" \
	"$(INTDIR)\FuelStands.obj" \
	"$(INTDIR)\FuelTrack.obj" \
	"$(INTDIR)\FuelTreatmentRank.obj" \
	"$(INTDIR)\HarvestReport.obj" \
	"$(INTDIR)\IntArray.obj" \
	"$(INTDIR)\ManagementArea.obj" \
	"$(INTDIR)\ManagementAreaIterator.obj" \
	"$(INTDIR)\ManagementAreas.obj" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\Reclass4.obj" \
	"$(INTDIR)\SiteHarvester.obj" \
	"$(INTDIR)\SiteRemovalMask.obj" \
	"$(INTDIR)\StandIterator.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\FuelDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "FuelDll - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\FuelDll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Debug" "$(OUTDIR)\FuelDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\CohortRemovalMask.obj"
	-@erase "$(INTDIR)\FuelGlobalFuncs.obj"
	-@erase "$(INTDIR)\FuelManage.obj"
	-@erase "$(INTDIR)\FuelManEvent.obj"
	-@erase "$(INTDIR)\FuelRule.obj"
	-@erase "$(INTDIR)\FuelSites.obj"
	-@erase "$(INTDIR)\FuelStand.obj"
	-@erase "$(INTDIR)\FuelStands.obj"
	-@erase "$(INTDIR)\FuelTrack.obj"
	-@erase "$(INTDIR)\FuelTreatmentRank.obj"
	-@erase "$(INTDIR)\HarvestReport.obj"
	-@erase "$(INTDIR)\IntArray.obj"
	-@erase "$(INTDIR)\ManagementArea.obj"
	-@erase "$(INTDIR)\ManagementAreaIterator.obj"
	-@erase "$(INTDIR)\ManagementAreas.obj"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\Reclass4.obj"
	-@erase "$(INTDIR)\SiteHarvester.obj"
	-@erase "$(INTDIR)\SiteRemovalMask.obj"
	-@erase "$(INTDIR)\StandIterator.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\FuelDll.dll"
	-@erase "$(OUTDIR)\FuelDll.exp"
	-@erase "$(OUTDIR)\FuelDll.ilk"
	-@erase "$(OUTDIR)\FuelDll.lib"
	-@erase "$(OUTDIR)\FuelDll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /Fp"$(INTDIR)\FuelDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\FuelDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\FuelDll.pdb" /debug /machine:I386 /def:".\source\Fuel.def" /out:"$(OUTDIR)\FuelDll.dll" /implib:"$(OUTDIR)\FuelDll.lib" /pdbtype:sept 
DEF_FILE= \
	".\source\Fuel.def"
LINK32_OBJS= \
	"$(INTDIR)\CohortRemovalMask.obj" \
	"$(INTDIR)\FuelGlobalFuncs.obj" \
	"$(INTDIR)\FuelManage.obj" \
	"$(INTDIR)\FuelManEvent.obj" \
	"$(INTDIR)\FuelRule.obj" \
	"$(INTDIR)\FuelSites.obj" \
	"$(INTDIR)\FuelStand.obj" \
	"$(INTDIR)\FuelStands.obj" \
	"$(INTDIR)\FuelTrack.obj" \
	"$(INTDIR)\FuelTreatmentRank.obj" \
	"$(INTDIR)\HarvestReport.obj" \
	"$(INTDIR)\IntArray.obj" \
	"$(INTDIR)\ManagementArea.obj" \
	"$(INTDIR)\ManagementAreaIterator.obj" \
	"$(INTDIR)\ManagementAreas.obj" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\Reclass4.obj" \
	"$(INTDIR)\SiteHarvester.obj" \
	"$(INTDIR)\SiteRemovalMask.obj" \
	"$(INTDIR)\StandIterator.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\FuelDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("FuelDll.dep")
!INCLUDE "FuelDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "FuelDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "FuelDll - Win32 Release" || "$(CFG)" == "FuelDll - Win32 Debug"
SOURCE=.\source\CohortRemovalMask.cpp

"$(INTDIR)\CohortRemovalMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelGlobalFuncs.cpp

"$(INTDIR)\FuelGlobalFuncs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelManage.cpp

"$(INTDIR)\FuelManage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelManEvent.cpp

"$(INTDIR)\FuelManEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelRule.cpp

"$(INTDIR)\FuelRule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelSites.cpp

"$(INTDIR)\FuelSites.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelStand.cpp

"$(INTDIR)\FuelStand.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelStands.cpp

"$(INTDIR)\FuelStands.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelTrack.cpp

"$(INTDIR)\FuelTrack.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\FuelTreatmentRank.cpp

"$(INTDIR)\FuelTreatmentRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\HarvestReport.cpp

"$(INTDIR)\HarvestReport.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\IntArray.cpp

"$(INTDIR)\IntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\ManagementArea.cpp

"$(INTDIR)\ManagementArea.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\ManagementAreaIterator.cpp

"$(INTDIR)\ManagementAreaIterator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\ManagementAreas.cpp

"$(INTDIR)\ManagementAreas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\POINT.CPP

"$(INTDIR)\POINT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\Reclass4.cpp

"$(INTDIR)\Reclass4.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\SiteHarvester.cpp

"$(INTDIR)\SiteHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\SiteRemovalMask.cpp

"$(INTDIR)\SiteRemovalMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\StandIterator.cpp

"$(INTDIR)\StandIterator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "FuelDll - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\FuelDll"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\FuelDll"

!ELSEIF  "$(CFG)" == "FuelDll - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\FuelDll"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\FuelDll"

!ENDIF 


!ENDIF 

