##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=wxcLib
ConfigurationName      :=Debug
WorkspacePath          := "D:\software\CodeBlocks\wxCrafterCB"
ProjectPath            := "D:\software\CodeBlocks\wxCrafterCB\wxcLib"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=PC
Date                   :=05/12/14
CodeLitePath           :="D:\software\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="wxcLib.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  $(shell wx-config --debug=no --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch).. 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --debug=no --unicode=yes) $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=D:\software\CodeLite
CBWX:=D:\software\CodeBlocks\SDK\wxWidgets-2.8.12
UNIT_TEST_PP_SRC_DIR:=D:\software\CodeLite\ut++
WXWIN:=D:\src\wxWidgets-3.0.0
WXCFG:=gcc_dll\mswu
PATH:=C:\src\codelitegit\lib\gcc_lib;$PATH;$WXWIN\lib\gcc_dll;$CBWX\lib\gcc_dll;D:\software\VS2013\VC\bin
WXWIN:=D:\software\CodeBlocks\SDK\wxWidgets-2.8.12
PATH:=$WXWIN\lib\gcc_dll;$PATH
CB_SRC_DIR:=D:\software\CodeBlocks\SDK\codeblocks-13.12
Objects0=$(IntermediateDirectory)/cJSON$(ObjectSuffix) $(IntermediateDirectory)/clSocketBase$(ObjectSuffix) $(IntermediateDirectory)/clSocketClient$(ObjectSuffix) $(IntermediateDirectory)/clSocketServer$(ObjectSuffix) $(IntermediateDirectory)/json_node$(ObjectSuffix) $(IntermediateDirectory)/wxcNetworkCommand$(ObjectSuffix) $(IntermediateDirectory)/wxcConnector$(ObjectSuffix) $(IntermediateDirectory)/wxcNetworkReply$(ObjectSuffix) $(IntermediateDirectory)/wxcNetworkReplyThread$(ObjectSuffix) $(IntermediateDirectory)/wxcReplyEventData$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "D:\software\CodeBlocks\wxCrafterCB/.build-debug"
	@echo rebuilt > "D:\software\CodeBlocks\wxCrafterCB/.build-debug/wxcLib"

PostBuild:
	@echo Executing Post Build commands ...
	copy "$(IntermediateDirectory)\lib$(ProjectName).a" ..\libs
	@echo Done

./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/cJSON$(ObjectSuffix): cJSON.cpp $(IntermediateDirectory)/cJSON$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/cJSON.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cJSON$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cJSON$(DependSuffix): cJSON.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cJSON$(ObjectSuffix) -MF$(IntermediateDirectory)/cJSON$(DependSuffix) -MM "cJSON.cpp"

$(IntermediateDirectory)/cJSON$(PreprocessSuffix): cJSON.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cJSON$(PreprocessSuffix) "cJSON.cpp"

$(IntermediateDirectory)/clSocketBase$(ObjectSuffix): clSocketBase.cpp $(IntermediateDirectory)/clSocketBase$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/clSocketBase.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clSocketBase$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clSocketBase$(DependSuffix): clSocketBase.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clSocketBase$(ObjectSuffix) -MF$(IntermediateDirectory)/clSocketBase$(DependSuffix) -MM "clSocketBase.cpp"

$(IntermediateDirectory)/clSocketBase$(PreprocessSuffix): clSocketBase.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clSocketBase$(PreprocessSuffix) "clSocketBase.cpp"

$(IntermediateDirectory)/clSocketClient$(ObjectSuffix): clSocketClient.cpp $(IntermediateDirectory)/clSocketClient$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/clSocketClient.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clSocketClient$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clSocketClient$(DependSuffix): clSocketClient.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clSocketClient$(ObjectSuffix) -MF$(IntermediateDirectory)/clSocketClient$(DependSuffix) -MM "clSocketClient.cpp"

$(IntermediateDirectory)/clSocketClient$(PreprocessSuffix): clSocketClient.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clSocketClient$(PreprocessSuffix) "clSocketClient.cpp"

