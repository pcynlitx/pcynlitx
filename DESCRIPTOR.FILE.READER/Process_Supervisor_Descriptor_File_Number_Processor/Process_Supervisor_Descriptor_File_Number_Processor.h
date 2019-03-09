
#ifndef PROCESS_SUPERVISOR_DESCRIPTOR_FILE_NUMBER_PROCESSOR_H
#define PROCESS_SUPERVISOR_DESCRIPTOR_FILE_NUMBER_PROCESSOR_H


#include "CharOperator.h"
#include "IntToCharTranslater.h"
#include <cstring>
#include <cstdlib>

class Process_Supervisor_Descriptor_File_Number_Processor
{
public:
  Process_Supervisor_Descriptor_File_Number_Processor();
  Process_Supervisor_Descriptor_File_Number_Processor(const Process_Supervisor_Descriptor_File_Number_Processor & orig);
  virtual ~Process_Supervisor_Descriptor_File_Number_Processor();
  int Read_Record_Number_From_String_Line(char * String);
  int Read_Second_Record_Number_From_String_Line(char * String);
  int Get_Read_Operation_Start_Point(char * String);
  void Set_Zero_For_Integer_List(int ** List, int list_size);
  bool Check_Number_Repitation(int * list, int list_size);
  void Clear_Dynamic_Memory();
private:
  CharOperator CharacterOperations;
  IntToCharTranslater Translater;
  bool Memory_Delete_Condition;
  int Record_Number;
  int Read_Operation_Start_Point;
  bool Number_Repitation;
};


#endif /* PROCESS_SUPERVISOR_DESCRIPTOR_FILE_NUMBER_PROCESSOR_H */
