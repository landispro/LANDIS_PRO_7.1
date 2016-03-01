# Microsoft Developer Studio Generated NMAKE File, Based on HarvestDll.dsp
!IF "$(CFG)" == ""
CFG=HarvestDll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HarvestDll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "HarvestDll - Win32 Release" && "$(CFG)" != "HarvestDll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HarvestDll.mak" CFG="HarvestDll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HarvestDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "HarvestDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HarvestDll - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HarvestDll.dll"

!ELSE 

ALL : "Landis40Core - Win32 Release" "$(OUTDIR)\HarvestDll.dll"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BoundedPocketStandHarvester.obj"
	-@erase "$(INTDIR)\CohortRemovalMask.obj"
	-@erase "$(INTDIR)\EconomicImportanceRank.obj"
	-@erase "$(INTDIR)\FillingStandHarvester.obj"
	-@erase "$(INTDIR)\GlobalFunctions.obj"
	-@erase "$(INTDIR)\GroupSelectionRegime.obj"
	-@erase "$(INTDIR)\HarvestEvent.obj"
	-@erase "$(INTDIR)\HarvestEventQueue.obj"
	-@erase "$(INTDIR)\HarvestPath.obj"
	-@erase "$(INTDIR)\HarvestPathIterator.obj"
	-@erase "$(INTDIR)\HarvestRegime.obj"
	-@erase "$(INTDIR)\HarvestReport.obj"
	-@erase "$(INTDIR)\HarvestSites.obj"
	-@erase "$(INTDIR)\IntArray.obj"
	-@erase "$(INTDIR)\ManagementArea.obj"
	-@erase "$(INTDIR)\ManagementAreaIterator.obj"
	-@erase "$(INTDIR)\ManagementAreas.obj"
	-@erase "$(INTDIR)\MultiplePocketStandHarvester.obj"
	-@erase "$(INTDIR)\OldestRank.obj"
	-@erase "$(INTDIR)\OnePassStandBasedRegime.obj"
	-@erase "$(INTDIR)\OnePassStandFillingRegime.obj"
	-@erase "$(INTDIR)\OnePassStandSpreadingRegime.obj"
	-@erase "$(INTDIR)\PeriodicStandFillingRegime.obj"
	-@erase "$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\RandomRank.obj"
	-@erase "$(INTDIR)\RegulateDistributionRank.obj"
	-@erase "$(INTDIR)\RelativeOldestRank.obj"
	-@erase "$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\SiteHarvester.obj"
	-@erase "$(INTDIR)\SiteRemovalMask.obj"
	-@erase "$(INTDIR)\Stand.obj"
	-@erase "$(INTDIR)\StandHarvester.obj"
	-@erase "$(INTDIR)\StandIterator.obj"
	-@erase "$(INTDIR)\StandRankingAlgorithm.obj"
	-@erase "$(INTDIR)\Stands.obj"
	-@erase "$(INTDIR)\TwoPassStandBasedRegime.obj"
	-@erase "$(INTDIR)\TwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\TwoPassStandSpreadingRegime.obj"
	-@erase "$(INTDIR)\UnboundedPocketStandHarvester.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HarvestDll.dll"
	-@erase "$(OUTDIR)\HarvestDll.exp"
	-@erase "$(OUTDIR)\HarvestDll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /D "__HARVEST__" /Fp"$(INTDIR)\HarvestDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HarvestDll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\HarvestDll.pdb" /machine:I386 /out:"$(OUTDIR)\HarvestDll.dll" /implib:"$(OUTDIR)\HarvestDll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BoundedPocketStandHarvester.obj" \
	"$(INTDIR)\CohortRemovalMask.obj" \
	"$(INTDIR)\EconomicImportanceRank.obj" \
	"$(INTDIR)\FillingStandHarvester.obj" \
	"$(INTDIR)\GlobalFunctions.obj" \
	"$(INTDIR)\GroupSelectionRegime.obj" \
	"$(INTDIR)\HarvestEvent.obj" \
	"$(INTDIR)\HarvestEventQueue.obj" \
	"$(INTDIR)\HarvestPath.obj" \
	"$(INTDIR)\HarvestPathIterator.obj" \
	"$(INTDIR)\HarvestRegime.obj" \
	"$(INTDIR)\HarvestReport.obj" \
	"$(INTDIR)\HarvestSites.obj" \
	"$(INTDIR)\IntArray.obj" \
	"$(INTDIR)\ManagementArea.obj" \
	"$(INTDIR)\ManagementAreaIterator.obj" \
	"$(INTDIR)\ManagementAreas.obj" \
	"$(INTDIR)\MultiplePocketStandHarvester.obj" \
	"$(INTDIR)\OldestRank.obj" \
	"$(INTDIR)\OnePassStandBasedRegime.obj" \
	"$(INTDIR)\OnePassStandFillingRegime.obj" \
	"$(INTDIR)\OnePassStandSpreadingRegime.obj" \
	"$(INTDIR)\PeriodicStandFillingRegime.obj" \
	"$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\RandomRank.obj" \
	"$(INTDIR)\RegulateDistributionRank.obj" \
	"$(INTDIR)\RelativeOldestRank.obj" \
	"$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj" \
	"$(INTDIR)\SiteHarvester.obj" \
	"$(INTDIR)\SiteRemovalMask.obj" \
	"$(INTDIR)\Stand.obj" \
	"$(INTDIR)\StandHarvester.obj" \
	"$(INTDIR)\StandIterator.obj" \
	"$(INTDIR)\StandRankingAlgorithm.obj" \
	"$(INTDIR)\Stands.obj" \
	"$(INTDIR)\TwoPassStandBasedRegime.obj" \
	"$(INTDIR)\TwoPassStandFillingRegime.obj" \
	"$(INTDIR)\TwoPassStandSpreadingRegime.obj" \
	"$(INTDIR)\UnboundedPocketStandHarvester.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\HarvestDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HarvestDll.dll" "$(OUTDIR)\HarvestDll.bsc"

