# Microsoft Developer Studio Project File - Name="sts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=sts - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sts.mak" CFG="sts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sts - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "sts - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sts - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "sts - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "sts - Win32 Release"
# Name "sts - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\approximateEntropy.c
# End Source File
# Begin Source File

SOURCE=.\src\assess.c
# End Source File
# Begin Source File

SOURCE=.\src\blockFrequency.c
# End Source File
# Begin Source File

SOURCE=.\src\cephes.c
# End Source File
# Begin Source File

SOURCE=.\src\cusum.c
# End Source File
# Begin Source File

SOURCE=.\src\dfft.c
# End Source File
# Begin Source File

SOURCE=.\src\discreteFourierTransform.c
# End Source File
# Begin Source File

SOURCE=.\src\frequency.c
# End Source File
# Begin Source File

SOURCE=.\src\generators.c
# End Source File
# Begin Source File

SOURCE=.\src\genutils.c
# End Source File
# Begin Source File

SOURCE=.\src\getopt.c
# End Source File
# Begin Source File

SOURCE=.\src\linearComplexity.c
# End Source File
# Begin Source File

SOURCE=.\src\longestRunOfOnes.c
# End Source File
# Begin Source File

SOURCE=.\src\matrix.c
# End Source File
# Begin Source File

SOURCE=.\src\nonOverlappingTemplateMatchings.c
# End Source File
# Begin Source File

SOURCE=.\src\overlappingTemplateMatchings.c
# End Source File
# Begin Source File

SOURCE=.\src\randomExcursions.c
# End Source File
# Begin Source File

SOURCE=.\src\randomExcursionsVariant.c
# End Source File
# Begin Source File

SOURCE=.\src\rank.c
# End Source File
# Begin Source File

SOURCE=.\src\runs.c
# End Source File
# Begin Source File

SOURCE=.\src\serial.c
# End Source File
# Begin Source File

SOURCE=.\src\universal.c
# End Source File
# Begin Source File

SOURCE=.\src\utilities.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\cephes.h
# End Source File
# Begin Source File

SOURCE=.\include\config.h
# End Source File
# Begin Source File

SOURCE=.\include\decls.h
# End Source File
# Begin Source File

SOURCE=.\include\defs.h
# End Source File
# Begin Source File

SOURCE=.\include\externs.h
# End Source File
# Begin Source File

SOURCE=.\include\generators.h
# End Source File
# Begin Source File

SOURCE=.\include\genutils.h
# End Source File
# Begin Source File

SOURCE=.\include\getopt.h
# End Source File
# Begin Source File

SOURCE=.\include\matrix.h
# End Source File
# Begin Source File

SOURCE=.\include\stat_fncs.h
# End Source File
# Begin Source File

SOURCE=.\include\tailor.h
# End Source File
# Begin Source File

SOURCE=.\include\utilities.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
