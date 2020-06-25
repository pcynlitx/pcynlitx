

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include "Cpp_FileOperations.h"

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer);

void Determination_of_test_command(char ** test_command, char * thread_number, char * swaptions, char * simulations);

int main(int argc, char ** argv){

    if(argc != 5) {

      std::cout << "\n\n   Usage: " << argv[0] << " [Repitation] [Thread Number] [Swaptions] [Simulations]" << std::endl;

      std::cout << "\n\n";

      exit(1);
    }

    std::cout << "\n\n PARSEC SWAPTIONS STD-THREAD TEST";

    std::cout << "\n";

    int sum = 0;

    std::string test_repitation = "";

    Convert_char_to_std_string(&test_repitation,argv[1]);

    std::stringstream s(test_repitation);

    int repitation = 0;

    s >> repitation;

    std::cout << "\n The number of repitation:" << repitation;

    std::cout << "\n";

    char * test_command = nullptr;

    Determination_of_test_command(&test_command,argv[2],argv[3],argv[4]);

    std::cout << "\n\n Test Command:";

    std::cout << "\n\n ";

    std::cout << test_command;

    std::cout << "\n\n Press Enter ..";

    std::cin.get();

    Cpp_FileOperations FileManager;

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(RWCf);

    FileManager.FileClose();

    for(int i=0;i<repitation;i++){

       system(test_command);

       std::cout << "\n the test [" << i << "] has been complated..";

       system("echo \"\n\" >> Test_Record_File");
    }

    FileManager.SetFilePath("Test_Record_File");

    FileManager.FileOpen(Rf);

    std::string test_result = "";

    while(!FileManager.Control_End_of_File()){

          test_result = FileManager.ReadLine();

          if(test_result[0] != '\n'){

             std::stringstream s(test_result);

             int test_output = 0;

             s >> test_output;

             sum = sum + test_output;

             if(test_output != 0){

                std::cout << "\n sum:" << sum;
             }
          }
    }

    FileManager.FileClose();

    std::cout << "\n\n -------------------------------------";

    std::cout << "\n the average:" << ((double)sum)/repitation << std::endl;

    std::cout << "\n\n";

    delete [] test_command;

    return 0;
}

void Convert_char_to_std_string(std::string * string_line, char * cstring_pointer){

    int string_length = strlen(cstring_pointer);

    for(int i=0;i<string_length;i++){

        *string_line = *string_line + cstring_pointer[i];
    }
}

void Determination_of_test_command(char ** test_command, char * thread_number, char * swaptions, char * simulations){

     char space = ' ';

     char directory_operator []= "./";

     char send_command [] = ">>";

     char Test_Record_File [] = "Test_Record_File";

     char exe_file [] = "parsec_swaptions_std_thread";

     int exe_file_character_size = strlen(exe_file);

     int swaptions_character_size = strlen(swaptions);

     int simulations_character_size = strlen(simulations);

     int Send_Command_Name_Size = strlen(send_command);

     int Directory_Operator_Size = strlen(directory_operator);

     int Test_Record_File_Character_Size = strlen(Test_Record_File);

     int thread_number_character_size = strlen(thread_number);

     int command_size = exe_file_character_size + swaptions_character_size

                        + Test_Record_File_Character_Size + Send_Command_Name_Size

                        + simulations_character_size + thread_number_character_size;

     *test_command = new char [5*command_size];

     int index_number = 0;

     for(int i=0;i<Directory_Operator_Size;i++){

         (*test_command)[index_number] = directory_operator[i];

         index_number++;
     }

     for(int i=0;i<exe_file_character_size;i++)
     {
         (*test_command)[index_number] = exe_file[i];

         index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<thread_number_character_size;i++){

        (*test_command)[index_number] = thread_number[i];

        index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<swaptions_character_size;i++){

        (*test_command)[index_number] = swaptions[i];

        index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<simulations_character_size;i++){

        (*test_command)[index_number] = simulations[i];

        index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<Send_Command_Name_Size;i++){

         (*test_command)[index_number] = send_command[i];

         index_number++;
     }

     (*test_command)[index_number] = space;

     index_number++;

     for(int i=0;i<Test_Record_File_Character_Size;i++){

         (*test_command)[index_number] = Test_Record_File[i];

         index_number++;
     }

     (*test_command)[index_number] = '\0';
}