!ELSE 

ALL : "Landis40Core - Win32 Debug" "$(OUTDIR)\HarvestDll.dll" "$(OUTDIR)\HarvestDll.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\BoundedPocketStandHarvester.obj"
	-@erase "$(INTDIR)\BoundedPocketStandHarvester.sbr"
	-@erase "$(INTDIR)\CohortRemovalMask.obj"
	-@erase "$(INTDIR)\CohortRemovalMask.sbr"
	-@erase "$(INTDIR)\EconomicImportanceRank.obj"
	-@erase "$(INTDIR)\EconomicImportanceRank.sbr"
	-@erase "$(INTDIR)\FillingStandHarvester.obj"
	-@erase "$(INTDIR)\FillingStandHarvester.sbr"
	-@erase "$(INTDIR)\GlobalFunctions.obj"
	-@erase "$(INTDIR)\GlobalFunctions.sbr"
	-@erase "$(INTDIR)\GroupSelectionRegime.obj"
	-@erase "$(INTDIR)\GroupSelectionRegime.sbr"
	-@erase "$(INTDIR)\HarvestEvent.obj"
	-@erase "$(INTDIR)\HarvestEvent.sbr"
	-@erase "$(INTDIR)\HarvestEventQueue.obj"
	-@erase "$(INTDIR)\HarvestEventQueue.sbr"
	-@erase "$(INTDIR)\HarvestPath.obj"
	-@erase "$(INTDIR)\HarvestPath.sbr"
	-@erase "$(INTDIR)\HarvestPathIterator.obj"
	-@erase "$(INTDIR)\HarvestPathIterator.sbr"
	-@erase "$(INTDIR)\HarvestRegime.obj"
	-@erase "$(INTDIR)\HarvestRegime.sbr"
	-@erase "$(INTDIR)\HarvestReport.obj"
	-@erase "$(INTDIR)\HarvestReport.sbr"
	-@erase "$(INTDIR)\HarvestSites.obj"
	-@erase "$(INTDIR)\HarvestSites.sbr"
	-@erase "$(INTDIR)\IntArray.obj"
	-@erase "$(INTDIR)\IntArray.sbr"
	-@erase "$(INTDIR)\ManagementArea.obj"
	-@erase "$(INTDIR)\ManagementArea.sbr"
	-@erase "$(INTDIR)\ManagementAreaIterator.obj"
	-@erase "$(INTDIR)\ManagementAreaIterator.sbr"
	-@erase "$(INTDIR)\ManagementAreas.obj"
	-@erase "$(INTDIR)\ManagementAreas.sbr"
	-@erase "$(INTDIR)\MultiplePocketStandHarvester.obj"
	-@erase "$(INTDIR)\MultiplePocketStandHarvester.sbr"
	-@erase "$(INTDIR)\OldestRank.obj"
	-@erase "$(INTDIR)\OldestRank.sbr"
	-@erase "$(INTDIR)\OnePassStandBasedRegime.obj"
	-@erase "$(INTDIR)\OnePassStandBasedRegime.sbr"
	-@erase "$(INTDIR)\OnePassStandFillingRegime.obj"
	-@erase "$(INTDIR)\OnePassStandFillingRegime.sbr"
	-@erase "$(INTDIR)\OnePassStandSpreadingRegime.obj"
	-@erase "$(INTDIR)\OnePassStandSpreadingRegime.sbr"
	-@erase "$(INTDIR)\PeriodicStandFillingRegime.obj"
	-@erase "$(INTDIR)\PeriodicStandFillingRegime.sbr"
	-@erase "$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\PeriodicTwoPassStandFillingRegime.sbr"
	-@erase "$(INTDIR)\POINT.OBJ"
	-@erase "$(INTDIR)\POINT.SBR"
	-@erase "$(INTDIR)\RandomRank.obj"
	-@erase "$(INTDIR)\RandomRank.sbr"
	-@erase "$(INTDIR)\RegulateDistributionRank.obj"
	-@erase "$(INTDIR)\RegulateDistributionRank.sbr"
	-@erase "$(INTDIR)\RelativeOldestRank.obj"
	-@erase "$(INTDIR)\RelativeOldestRank.sbr"
	-@erase "$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\RepeatingTwoPassStandFillingRegime.sbr"
	-@erase "$(INTDIR)\SiteHarvester.obj"
	-@erase "$(INTDIR)\SiteHarvester.sbr"
	-@erase "$(INTDIR)\SiteRemovalMask.obj"
	-@erase "$(INTDIR)\SiteRemovalMask.sbr"
	-@erase "$(INTDIR)\Stand.obj"
	-@erase "$(INTDIR)\Stand.sbr"
	-@erase "$(INTDIR)\StandHarvester.obj"
	-@erase "$(INTDIR)\StandHarvester.sbr"
	-@erase "$(INTDIR)\StandIterator.obj"
	-@erase "$(INTDIR)\StandIterator.sbr"
	-@erase "$(INTDIR)\StandRankingAlgorithm.obj"
	-@erase "$(INTDIR)\StandRankingAlgorithm.sbr"
	-@erase "$(INTDIR)\Stands.obj"
	-@erase "$(INTDIR)\Stands.sbr"
	-@erase "$(INTDIR)\TwoPassStandBasedRegime.obj"
	-@erase "$(INTDIR)\TwoPassStandBasedRegime.sbr"
	-@erase "$(INTDIR)\TwoPassStandFillingRegime.obj"
	-@erase "$(INTDIR)\TwoPassStandFillingRegime.sbr"
	-@erase "$(INTDIR)\TwoPassStandSpreadingRegime.obj"
	-@erase "$(INTDIR)\TwoPassStandSpreadingRegime.sbr"
	-@erase "$(INTDIR)\UnboundedPocketStandHarvester.obj"
	-@erase "$(INTDIR)\UnboundedPocketStandHarvester.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HarvestDll.bsc"
	-@erase "$(OUTDIR)\HarvestDll.dll"
	-@erase "$(OUTDIR)\HarvestDll.exp"
	-@erase "$(OUTDIR)\HarvestDll.ilk"
	-@erase "$(OUTDIR)\HarvestDll.lib"
	-@erase "$(OUTDIR)\HarvestDll.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /D "__HARVEST__" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HarvestDll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HarvestDll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BoundedPocketStandHarvester.sbr" \
	"$(INTDIR)\CohortRemovalMask.sbr" \
	"$(INTDIR)\EconomicImportanceRank.sbr" \
	"$(INTDIR)\FillingStandHarvester.sbr" \
	"$(INTDIR)\GlobalFunctions.sbr" \
	"$(INTDIR)\GroupSelectionRegime.sbr" \
	"$(INTDIR)\HarvestEvent.sbr" \
	"$(INTDIR)\HarvestEventQueue.sbr" \
	"$(INTDIR)\HarvestPath.sbr" \
	"$(INTDIR)\HarvestPathIterator.sbr" \
	"$(INTDIR)\HarvestRegime.sbr" \
	"$(INTDIR)\HarvestReport.sbr" \
	"$(INTDIR)\HarvestSites.sbr" \
	"$(INTDIR)\IntArray.sbr" \
	"$(INTDIR)\ManagementArea.sbr" \
	"$(INTDIR)\ManagementAreaIterator.sbr" \
	"$(INTDIR)\ManagementAreas.sbr" \
	"$(INTDIR)\MultiplePocketStandHarvester.sbr" \
	"$(INTDIR)\OldestRank.sbr" \
	"$(INTDIR)\OnePassStandBasedRegime.sbr" \
	"$(INTDIR)\OnePassStandFillingRegime.sbr" \
	"$(INTDIR)\OnePassStandSpreadingRegime.sbr" \
	"$(INTDIR)\PeriodicStandFillingRegime.sbr" \
	"$(INTDIR)\PeriodicTwoPassStandFillingRegime.sbr" \
	"$(INTDIR)\POINT.SBR" \
	"$(INTDIR)\RandomRank.sbr" \
	"$(INTDIR)\RegulateDistributionRank.sbr" \
	"$(INTDIR)\RelativeOldestRank.sbr" \
	"$(INTDIR)\RepeatingTwoPassStandFillingRegime.sbr" \
	"$(INTDIR)\SiteHarvester.sbr" \
	"$(INTDIR)\SiteRemovalMask.sbr" \
	"$(INTDIR)\Stand.sbr" \
	"$(INTDIR)\StandHarvester.sbr" \
	"$(INTDIR)\StandIterator.sbr" \
	"$(INTDIR)\StandRankingAlgorithm.sbr" \
	"$(INTDIR)\Stands.sbr" \
	"$(INTDIR)\TwoPassStandBasedRegime.sbr" \
	"$(INTDIR)\TwoPassStandFillingRegime.sbr" \
	"$(INTDIR)\TwoPassStandSpreadingRegime.sbr" \
	"$(INTDIR)\UnboundedPocketStandHarvester.sbr"

