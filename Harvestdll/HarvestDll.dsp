# Microsoft Developer Studio Project File - Name="HarvestDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=HarvestDll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HarvestDll.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HarvestDll - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\public" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /D "__HARVEST__" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "HarvestDll - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\public" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "HARVESTDLL_EXPORTS" /D "__HARVEST__" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib LandisProCore.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\output"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "HarvestDll - Win32 Release"
# Name "HarvestDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\BoundedPocketStandHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CohortRemovalMask.cpp
# End Source File
# Begin Source File

SOURCE=.\source\EconomicImportanceRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FillingStandHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\GlobalFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\source\GroupSelectionRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestEventQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestPath.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestPathIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestReport.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HarvestSites.cpp
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

SOURCE=.\source\MultiplePocketStandHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\OldestRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandBasedRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandFillingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandSpreadingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\PeriodicStandFillingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\PeriodicTwoPassStandFillingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\POINT.CPP
# End Source File
# Begin Source File

SOURCE=.\source\RandomRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\RegulateDistributionRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\RelativeOldestRank.cpp
# End Source File
# Begin Source File

SOURCE=.\source\RepeatingTwoPassStandFillingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\SiteHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\SiteRemovalMask.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stand.cpp
# End Source File
# Begin Source File

SOURCE=.\source\StandHarvester.cpp
# End Source File
# Begin Source File

SOURCE=.\source\StandIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\source\StandRankingAlgorithm.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Stands.cpp
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandBasedRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandFillingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandSpreadingRegime.cpp
# End Source File
# Begin Source File

SOURCE=.\source\UnboundedPocketStandHarvester.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\source\BoundedPocketStandHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\CohortRemovalMask.h
# End Source File
# Begin Source File

SOURCE=.\source\EconomicImportanceRank.h
# End Source File
# Begin Source File

SOURCE=.\source\FillingStandHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\GroupSelectionRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\HarvestPath.h
# End Source File
# Begin Source File

SOURCE=.\source\HarvestPathIterator.h
# End Source File
# Begin Source File

SOURCE=.\source\HarvestRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\HarvestReport.h
# End Source File
# Begin Source File

SOURCE=.\source\ManagementAreaIterator.h
# End Source File
# Begin Source File

SOURCE=.\source\MultiplePocketStandHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\OldestRank.h
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandBasedRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandFillingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\OnePassStandSpreadingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\PeriodicStandFillingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\PeriodicTwoPassStandFillingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\RandomRank.h
# End Source File
# Begin Source File

SOURCE=.\source\RegulateDistributionRank.h
# End Source File
# Begin Source File

SOURCE=.\source\RelativeOldestRank.h
# End Source File
# Begin Source File

SOURCE=.\source\RepeatingTwoPassStandFillingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\SiteHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\SiteRemovalMask.h
# End Source File
# Begin Source File

SOURCE=.\source\StandHarvester.h
# End Source File
# Begin Source File

SOURCE=.\source\StandIterator.h
# End Source File
# Begin Source File

SOURCE=.\source\StandRankingAlgorithm.h
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandBasedRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandFillingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\TwoPassStandSpreadingRegime.h
# End Source File
# Begin Source File

SOURCE=.\source\UnboundedPocketStandHarvester.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
