
PROJECT_HEADER_FILES=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY

g++ -std=c++14 -o Rodinia_Pathfinder_Std_Thread_Test -I$PROJECT_HEADER_FILES \
    -L$PROJECT_LIBRARY_DIRECTORY Rodinia_Pathfinder_Std_Thread_Test.cpp \
    -include Cpp_FileOperations.h -lmptools