$(IntermediateDirectory)/clSocketServer$(ObjectSuffix): clSocketServer.cpp $(IntermediateDirectory)/clSocketServer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/clSocketServer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/clSocketServer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/clSocketServer$(DependSuffix): clSocketServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/clSocketServer$(ObjectSuffix) -MF$(IntermediateDirectory)/clSocketServer$(DependSuffix) -MM "clSocketServer.cpp"

$(IntermediateDirectory)/clSocketServer$(PreprocessSuffix): clSocketServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/clSocketServer$(PreprocessSuffix) "clSocketServer.cpp"

$(IntermediateDirectory)/json_node$(ObjectSuffix): json_node.cpp $(IntermediateDirectory)/json_node$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/json_node.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/json_node$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_node$(DependSuffix): json_node.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/json_node$(ObjectSuffix) -MF$(IntermediateDirectory)/json_node$(DependSuffix) -MM "json_node.cpp"

$(IntermediateDirectory)/json_node$(PreprocessSuffix): json_node.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_node$(PreprocessSuffix) "json_node.cpp"

$(IntermediateDirectory)/wxcNetworkCommand$(ObjectSuffix): wxcNetworkCommand.cpp $(IntermediateDirectory)/wxcNetworkCommand$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/wxcNetworkCommand.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcNetworkCommand$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcNetworkCommand$(DependSuffix): wxcNetworkCommand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcNetworkCommand$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcNetworkCommand$(DependSuffix) -MM "wxcNetworkCommand.cpp"

$(IntermediateDirectory)/wxcNetworkCommand$(PreprocessSuffix): wxcNetworkCommand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcNetworkCommand$(PreprocessSuffix) "wxcNetworkCommand.cpp"

$(IntermediateDirectory)/wxcConnector$(ObjectSuffix): wxcConnector.cpp $(IntermediateDirectory)/wxcConnector$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/wxcConnector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcConnector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcConnector$(DependSuffix): wxcConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcConnector$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcConnector$(DependSuffix) -MM "wxcConnector.cpp"

$(IntermediateDirectory)/wxcConnector$(PreprocessSuffix): wxcConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcConnector$(PreprocessSuffix) "wxcConnector.cpp"

$(IntermediateDirectory)/wxcNetworkReply$(ObjectSuffix): wxcNetworkReply.cpp $(IntermediateDirectory)/wxcNetworkReply$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/wxcNetworkReply.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcNetworkReply$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcNetworkReply$(DependSuffix): wxcNetworkReply.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcNetworkReply$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcNetworkReply$(DependSuffix) -MM "wxcNetworkReply.cpp"

$(IntermediateDirectory)/wxcNetworkReply$(PreprocessSuffix): wxcNetworkReply.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcNetworkReply$(PreprocessSuffix) "wxcNetworkReply.cpp"

$(IntermediateDirectory)/wxcNetworkReplyThread$(ObjectSuffix): wxcNetworkReplyThread.cpp $(IntermediateDirectory)/wxcNetworkReplyThread$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/wxcNetworkReplyThread.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcNetworkReplyThread$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcNetworkReplyThread$(DependSuffix): wxcNetworkReplyThread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcNetworkReplyThread$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcNetworkReplyThread$(DependSuffix) -MM "wxcNetworkReplyThread.cpp"

$(IntermediateDirectory)/wxcNetworkReplyThread$(PreprocessSuffix): wxcNetworkReplyThread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcNetworkReplyThread$(PreprocessSuffix) "wxcNetworkReplyThread.cpp"

$(IntermediateDirectory)/wxcReplyEventData$(ObjectSuffix): wxcReplyEventData.cpp $(IntermediateDirectory)/wxcReplyEventData$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/software/CodeBlocks/wxCrafterCB/wxcLib/wxcReplyEventData.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcReplyEventData$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcReplyEventData$(DependSuffix): wxcReplyEventData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcReplyEventData$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcReplyEventData$(DependSuffix) -MM "wxcReplyEventData.cpp"

$(IntermediateDirectory)/wxcReplyEventData$(PreprocessSuffix): wxcReplyEventData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcReplyEventData$(PreprocessSuffix) "wxcReplyEventData.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/*.*
	$(RM) $(OutputFile)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/wxcLib"


