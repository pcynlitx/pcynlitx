
BASE_DIRECTORY=~/PRODUCER_CONSUMER_PCYNLITX
APP_SPEC_LIBRARY_HEADERS=$BASE_DIRECTORY/Thread_Server_Include_Directory
PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY

g++ -I$BASE_DIRECTORY -I$APP_SPEC_LIBRARY_HEADERS -I$PROJECT_HEADERS \
    -L$BASE_DIRECTORY -L$PROJECT_LIBRARY \
    -o Producer_Consumer_Pcynlitx_tn64 Producer_Consumer_Pcynlitx_tn64.cpp \
     Data_Reader.cpp Data_Recorder.cpp -include Producer_Consumer_Pcynlitx.h \
    -include Data_Reader_Client.h -include Data_Recorder_Client.h \
    -include Data_Reader.h -include Data_Recorder.h \
    -include Data_Reader_Types.h -include Data_Recorder_Types.h \
    -include MT_Library_Headers.h -include TM_Client.h -include Thread_Manager.h \
    -include Thread_Server.h -include itds.h -include Thread_Locker.h \
    -include Cpp_FileOperations.h -include IntToCharTranslater.h \
    -lThread_Server -lmptools -lm -lpthread
