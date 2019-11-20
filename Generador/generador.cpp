#include <iostream>
#include <fstream> //ofstream
#include <stdlib.h> //rand
#include <time.h>
#include <string>
#include <ctime>
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

   for(n1=0; n1<N; n1++){   
      for(n2=0; n2<N; n2++){   
         matrix[n1][n2] = rand() % 2; // 0 or 1
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
      double totalTime, avgTime=0;

      ofstream file;
      file.open("patterns/patterns_report.txt");
      
      double start = clock();
      vector<bool**> worlds(M);

      int i;      
      for(i = 0; i < M; i++)
      {
         worlds[i] = create_world(N);
      }

      double end_m = clock();
      double time = (end_m-start)/CLOCKS_PER_SEC * 1000;
      cout << "Matrices llenas en: " << time << " ms" << endl;
         
      for(int j=0; j<M; j++){
         string world_name = "patterns/world" + to_string(j) + ".txt";
         createFile(world_name, worlds[j], N);
         file << j << " " << N << " " << N*N << " " << time << endl;      
      }

      double end = clock();
      totalTime = (end - start) / CLOCKS_PER_SEC * 1000; // miliseconds
      avgTime = totalTime/(double)M;
      
      file << M << " " << N*N*M << " " << totalTime << " " << avgTime << endl;
      file.close();
   }
}