"$(OUTDIR)\HarvestDll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\HarvestDll.pdb" /debug /machine:I386 /out:"$(OUTDIR)\HarvestDll.dll" /implib:"$(OUTDIR)\HarvestDll.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BoundedPocketStandHarvester.obj" \
	"$(INTDIR)\CohortRemovalMask.obj" \
	"$(INTDIR)\EconomicImportanceRank.obj" \
	"$(INTDIR)\FillingStandHarvester.obj" \
	"$(INTDIR)\GlobalFunctions.obj" \
	"$(INTDIR)\GroupSelectionRegime.obj" \
	"$(INTDIR)\HarvestEvent.obj" \
	"$(INTDIR)\HarvestEventQueue.obj" \
	"$(INTDIR)\HarvestPath.obj" \
	"$(INTDIR)\HarvestPathIterator.obj" \
	"$(INTDIR)\HarvestRegime.obj" \
	"$(INTDIR)\HarvestReport.obj" \
	"$(INTDIR)\HarvestSites.obj" \
	"$(INTDIR)\IntArray.obj" \
	"$(INTDIR)\ManagementArea.obj" \
	"$(INTDIR)\ManagementAreaIterator.obj" \
	"$(INTDIR)\ManagementAreas.obj" \
	"$(INTDIR)\MultiplePocketStandHarvester.obj" \
	"$(INTDIR)\OldestRank.obj" \
	"$(INTDIR)\OnePassStandBasedRegime.obj" \
	"$(INTDIR)\OnePassStandFillingRegime.obj" \
	"$(INTDIR)\OnePassStandSpreadingRegime.obj" \
	"$(INTDIR)\PeriodicStandFillingRegime.obj" \
	"$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj" \
	"$(INTDIR)\POINT.OBJ" \
	"$(INTDIR)\RandomRank.obj" \
	"$(INTDIR)\RegulateDistributionRank.obj" \
	"$(INTDIR)\RelativeOldestRank.obj" \
	"$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj" \
	"$(INTDIR)\SiteHarvester.obj" \
	"$(INTDIR)\SiteRemovalMask.obj" \
	"$(INTDIR)\Stand.obj" \
	"$(INTDIR)\StandHarvester.obj" \
	"$(INTDIR)\StandIterator.obj" \
	"$(INTDIR)\StandRankingAlgorithm.obj" \
	"$(INTDIR)\Stands.obj" \
	"$(INTDIR)\TwoPassStandBasedRegime.obj" \
	"$(INTDIR)\TwoPassStandFillingRegime.obj" \
	"$(INTDIR)\TwoPassStandSpreadingRegime.obj" \
	"$(INTDIR)\UnboundedPocketStandHarvester.obj" \
	"$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)\HarvestDll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HarvestDll.dep")
