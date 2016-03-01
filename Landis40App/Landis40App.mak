# Microsoft Developer Studio Generated NMAKE File, Based on Landis40App.dsp
!IF "$(CFG)" == ""
CFG=Landis40App - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Landis40App - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Landis40App - Win32 Release" && "$(CFG)" != "Landis40App - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Landis40App.mak" CFG="Landis40App - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Landis40App - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Landis40App - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Landis40App.exe"

!ELSE 

ALL : "BDADll - Win32 Release" "WindDll - Win32 Release" "FireDll - Win32 Release" "FuelDll - Win32 Release" "HarvestDll - Win32 Release" "Landis40Core - Win32 Release" "$(OUTDIR)\Landis40App.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 ReleaseCLEAN" "HarvestDll - Win32 ReleaseCLEAN" "FuelDll - Win32 ReleaseCLEAN" "FireDll - Win32 ReleaseCLEAN" "WindDll - Win32 ReleaseCLEAN" "BDADll - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\IO.OBJ"
	-@erase "$(INTDIR)\LANDIS.OBJ"
	-@erase "$(INTDIR)\PARAMS.OBJ"
	-@erase "$(INTDIR)\PDP.OBJ"
	-@erase "$(INTDIR)\RECLASS.OBJ"
	-@erase "$(INTDIR)\RECLASS2.OBJ"
	-@erase "$(INTDIR)\RECLASS3.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Landis40App.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Landis40App.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Landis40App.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Landis40App.pdb" /machine:I386 /out:"$(OUTDIR)\Landis40App.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IO.OBJ" \
	"$(INTDIR)\LANDIS.OBJ" \
	"$(INTDIR)\PARAMS.OBJ" \
	"$(INTDIR)\PDP.OBJ" \
	"$(INTDIR)\RECLASS.OBJ" \
	"$(INTDIR)\RECLASS2.OBJ" \
	"$(INTDIR)\RECLASS3.OBJ" \
	"$(OUTDIR)\Landis40Core.lib" \
	"$(OUTDIR)\HarvestDll.lib" \
	"$(OUTDIR)\FuelDll.lib" \
	"$(OUTDIR)\FireDll.lib" \
	"$(OUTDIR)\WindDll.lib" \
	"$(OUTDIR)\BDADll.lib"

"$(OUTDIR)\Landis40App.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Landis40App.exe" "$(OUTDIR)\Landis40App.bsc"

!ELSE 

ALL : "BDADll - Win32 Debug" "WindDll - Win32 Debug" "FireDll - Win32 Debug" "FuelDll - Win32 Debug" "HarvestDll - Win32 Debug" "Landis40Core - Win32 Debug" "$(OUTDIR)\Landis40App.exe" "$(OUTDIR)\Landis40App.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Landis40Core - Win32 DebugCLEAN" "HarvestDll - Win32 DebugCLEAN" "FuelDll - Win32 DebugCLEAN" "FireDll - Win32 DebugCLEAN" "WindDll - Win32 DebugCLEAN" "BDADll - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\IO.OBJ"
	-@erase "$(INTDIR)\IO.SBR"
	-@erase "$(INTDIR)\LANDIS.OBJ"
	-@erase "$(INTDIR)\LANDIS.SBR"
	-@erase "$(INTDIR)\PARAMS.OBJ"
	-@erase "$(INTDIR)\PARAMS.SBR"
	-@erase "$(INTDIR)\PDP.OBJ"
	-@erase "$(INTDIR)\PDP.SBR"
	-@erase "$(INTDIR)\RECLASS.OBJ"
	-@erase "$(INTDIR)\RECLASS.SBR"
	-@erase "$(INTDIR)\RECLASS2.OBJ"
	-@erase "$(INTDIR)\RECLASS2.SBR"
	-@erase "$(INTDIR)\RECLASS3.OBJ"
	-@erase "$(INTDIR)\RECLASS3.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Landis40App.bsc"
	-@erase "$(OUTDIR)\Landis40App.exe"
	-@erase "$(OUTDIR)\Landis40App.ilk"
	-@erase "$(OUTDIR)\Landis40App.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Landis40App.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Landis40App.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\IO.SBR" \
	"$(INTDIR)\LANDIS.SBR" \
	"$(INTDIR)\PARAMS.SBR" \
	"$(INTDIR)\PDP.SBR" \
	"$(INTDIR)\RECLASS.SBR" \
	"$(INTDIR)\RECLASS2.SBR" \
	"$(INTDIR)\RECLASS3.SBR"

"$(OUTDIR)\Landis40App.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Landis40Core.lib SUCCESSION.lib FuelDll.lib FireDll.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Landis40App.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Landis40App.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IO.OBJ" \
	"$(INTDIR)\LANDIS.OBJ" \
	"$(INTDIR)\PARAMS.OBJ" \
	"$(INTDIR)\PDP.OBJ" \
	"$(INTDIR)\RECLASS.OBJ" \
	"$(INTDIR)\RECLASS2.OBJ" \
	"$(INTDIR)\RECLASS3.OBJ" \
	"$(OUTDIR)\Landis40Core.lib" \
	"$(OUTDIR)\HarvestDll.lib" \
	"$(OUTDIR)\FuelDll.lib" \
	"$(OUTDIR)\FireDll.lib" \
	"$(OUTDIR)\WindDll.lib" \
	"$(OUTDIR)\BDADll.lib"

