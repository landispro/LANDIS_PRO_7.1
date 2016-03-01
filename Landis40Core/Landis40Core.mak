# Microsoft Developer Studio Generated NMAKE File, Based on Landis40Core.dsp
!IF "$(CFG)" == ""
CFG=Landis40Core - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Landis40Core - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Landis40Core - Win32 Release" && "$(CFG)" != "Landis40Core - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Landis40Core.mak" CFG="Landis40Core - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Landis40Core - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Landis40Core - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Landis40Core - Win32 Release"

OUTDIR=D:\fireDLL\Landis4.0dll5\release
INTDIR=.\Release
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\release
# End Custom Macros

ALL : "$(OUTDIR)\Landis40Core.dll"


CLEAN :
	-@erase "$(INTDIR)\AGELIST.OBJ"
	-@erase "$(INTDIR)\ERROR.OBJ"
	-@erase "$(INTDIR)\LANDU.OBJ"
	-@erase "$(INTDIR)\LANDUS.OBJ"
	-@erase "$(INTDIR)\Map8.obj"
	-@erase "$(INTDIR)\SITE.OBJ"
	-@erase "$(INTDIR)\SITES.OBJ"
	-@erase "$(INTDIR)\SPECATT.OBJ"
	-@erase "$(INTDIR)\SPECATTS.OBJ"
	-@erase "$(INTDIR)\SPECIE.OBJ"
	-@erase "$(INTDIR)\SPECIES.OBJ"
	-@erase "$(INTDIR)\SYSTEM1.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Landis40Core.dll"
	-@erase "$(OUTDIR)\Landis40Core.exp"
	-@erase "$(OUTDIR)\Landis40Core.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LANDIS40CORE_EXPORTS" /Fp"$(INTDIR)\Landis40Core.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Landis40Core.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\Landis40Core.pdb" /machine:I386 /out:"$(OUTDIR)\Landis40Core.dll" /implib:"$(OUTDIR)\Landis40Core.lib" 
LINK32_OBJS= \
	"$(INTDIR)\AGELIST.OBJ" \
	"$(INTDIR)\ERROR.OBJ" \
	"$(INTDIR)\LANDU.OBJ" \
	"$(INTDIR)\LANDUS.OBJ" \
	"$(INTDIR)\Map8.obj" \
	"$(INTDIR)\SITE.OBJ" \
	"$(INTDIR)\SITES.OBJ" \
	"$(INTDIR)\SPECATT.OBJ" \
	"$(INTDIR)\SPECATTS.OBJ" \
	"$(INTDIR)\SPECIE.OBJ" \
	"$(INTDIR)\SPECIES.OBJ" \
	"$(INTDIR)\SYSTEM1.OBJ"

"$(OUTDIR)\Landis40Core.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"

OUTDIR=D:\fireDLL\Landis4.0dll5\output
INTDIR=.\Debug
# Begin Custom Macros
OutDir=D:\fireDLL\Landis4.0dll5\output
# End Custom Macros

ALL : "$(OUTDIR)\Landis40Core.dll" "$(OUTDIR)\Landis40Core.bsc"


