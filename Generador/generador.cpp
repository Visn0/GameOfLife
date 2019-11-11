#include <iostream>
#include <fstream> //ofstream
#include <stdlib.h> //rand
#include <time.h>
#include <string>
#include <ctime>

using namespace std;

//return time to create the matrix
double create_world(int &N, int &count){
   ofstream file;
   int NN = N*N;

   //-------------------------------------------
   clock_t begin = clock();
   bool matrix[N][N];
   srand(time(NULL));

   for(int n1=0; n1<N; n1++){   
      for(int n2=0; n2<N; n2++){   
         matrix[n1][n2] = rand() % 2; // 0 or 1
      }
   }
   clock_t end = clock();
   double total = double(end - begin)*1000 / CLOCKS_PER_SEC;
   //-------------------------------------------

   file.open("patterns/world" + to_string(count) + ".txt");
   file << N << "\n";

   for(int r=0; r<N; r++){   
      for(int c=0; c<N; c++){   
         file << matrix[r][c] << " ";
      }
      file << "\n";
   }
   file.close();
   return total;
}


int main(int argc, char *argv[]) {
   int N=0, M=0;

   if(argc < 2){
      cout << "Not enough arguments" << endl;
      cout << "./generador [size world] [num of worlds]" << endl;
   }
   else{
      N = atoi(argv[1]);
      M = atoi(argv[2]);
      cout << N << " " << M << endl;
      double time=0, totalTime=0, avgTime=0;

      ofstream file;
      file.open("patterns/patterns_report.txt");
      
      for(int i=0; i<M; i++){
         time = create_world(N, i);
         totalTime += time;
         file << i << " " << N << " " << N*N << " " << time << endl;
      }
      avgTime = totalTime/M;
      file << M << " " << N*N*M << " " << totalTime << " " << avgTime << endl;
      file.close();
   }
}
