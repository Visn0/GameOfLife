#include <iostream>
#include <fstream> //ofstream
#include <stdlib.h> //rand
#include <time.h>
#include <string>
#include <ctime>
#include <omp.h>
#include <vector>

using namespace std;

//return time to create the matrix
void createFile(string filename, bool** matrix, int N) 
{
   ofstream file;
   file.open(filename);
   file << N << "\n";

   for(int r=0; r<N; r++){   
      for(int c=0; c<N; c++){   
         file << matrix[r][c] << " ";
      }
      file << "\n";
   }
   file.close();
}

bool** create_world(int &N){
   
   int NN = N*N;   

   bool** matrix = (bool**)malloc(sizeof(bool*)*N);
   for(int i = 0; i < N; i++)
      matrix[i] = (bool*)malloc(sizeof(bool)*N);

   int n1=0, n2=0;
   // omp_set_num_threads(4);
   // #pragma omp parallel for shared(matrix) private(n1, n2) schedule(static, 10)
      for(n1=0; n1<N; n1++)
      {   
         for(n2=0; n2<N; n2++)
         {   
            //matrix[n1][n2] = rand() % 2; // 0 or 1
            matrix[n1][n2] = 1;
         }
      }   
   
   return matrix;
}


int main(int argc, char *argv[]) 
{
   srand(time(NULL));
   
   int N=0, M=0;

   if(argc < 2){
      cout << "Not enough arguments" << endl;
      cout << "./generador [size world] [num of worlds]" << endl;
   }
   else{
      N = atoi(argv[1]);
      M = atoi(argv[2]);
      cout << N << " " << M << endl;      

      double totalTime, avgTime;
      
      ofstream file;
      file.open("patterns/patterns_report.txt");      
      //vector<bool**> worlds(M);
      double start = clock();
      double* times = (double*)malloc(sizeof(double) * M);

      bool*** worlds = (bool***)malloc(sizeof(bool**) * M);
      for(int i = 0; i < M; i++)
         worlds[i] = (bool**)malloc(sizeof(bool*) * N);

      int i;
      int chunk = N/8;
      int threads = 4;
      
      #pragma omp parallel shared(worlds, chunk, M, N) private(i)
      {
         #pragma omp for schedule(dynamic, chunk) nowait
         for(i = 0; i < M; i++)
         {            
            double start_m = clock();
            worlds[i] = create_world(N);     
            times[i] = ((double)clock() - start) / (CLOCKS_PER_SEC * 1000);
            totalTime += times[i];
         }
      }    
     
      // double end_m = clock();
      // double time = (end_m - start)/CLOCKS_PER_SEC * 1000;
      // cout << "Matrices llenas en: " << time << " ms" << endl;

      int j;
      #pragma omp parallel shared(worlds, chunk, M, N) private(j)
      {
         #pragma omp for schedule(dynamic, chunk) nowait
         for(j=0; j<M; j++){

            string world_name = "patterns/world" + to_string(j) + ".txt";
            createFile(world_name, worlds[j], N);            
         }
      }

      for(int k = 0; k < M; k++)
      {
         file << k << " " << N << " " << N*N << " " << times[k] << endl;      
      }

      double end = clock();            
      avgTime = totalTime/(double)M;

      cout << "Total time: " << totalTime << " ms" << endl;

      file << M << " " << N*N*M << " " << totalTime << " " << avgTime << endl;
      file.close();
   }
}
