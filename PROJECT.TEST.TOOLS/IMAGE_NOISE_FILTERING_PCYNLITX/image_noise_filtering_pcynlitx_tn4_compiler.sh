
g++ -I/home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX/Thread_Server_Include_Directory \
    -I/home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX \
    -L/home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX \
    -o image_noise_filtering_pcynlitx_tn4 image_noise_filtering_pcynlitx_tn4.cpp Loop_Interval.cpp \
    -include Loop_Interval_Client.h -include Loop_Interval.h -include MT_Library_Headers.h \
    -include TM_Client.h -include Thread_Manager.h -include Thread_Server.h -include itds.h \
    -include Thread_Locker.h -lThread_Server `pkg-config --cflags --libs opencv` -lpthread