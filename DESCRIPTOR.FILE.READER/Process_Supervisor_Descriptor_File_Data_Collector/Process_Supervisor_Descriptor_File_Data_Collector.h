
#ifndef PROCESS_SUPERVISOR_DESCRIPTOR_FILE_DATA_COLLECTOR_H
#define PROCESS_SUPERVISOR_DESCRIPTOR_FILE_DATA_COLLECTOR_H

#include <cstring>
#include <cstdlib>
#include "StringOperator.h"
#include "DirectoryOperations.h"

class Process_Supervisor_Descriptor_File_Data_Collector
{
public:
  Process_Supervisor_Descriptor_File_Data_Collector();
  Process_Supervisor_Descriptor_File_Data_Collector(const Process_Supervisor_Descriptor_File_Data_Collector & orig);
  virtual ~Process_Supervisor_Descriptor_File_Data_Collector();
  void Receive_Descriptor_File_Directory(const char * DescriptorFileDirectory);
  void Receive_Descriptor_File_Directory(char * DescriptorFileDirectory);
  void Receive_Descriptor_File_Name(const char * DescriptorFileName);
  void Receive_Descriptor_File_Name(char * DescriptorFileName);
  void Collect_Descriptor_File_Datas();
  void Place_String(char ** Pointer, const char * String, int String_Size);
  void Place_String(char ** Pointer, char * String, int String_Size);
  void Clear_Dynamic_Memory();
  char * Get_DescriptorFileName();
  char * Get_DescriptorFileDirectory();
  StringOperator StringOperations;
  DirectoryOperations DirectoryManager;
  int Include_Directory_Numbers;
  int Source_File_Location_Number;
  int Source_File_Number;
  int Library_Directory_Number;
  int Library_Names_Number;
  int Header_File_Names_Number;
  int Executable_File_Name_Record_Number;
  int Main_File_Name_Record_Number;
  int Inter_Thread_Class_Header_File_Names_Number;
  int Class_Number;
  int Class_Instance_Number;
  int Shared_Data_Types_Number;
  int Shared_Data_Types_Include_File_Names_Number;
  int Shared_Data_Type_Pointer_Names_Number;
  int Construction_Point_Record_Number;
  int Supervisor_Class_Name_Record_Number;
  int Record_Line_Number_for_Total_Thread_Number;
  int Thread_Function_Number;
  int Include_Directory_Record_Area[2];
  int Library_Directories_Record_Area[2];
  int Source_File_Locations_Record_Area[2];
  int Source_File_Names_Record_Area[2];
  int Main_File_Name_Record_Area[2];
  int Executable_File_Name_Record_Area[2];
  int Library_Names_Record_Area[2];
  int Header_File_Names_Record_Area[2];
  int Inter_Thread_Class_Header_File_Names_Record_Area[2];
  int Class_Names_Record_Area[2];
  int Class_Instance_Record_Area[2];
  int Shared_Data_Types_Include_Files_Record_Area[2];
  int Shared_Data_Types_Record_Area[2];
  int Shared_Data_Type_Pointer_Names_Record_Area[2];
  int Supervisor_Class_Construction_Point_Record_Area[2];
  int Supervisor_Class_Name_Record_Area[2];
  int Thread_Numbers_Record_Area[2];
  int Thread_Names_Record_Area[2];
private:
  void ReadConstString(const char * ConstString);
  char * GetConstString();
  void Clear_Pointer_Memory(char ** Pointer);
  void Determine_Data_Record_Area(const char * Start_Point, const char * End_Point);
  int  Determine_Record_Number(int Start_Point, int End_Point);
  void Determine_Record_Lines();
  void Determine_Data_Record_Numbers();
  void Print_End_of_Program();
  void Print_Read_Error_Information();
  char * DescriptorFileName;
  char * DescriptorFileDirectory;
  char * ConstString;
  int  Data_Record_StartLine;
  int  Data_Record_EndLine;
  int  Record_Number;
  bool Memory_Delete_Condition;
  bool DescriptorFileName_Receive_Condition;
  bool DescriptorFileDirectory_Receive_Condition;
};

#endif /* PROCESS_SUPERVISOR_DESCRIPTOR_FILE_DATA_COLLECTOR_H */