!INCLUDE "HarvestDll.dep"
!ELSE 
!MESSAGE Warning: cannot find "HarvestDll.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HarvestDll - Win32 Release" || "$(CFG)" == "HarvestDll - Win32 Debug"
SOURCE=.\source\BoundedPocketStandHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\BoundedPocketStandHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\BoundedPocketStandHarvester.obj"	"$(INTDIR)\BoundedPocketStandHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\CohortRemovalMask.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\CohortRemovalMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\CohortRemovalMask.obj"	"$(INTDIR)\CohortRemovalMask.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\EconomicImportanceRank.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\EconomicImportanceRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\EconomicImportanceRank.obj"	"$(INTDIR)\EconomicImportanceRank.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FillingStandHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\FillingStandHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\FillingStandHarvester.obj"	"$(INTDIR)\FillingStandHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\GlobalFunctions.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\GlobalFunctions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\GlobalFunctions.obj"	"$(INTDIR)\GlobalFunctions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\GroupSelectionRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\GroupSelectionRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\GroupSelectionRegime.obj"	"$(INTDIR)\GroupSelectionRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestEvent.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestEvent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestEvent.obj"	"$(INTDIR)\HarvestEvent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestEventQueue.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestEventQueue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestEventQueue.obj"	"$(INTDIR)\HarvestEventQueue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestPath.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestPath.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestPath.obj"	"$(INTDIR)\HarvestPath.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestPathIterator.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestPathIterator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestPathIterator.obj"	"$(INTDIR)\HarvestPathIterator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestRegime.obj"	"$(INTDIR)\HarvestRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestReport.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestReport.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestReport.obj"	"$(INTDIR)\HarvestReport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HarvestSites.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\HarvestSites.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\HarvestSites.obj"	"$(INTDIR)\HarvestSites.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\IntArray.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\IntArray.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\IntArray.obj"	"$(INTDIR)\IntArray.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\ManagementArea.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\ManagementArea.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\ManagementArea.obj"	"$(INTDIR)\ManagementArea.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\ManagementAreaIterator.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\ManagementAreaIterator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\ManagementAreaIterator.obj"	"$(INTDIR)\ManagementAreaIterator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\ManagementAreas.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\ManagementAreas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\ManagementAreas.obj"	"$(INTDIR)\ManagementAreas.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\MultiplePocketStandHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\MultiplePocketStandHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\MultiplePocketStandHarvester.obj"	"$(INTDIR)\MultiplePocketStandHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\OldestRank.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\OldestRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\OldestRank.obj"	"$(INTDIR)\OldestRank.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\OnePassStandBasedRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\OnePassStandBasedRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\OnePassStandBasedRegime.obj"	"$(INTDIR)\OnePassStandBasedRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\OnePassStandFillingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\OnePassStandFillingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\OnePassStandFillingRegime.obj"	"$(INTDIR)\OnePassStandFillingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\OnePassStandSpreadingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\OnePassStandSpreadingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\OnePassStandSpreadingRegime.obj"	"$(INTDIR)\OnePassStandSpreadingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PeriodicStandFillingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\PeriodicStandFillingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\PeriodicStandFillingRegime.obj"	"$(INTDIR)\PeriodicStandFillingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PeriodicTwoPassStandFillingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\PeriodicTwoPassStandFillingRegime.obj"	"$(INTDIR)\PeriodicTwoPassStandFillingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\POINT.CPP

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\POINT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\POINT.OBJ"	"$(INTDIR)\POINT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RandomRank.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\RandomRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\RandomRank.obj"	"$(INTDIR)\RandomRank.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RegulateDistributionRank.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\RegulateDistributionRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\RegulateDistributionRank.obj"	"$(INTDIR)\RegulateDistributionRank.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RelativeOldestRank.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\RelativeOldestRank.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\RelativeOldestRank.obj"	"$(INTDIR)\RelativeOldestRank.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RepeatingTwoPassStandFillingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\RepeatingTwoPassStandFillingRegime.obj"	"$(INTDIR)\RepeatingTwoPassStandFillingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SiteHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\SiteHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\SiteHarvester.obj"	"$(INTDIR)\SiteHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SiteRemovalMask.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\SiteRemovalMask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\SiteRemovalMask.obj"	"$(INTDIR)\SiteRemovalMask.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\Stand.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\Stand.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\Stand.obj"	"$(INTDIR)\Stand.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\StandHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\StandHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\StandHarvester.obj"	"$(INTDIR)\StandHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\StandIterator.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\StandIterator.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\StandIterator.obj"	"$(INTDIR)\StandIterator.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\StandRankingAlgorithm.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\StandRankingAlgorithm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\StandRankingAlgorithm.obj"	"$(INTDIR)\StandRankingAlgorithm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\Stands.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\Stands.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\Stands.obj"	"$(INTDIR)\Stands.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\TwoPassStandBasedRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\TwoPassStandBasedRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\TwoPassStandBasedRegime.obj"	"$(INTDIR)\TwoPassStandBasedRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\TwoPassStandFillingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\TwoPassStandFillingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\TwoPassStandFillingRegime.obj"	"$(INTDIR)\TwoPassStandFillingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\TwoPassStandSpreadingRegime.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\TwoPassStandSpreadingRegime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\TwoPassStandSpreadingRegime.obj"	"$(INTDIR)\TwoPassStandSpreadingRegime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\UnboundedPocketStandHarvester.cpp

!IF  "$(CFG)" == "HarvestDll - Win32 Release"


"$(INTDIR)\UnboundedPocketStandHarvester.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"


"$(INTDIR)\UnboundedPocketStandHarvester.obj"	"$(INTDIR)\UnboundedPocketStandHarvester.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "HarvestDll - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\Harvestdll"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Harvestdll"

!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\Harvestdll"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Harvestdll"

!ENDIF 


!ENDIF 

