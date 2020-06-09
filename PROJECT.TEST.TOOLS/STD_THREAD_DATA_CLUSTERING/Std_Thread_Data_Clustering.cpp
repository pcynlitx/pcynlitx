
#include "Std_Thread_Data_Clustering.h"
#include <thread>
#include <iomanip>

int Elapsed_Time = 0;

int data_matrix_size = 1000;

int First_Pool_Start_Index = 0;

int Second_Pool_Start_Index = data_matrix_size/2;

int num_threads = 0;

int first_pool_thread_number_in_start = 0;

int second_pool_thread_number_in_start = 0;

int first_pool_thread_number_in_end = 0;

int second_pool_thread_number_in_end = 0;

int first_pool_arrange_index = 0;

int second_pool_arrange_index = Second_Pool_Start_Index;

#define FIRST_POOL_END_POINT data_matrix_size/2

#define SECOND_POOL_END_POINT data_matrix_size

#define FIRST_POOL_THREAD_NUMBER num_threads/2

#define SECOND_POOL_THREAD_NUMBER (num_threads - (num_threads/2))

#define FIRST_POOL_THREAD_SEARCH_CONDITION (first_pool_thread_number_in_end < FIRST_POOL_THREAD_NUMBER)

#define SECOND_POOL_THREAD_SEARCH_CONDITION (second_pool_thread_number_in_end < SECOND_POOL_THREAD_NUMBER)

#define THREAD_SEARCH_CONDITION (first_pool_thread_number_in_end < FIRST_POOL_THREAD_NUMBER) || (second_pool_thread_number_in_end < SECOND_POOL_THREAD_NUMBER)

double ** data_matrix = nullptr;

double ** result_matrix = nullptr;

double lower_bound = 0;

double upper_bound = 500;

std::uniform_real_distribution<double> unif(lower_bound,upper_bound);

std::default_random_engine re;

void Construct_Random_Matrix(double *** pointer, int matrix_size);

void Rearrange_The_Row(int row_number);

void Rearrange_The_Column(int column_number);

void Clear_Heap_Memory(double *** pointer, int matrix_size);

void Print_Data();

void Print_Column(int column_number);

std::mutex mtx_tp1;
std::mutex mtx_tp2;
std::mutex mtx_common;

std::condition_variable cv_tp1;
std::condition_variable cv_tp2;
std::condition_variable cv_tp12;

int first_pool_thread_number_in_barrier = 0;

int second_pool_thread_number_in_barrier = 0;

int common_barrier_thread_number = 0;


void First_Pool_Function(int thread_number, int num_threads);

void Second_Pool_Function(int thread_number, int num_threads);