CLEAN :
	-@erase "$(INTDIR)\AGELIST.OBJ"
	-@erase "$(INTDIR)\AGELIST.SBR"
	-@erase "$(INTDIR)\ERROR.OBJ"
	-@erase "$(INTDIR)\ERROR.SBR"
	-@erase "$(INTDIR)\LANDU.OBJ"
	-@erase "$(INTDIR)\LANDU.SBR"
	-@erase "$(INTDIR)\LANDUS.OBJ"
	-@erase "$(INTDIR)\LANDUS.SBR"
	-@erase "$(INTDIR)\Map8.obj"
	-@erase "$(INTDIR)\Map8.sbr"
	-@erase "$(INTDIR)\SITE.OBJ"
	-@erase "$(INTDIR)\SITE.SBR"
	-@erase "$(INTDIR)\SITES.OBJ"
	-@erase "$(INTDIR)\SITES.SBR"
	-@erase "$(INTDIR)\SPECATT.OBJ"
	-@erase "$(INTDIR)\SPECATT.SBR"
	-@erase "$(INTDIR)\SPECATTS.OBJ"
	-@erase "$(INTDIR)\SPECATTS.SBR"
	-@erase "$(INTDIR)\SPECIE.OBJ"
	-@erase "$(INTDIR)\SPECIE.SBR"
	-@erase "$(INTDIR)\SPECIES.OBJ"
	-@erase "$(INTDIR)\SPECIES.SBR"
	-@erase "$(INTDIR)\SYSTEM1.OBJ"
	-@erase "$(INTDIR)\SYSTEM1.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Landis40Core.bsc"
	-@erase "$(OUTDIR)\Landis40Core.dll"
	-@erase "$(OUTDIR)\Landis40Core.exp"
	-@erase "$(OUTDIR)\Landis40Core.ilk"
	-@erase "$(OUTDIR)\Landis40Core.lib"
	-@erase "$(OUTDIR)\Landis40Core.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LANDIS40CORE_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Landis40Core.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Landis40Core.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AGELIST.SBR" \
	"$(INTDIR)\ERROR.SBR" \
	"$(INTDIR)\LANDU.SBR" \
	"$(INTDIR)\LANDUS.SBR" \
	"$(INTDIR)\Map8.sbr" \
	"$(INTDIR)\SITE.SBR" \
	"$(INTDIR)\SITES.SBR" \
	"$(INTDIR)\SPECATT.SBR" \
	"$(INTDIR)\SPECATTS.SBR" \
	"$(INTDIR)\SPECIE.SBR" \
	"$(INTDIR)\SPECIES.SBR" \
	"$(INTDIR)\SYSTEM1.SBR"

"$(OUTDIR)\Landis40Core.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\Landis40Core.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Landis40Core.dll" /implib:"$(OUTDIR)\Landis40Core.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AGELIST.OBJ" \
	"$(INTDIR)\ERROR.OBJ" \
	"$(INTDIR)\LANDU.OBJ" \
	"$(INTDIR)\LANDUS.OBJ" \
	"$(INTDIR)\Map8.obj" \
	"$(INTDIR)\SITE.OBJ" \
	"$(INTDIR)\SITES.OBJ" \
	"$(INTDIR)\SPECATT.OBJ" \
	"$(INTDIR)\SPECATTS.OBJ" \
	"$(INTDIR)\SPECIE.OBJ" \
	"$(INTDIR)\SPECIES.OBJ" \
	"$(INTDIR)\SYSTEM1.OBJ"

"$(OUTDIR)\Landis40Core.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Landis40Core.dep")
!INCLUDE "Landis40Core.dep"
!ELSE 
!MESSAGE Warning: cannot find "Landis40Core.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Landis40Core - Win32 Release" || "$(CFG)" == "Landis40Core - Win32 Debug"
SOURCE=.\source\AGELIST.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\AGELIST.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\AGELIST.OBJ"	"$(INTDIR)\AGELIST.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\ERROR.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\ERROR.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\ERROR.OBJ"	"$(INTDIR)\ERROR.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\LANDU.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\LANDU.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\LANDU.OBJ"	"$(INTDIR)\LANDU.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\LANDUS.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\LANDUS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\LANDUS.OBJ"	"$(INTDIR)\LANDUS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\Map8.cpp

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\Map8.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\Map8.obj"	"$(INTDIR)\Map8.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SITE.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SITE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SITE.OBJ"	"$(INTDIR)\SITE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SITES.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SITES.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SITES.OBJ"	"$(INTDIR)\SITES.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SPECATT.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SPECATT.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SPECATT.OBJ"	"$(INTDIR)\SPECATT.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SPECATTS.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SPECATTS.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SPECATTS.OBJ"	"$(INTDIR)\SPECATTS.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SPECIE.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SPECIE.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SPECIE.OBJ"	"$(INTDIR)\SPECIE.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SPECIES.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SPECIES.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SPECIES.OBJ"	"$(INTDIR)\SPECIES.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\SYSTEM1.CPP

!IF  "$(CFG)" == "Landis40Core - Win32 Release"


"$(INTDIR)\SYSTEM1.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Landis40Core - Win32 Debug"


"$(INTDIR)\SYSTEM1.OBJ"	"$(INTDIR)\SYSTEM1.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

