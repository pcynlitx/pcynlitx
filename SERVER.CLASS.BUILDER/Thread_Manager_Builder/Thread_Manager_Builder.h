
#ifndef THREAD_MANAGER_BUILDER_H
#define THREAD_MANAGER_BUILDER_H

#include <cstring>
#include <cstdlib>
#include "CFileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "Thread_Locker_Builder.h"
#include "Thread_Manager_Header_File_Builder.h"
#include "Descriptor_File_Reader.h"

class Thread_Manager_Builder
{
public:
 Thread_Manager_Builder();
 Thread_Manager_Builder(const Thread_Manager_Builder & orig);
 virtual ~Thread_Manager_Builder();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 void Build_Thread_Manager();
 void Receive_Constructed_Include_Directory(char * Directory);
 void Run_System_Commands();
 void Clear_Dynamic_Memory();
private:
 void Determine_Compiler_Command();
 void Remove_Source_File();
 void Remove_Header_Extra_File();
 void Move_Header_File();
 void Place_Information(char ** Pointer, char * Information, int * Counter);
 Thread_Locker_Builder Locker_Builder;
 Descriptor_File_Reader * Reader_Pointer;
 Thread_Manager_Header_File_Builder HeaderFileBuilder;
 CFileOperations FileManager;
 DirectoryOperations Directory_Manager;
 IntToCharTranslater Translater;
 bool   Memory_Delete_Condition;
 char * Compiler_Command;
 char * Constructed_Include_Directory;
};

#endif /* THREAD_MANAGER_BUILDER_H */
