#include <iostream>
#include <vector>
#include <fstream> //ifstream
#include <time.h>
#include <string>
#include <ctime>

using namespace std;

using WorldLine = vector<bool>;
using World2D = vector<WorldLine>;
struct Cell {
   int r, c;
};

int g_dir[8][2] = 
{{-1, -1}, {-1, 0}, {-1, 1},
   {0, -1}, {0, 1},
   {1, -1}, {1, 0}, {1, 1}};

template <size_t rows, size_t cols>
void print_world(bool (&world)[rows][cols]){
   for(int r=0; r<rows; r++){
      for(int c=0; c<cols; c++){
         cout << world[r][c] << " ";
      }
      cout << endl;
   }
}

int celulas_vivas(const World2D& world, const int& row, const int& col) {
   int c = 0;
   for (auto dir : g_dir) {
      if( world[ row+dir[0] ][ col+dir[1] ] ) c++;
   }
   return c;
}

double simulate_world(string world_file, int &generations){
   ifstream file(world_file);
   double total = 0;

   if (file.is_open()){
      size_t N = 0; file >> N;
      World2D world;

      //fill the world
      size_t n;
      for(size_t r=0; r<N; r++) {
         WorldLine wl;
         for(size_t c=0; c<N; c++) {
            file >> n;
            wl.push_back(n);
         }
         world.push_back(wl);
      }
      file.close(); // no need to close but OK


      int vivas=0;
      vector<Cell> cells;
      //START THE SIMULATION
      clock_t begin = clock();

      for(int i=0; i<generations; i++){
         //Detect cells that die or born
         for(int r=0; r<N; r++){
            for(int c=0; c<N; c++){
               vivas = celulas_vivas(world, r, c);
               if(!world[r][c]){ //if its dead
                  if(vivas == 3) cells.push_back({r, c}); 
               }else{
                  if(vivas != 2 && vivas != 3) cells.push_back({r, c});
               }
            }
         }
         //Change the cells
         for(Cell cell : cells){
            world[cell.r][cell.c] = !world[cell.r][cell.c];
         }
      }

      //END SIMULATION
      clock_t end = clock();
      total = double(end - begin)*1000 / CLOCKS_PER_SEC;

   }
   else cout << "Unable to open file " + world_file << endl;

   return total;
}


int main(int argc, char *argv[]) {
   string folder = "";
   int generations = 0, M = 0;

   if(argc < 3){
      cout << "Not enough arguments" << endl;
      cout << "./gameoflife [dir folder] [num generations] [num patterns]" << endl;
   }
   else{
      folder = argv[1];
      generations = atoi(argv[2]);
      M = atoi(argv[3]);
      double time=0, totalTime=0, avgTime=0;

      for(int i=0; i<M; i++){
         time = simulate_world(folder+"world"+to_string(i)+".txt", generations);
         totalTime += time;
      }
      avgTime = totalTime/M;      
   }
}