int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n usage: " << argv[0] << " <thread number>";

       std::cout << "\n\n";

       exit(0);
    }

    Construct_Random_Matrix(&data_matrix,data_matrix_size);

    IntToCharTranslater Translater;

    num_threads = Translater.TranslateFromCharToInt(argv[1]);

    if((num_threads%2)!=0){

        std::cout << "\n\n The number of the threads must be selected as multiple of two..";

        std::cout << "\n\n";
    }

    std::thread threads[num_threads];

    struct rusage usage;

    struct timeval start, end;

    int return_value = getrusage(RUSAGE_SELF,&usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    start = usage.ru_utime;


    for(int i=0;i<FIRST_POOL_THREAD_NUMBER;i++){

        threads[i] = std::thread(First_Pool_Function,i,num_threads);
    }

    for(int i=SECOND_POOL_THREAD_NUMBER;i<num_threads;i++){

        threads[i] = std::thread(Second_Pool_Function,i,num_threads);
    }

    for(int i=0;i<num_threads;i++){

        threads[i].join();
    }

    return_value = getrusage(RUSAGE_SELF, &usage);

    if(return_value!= 0){

       std::cout << "\n The usage data can not be obtain..\n";

       return 0;
    }

    end = usage.ru_utime;

    Elapsed_Time = end.tv_sec - start.tv_sec;

    Clear_Heap_Memory(&data_matrix,data_matrix_size);

    std::cout << Elapsed_Time << std::endl;

    return 0;
}


 void First_Pool_Function(int thread_number, int num_threads){

      std::unique_lock<std::mutex> tp1_lck(mtx_tp1);

      tp1_lck.unlock();

      std::unique_lock<std::mutex> common_lck(mtx_common);

      common_lck.unlock();


      // START OF THE ENTRANCE BARRIER

      tp1_lck.lock();

      first_pool_thread_number_in_start++;

      if(first_pool_thread_number_in_start < FIRST_POOL_THREAD_NUMBER ){

         cv_tp1.wait(tp1_lck);

         tp1_lck.unlock();
      }
      else{

           tp1_lck.unlock();
      }

      tp1_lck.lock();

      first_pool_thread_number_in_start--;

      tp1_lck.unlock();


      tp1_lck.lock();

      if(first_pool_thread_number_in_start > 0){

         cv_tp1.notify_all();
      }

      tp1_lck.unlock();


      // START OF THE ENTRANCE BARRIER


      do {

           tp1_lck.lock();  // SERIAL EXECUTION BARRIER

           first_pool_thread_number_in_barrier++;

           if(first_pool_thread_number_in_barrier < FIRST_POOL_THREAD_NUMBER){

              cv_tp1.wait(tp1_lck);

              tp1_lck.unlock();


              tp1_lck.lock();

              first_pool_thread_number_in_barrier--;

              tp1_lck.unlock();
           }
           else{

                 if(first_pool_arrange_index < FIRST_POOL_END_POINT){

                    Rearrange_The_Row(first_pool_arrange_index);

                    first_pool_arrange_index++;
                 }

                 cv_tp1.notify_one();

                 cv_tp1.wait(tp1_lck);

                 tp1_lck.unlock();
          }

      }while(first_pool_arrange_index < FIRST_POOL_END_POINT);



      tp1_lck.lock();

      first_pool_thread_number_in_end++;

      tp1_lck.unlock();


      do {

        if(FIRST_POOL_THREAD_SEARCH_CONDITION){

           cv_tp1.notify_all();
        }

      } while(FIRST_POOL_THREAD_SEARCH_CONDITION);



      if(thread_number == 0){

         first_pool_thread_number_in_barrier = 0;

         first_pool_arrange_index = 0;
      }


      common_lck.lock();

      common_barrier_thread_number++;

      if(common_barrier_thread_number < num_threads ){

         cv_tp12.wait(common_lck);

         common_lck.unlock();

         common_lck.lock();

         common_barrier_thread_number--;

         common_lck.unlock();
      }
      else{

           common_lck.unlock();

           cv_tp12.notify_all();
      }


      if(thread_number == 0){

         first_pool_thread_number_in_end = 0;
      }


      do {

           tp1_lck.lock();  // SERIAL EXECUTION BARRIER

           first_pool_thread_number_in_barrier++;

           if(first_pool_thread_number_in_barrier < FIRST_POOL_THREAD_NUMBER){

              cv_tp1.wait(tp1_lck);

              tp1_lck.unlock();


              tp1_lck.lock();

              first_pool_thread_number_in_barrier--;

              tp1_lck.unlock();
           }
           else{

                 if(first_pool_arrange_index < FIRST_POOL_END_POINT){

                    Rearrange_The_Column(first_pool_arrange_index);

                    first_pool_arrange_index++;
                 }

                 cv_tp1.notify_one();

                 cv_tp1.wait(tp1_lck);

                 tp1_lck.unlock();
          }

      }while(first_pool_arrange_index < FIRST_POOL_END_POINT);


     tp1_lck.lock();

     first_pool_thread_number_in_end++;

     tp1_lck.unlock();


     do {

        if(FIRST_POOL_THREAD_SEARCH_CONDITION){

           cv_tp1.notify_all();
        }

     } while(FIRST_POOL_THREAD_SEARCH_CONDITION);
 }


// --------------------------------------------------------------------------------

//  Writer threads function