"$(OUTDIR)\Landis40App.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Landis40App.dep")
!INCLUDE "Landis40App.dep"
!ELSE 
!MESSAGE Warning: cannot find "Landis40App.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Landis40App - Win32 Release" || "$(CFG)" == "Landis40App - Win32 Debug"
SOURCE=.\source\IO.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\IO.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\IO.OBJ"	"$(INTDIR)\IO.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\LANDIS.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\LANDIS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\LANDIS.OBJ"	"$(INTDIR)\LANDIS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PARAMS.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\PARAMS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\PARAMS.OBJ"	"$(INTDIR)\PARAMS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PDP.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\PDP.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\PDP.OBJ"	"$(INTDIR)\PDP.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RECLASS.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\RECLASS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\RECLASS.OBJ"	"$(INTDIR)\RECLASS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RECLASS2.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\RECLASS2.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\RECLASS2.OBJ"	"$(INTDIR)\RECLASS2.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\RECLASS3.CPP

!IF  "$(CFG)" == "Landis40App - Win32 Release"


"$(INTDIR)\RECLASS3.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"


"$(INTDIR)\RECLASS3.OBJ"	"$(INTDIR)\RECLASS3.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"Landis40Core - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" 
   cd "..\Landis40App"

"Landis40Core - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"Landis40Core - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" 
   cd "..\Landis40App"

"Landis40Core - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Landis40Core"
   $(MAKE) /$(MAKEFLAGS) /F .\Landis40Core.mak CFG="Landis40Core - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"HarvestDll - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\Harvestdll"
   $(MAKE) /$(MAKEFLAGS) /F .\HarvestDll.mak CFG="HarvestDll - Win32 Release" 
   cd "..\Landis40App"

"HarvestDll - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Harvestdll"
   $(MAKE) /$(MAKEFLAGS) /F .\HarvestDll.mak CFG="HarvestDll - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"HarvestDll - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\Harvestdll"
   $(MAKE) /$(MAKEFLAGS) /F .\HarvestDll.mak CFG="HarvestDll - Win32 Debug" 
   cd "..\Landis40App"

"HarvestDll - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\Harvestdll"
   $(MAKE) /$(MAKEFLAGS) /F .\HarvestDll.mak CFG="HarvestDll - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"FuelDll - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\FuelDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FuelDll.mak CFG="FuelDll - Win32 Release" 
   cd "..\Landis40App"

"FuelDll - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\FuelDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FuelDll.mak CFG="FuelDll - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"FuelDll - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\FuelDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FuelDll.mak CFG="FuelDll - Win32 Debug" 
   cd "..\Landis40App"

"FuelDll - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\FuelDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FuelDll.mak CFG="FuelDll - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"FireDll - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\FireDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FireDll.mak CFG="FireDll - Win32 Release" 
   cd "..\Landis40App"

"FireDll - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\FireDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FireDll.mak CFG="FireDll - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"FireDll - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\FireDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FireDll.mak CFG="FireDll - Win32 Debug" 
   cd "..\Landis40App"

"FireDll - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\FireDll"
   $(MAKE) /$(MAKEFLAGS) /F .\FireDll.mak CFG="FireDll - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"WindDll - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\WindDll"
   $(MAKE) /$(MAKEFLAGS) /F .\WindDll.mak CFG="WindDll - Win32 Release" 
   cd "..\Landis40App"

"WindDll - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\WindDll"
   $(MAKE) /$(MAKEFLAGS) /F .\WindDll.mak CFG="WindDll - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"WindDll - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\WindDll"
   $(MAKE) /$(MAKEFLAGS) /F .\WindDll.mak CFG="WindDll - Win32 Debug" 
   cd "..\Landis40App"

"WindDll - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\WindDll"
   $(MAKE) /$(MAKEFLAGS) /F .\WindDll.mak CFG="WindDll - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 

!IF  "$(CFG)" == "Landis40App - Win32 Release"

"BDADll - Win32 Release" : 
   cd "\fireDLL\Landis4.0dll5\BDADll"
   $(MAKE) /$(MAKEFLAGS) /F .\BDADll.mak CFG="BDADll - Win32 Release" 
   cd "..\Landis40App"

"BDADll - Win32 ReleaseCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\BDADll"
   $(MAKE) /$(MAKEFLAGS) /F .\BDADll.mak CFG="BDADll - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ELSEIF  "$(CFG)" == "Landis40App - Win32 Debug"

"BDADll - Win32 Debug" : 
   cd "\fireDLL\Landis4.0dll5\BDADll"
   $(MAKE) /$(MAKEFLAGS) /F .\BDADll.mak CFG="BDADll - Win32 Debug" 
   cd "..\Landis40App"

"BDADll - Win32 DebugCLEAN" : 
   cd "\fireDLL\Landis4.0dll5\BDADll"
   $(MAKE) /$(MAKEFLAGS) /F .\BDADll.mak CFG="BDADll - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Landis40App"

!ENDIF 


!ENDIF 

