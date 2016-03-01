# Microsoft Developer Studio Project File - Name="FuelDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FuelDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FuelDll.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FuelDll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\output"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\public" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 LandisProCore.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /machine:I386 /libpath:"../output"

!ELSEIF  "$(CFG)" == "FuelDll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\output"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\public" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FUELDLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib LandisProCore.lib /nologo /dll /debug /machine:I386 /def:".\source\Fuel.def" /pdbtype:sept /libpath:"..\output"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "FuelDll - Win32 Release"
# Name "FuelDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\CohortRemovalMask.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Fuel.def

!IF  "$(CFG)" == "FuelDll - Win32 Release"

!ELSEIF  "$(CFG)" == "FuelDll - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\FuelGlobalFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelManage.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelManEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelRule.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelSites.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelStand.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelStands.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelTrack.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FuelTreatmentRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestReport.cpp
# End Source File
# Begin Source File

SOURCE=.\source\IntArray.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ManagementArea.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ManagementAreaIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ManagementAreas.cpp
# End Source File
# Begin Source File

SOURCE=.\source\POINT.CPP
# End Source File
# Begin Source File

SOURCE=.\source\Reclass4.cpp
# End Source File
# Begin Source File

SOURCE=.\source\SiteHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\SiteRemovalMask.cpp
# End Source File
# Begin Source File

SOURCE=.\source\StandIterator.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\source\CohortRemovalMask.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelDefines.h
# End Source File
# Begin Source File

SOURCE=..\public\FuelGlobalFuncs.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelGlobalVariables.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelManage.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelManEvent.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelRule.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelSites.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelStand.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelStands.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelTrack.h
# End Source File
# Begin Source File

SOURCE=.\source\FuelTreatmentRank.h
# End Source File
# Begin Source File

SOURCE=.\source\HarvestReport.h
# End Source File
# Begin Source File

SOURCE=.\source\ManagementAreaIterator.h
# End Source File
# Begin Source File

SOURCE=.\source\Reclass4.h
# End Source File
# Begin Source File

SOURCE=.\source\SiteHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\SiteRemovalMask.h
# End Source File
# Begin Source File

SOURCE=.\source\StandIterator.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
