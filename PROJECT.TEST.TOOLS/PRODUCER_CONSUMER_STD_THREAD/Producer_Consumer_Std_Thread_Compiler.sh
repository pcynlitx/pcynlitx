
g++ -std=c++14 -o Producer_Consumer_Std_Thread -I/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES \
-L/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY \
Producer_Consumer_Std_Thread.cpp Data_Receiver.cpp Producer_Consumer_Std_Thread.h -include Data_Receiver.h \
-lmptools -lpthread