void Second_Pool_Function(int thread_number, int num_threads){

     std::unique_lock<std::mutex> tp2_lck(mtx_tp2);

     tp2_lck.unlock();

     std::unique_lock<std::mutex> common_lck(mtx_common);

     common_lck.unlock();


     // START OF THE ENTRANCE BARRIER

     tp2_lck.lock();

     second_pool_thread_number_in_start++;

     if(second_pool_thread_number_in_start < SECOND_POOL_THREAD_NUMBER ){

        cv_tp2.wait(tp2_lck);

        tp2_lck.unlock();
     }
     else{

           tp2_lck.unlock();
     }

     tp2_lck.lock();

     second_pool_thread_number_in_start--;

     tp2_lck.unlock();


     tp2_lck.lock();

     if(second_pool_thread_number_in_start > 0){

        cv_tp2.notify_all();
     }

     tp2_lck.unlock();


     // START OF THE ENTRANCE BARRIER

     do {

         tp2_lck.lock();  // SERIAL EXECUTION BARRIER

         second_pool_thread_number_in_barrier++;

         if(second_pool_thread_number_in_barrier < SECOND_POOL_THREAD_NUMBER){

            cv_tp2.wait(tp2_lck);

            tp2_lck.unlock();


            tp2_lck.lock();

            second_pool_thread_number_in_barrier--;

            tp2_lck.unlock();
          }
          else{

            if(second_pool_arrange_index < SECOND_POOL_END_POINT){

              Rearrange_The_Row(second_pool_arrange_index);

              second_pool_arrange_index++;
            }

            cv_tp2.notify_one();

            cv_tp2.wait(tp2_lck);

            tp2_lck.unlock();
         }

     }while(second_pool_arrange_index < SECOND_POOL_END_POINT);


     tp2_lck.lock();

     second_pool_thread_number_in_end++;

     tp2_lck.unlock();


     do {

          if(SECOND_POOL_THREAD_SEARCH_CONDITION){

             cv_tp2.notify_all();
          }

     } while(SECOND_POOL_THREAD_SEARCH_CONDITION);



     if(thread_number == (num_threads -1)){

        second_pool_thread_number_in_barrier = 0;

        second_pool_arrange_index = Second_Pool_Start_Index;
     }



     // -------------------------------------------------------------------------

     common_lck.lock();

     common_barrier_thread_number++;

     if(common_barrier_thread_number < num_threads){

        cv_tp12.wait(common_lck);

        common_lck.unlock();


        common_lck.lock();

        common_barrier_thread_number--;

        common_lck.unlock();
     }
     else{

            common_lck.unlock();

            cv_tp12.notify_all();
     }


     // -------------------------------------------------------------------------


     if(thread_number == (num_threads-1)){

        second_pool_thread_number_in_end = 0;
     }


     do {

       tp2_lck.lock();  // SERIAL EXECUTION BARRIER

       second_pool_thread_number_in_barrier++;

       if(second_pool_thread_number_in_barrier < SECOND_POOL_THREAD_NUMBER){

          cv_tp2.wait(tp2_lck);

          tp2_lck.unlock();


          tp2_lck.lock();

          second_pool_thread_number_in_barrier--;

          tp2_lck.unlock();
        }
        else{

          if(second_pool_arrange_index < SECOND_POOL_END_POINT){

            Rearrange_The_Column(second_pool_arrange_index);

            second_pool_arrange_index++;
          }

          cv_tp2.notify_one();

          cv_tp2.wait(tp2_lck);

          tp2_lck.unlock();
       }

     }while(second_pool_arrange_index < SECOND_POOL_END_POINT);


      tp2_lck.lock();

      second_pool_thread_number_in_end++;

      tp2_lck.unlock();


      do {

          if(SECOND_POOL_THREAD_SEARCH_CONDITION){

             cv_tp2.notify_all();
          }

     } while(SECOND_POOL_THREAD_SEARCH_CONDITION);
 }


 void Construct_Random_Matrix(double *** pointer, int matrix_size){

      *pointer = new double * [5*matrix_size];

      for(int i=0;i<matrix_size;i++){

          (*pointer)[i] = new double [5*matrix_size];

          for(int k=0;k<matrix_size;k++){

              (*pointer)[i][k] = unif(re);
          }
      }
 }

 void Clear_Heap_Memory(double *** pointer, int matrix_size){

      for(int i=0;i<matrix_size;i++){

          delete [] (*pointer)[i];
      }
 }

 void Rearrange_The_Row(int row_number){

      for(int i=0;i<data_matrix_size;i++){

         for(int k=data_matrix_size-1;k>0;k--){

            if(data_matrix[k][row_number] > data_matrix[k-1][row_number]){

               double temp = 0.0;

               temp = data_matrix[k-1][row_number];

               data_matrix[k-1][row_number] = data_matrix[k][row_number];

               data_matrix[k][row_number] = temp;
            }
         }
      }
 }

 void Rearrange_The_Column(int column_number){

      for(int i=0;i<data_matrix_size;i++){

         for(int k=0;k<data_matrix_size;k++){

            if(data_matrix[column_number][k] < data_matrix[column_number][k+1]){

               double temp = 0.0;

               temp = data_matrix[column_number][k+1];

               data_matrix[column_number][k+1] = data_matrix[column_number][k];

               data_matrix[column_number][k] = temp;
            }
         }
      }
 }

void Print_Column(int column_number){

  for(int k=0;k<data_matrix_size;k++){

      std::cout << data_matrix[column_number][k] << " ";
  }
}

void Print_Data(){

     std::cout << "\n\n";

     for(int i=0;i<data_matrix_size;i++){

         std::cout << "\n";

         for(int k=0;k<data_matrix_size;k++){

             std::cout << std::setw(10) << data_matrix[k][i];
         }
     }

     std::cout << "\n\n";
}