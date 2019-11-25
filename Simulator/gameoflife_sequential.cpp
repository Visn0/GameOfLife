#include <iostream>
#include <vector>
#include <fstream> //ifstream
#include <time.h>
#include <string>
#include <ctime>
#include <unistd.h>

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

void print_world_beautiful(const World2D &world){
   int size = (int)world.size();
   for(int r=0; r<size; r++){
      for(int c=0; c<size; c++){
         if(world[r][c])
            cout << "# ";
         else
            cout << "· ";
      }
      cout << endl;
   }
}

void print_world(const World2D &world){
   int size = (int)world.size();
   for(int r=0; r<size; r++){
      for(int c=0; c<size; c++){
         cout << world[r][c] << " ";
      }
      cout << endl;
   }
}

int celulas_vivas(const World2D& world, const int& row, const int& col) {
   int c = 0;
   int size = (int) world.size();
   int nr = 0;
   int nc = 0;

   for (auto dir : g_dir) {      
      nr = row + dir[0];
      nc = col + dir[1];

      if(nr >= size) 
         nr = nr % size;
      else if (nr < 0) 
         nr = nr + size;

      if(nc >= size) 
         nc = nc % size;
      else if (nc < 0) 
         nc = nc + size;

      if(world[nr][nc]) c++;
   }
   return c;
}

World2D readFile(string world_file)
{
   ifstream file(world_file);
   World2D world;

   if (file.is_open())
   {
      int N = 0; file >> N;      

      //fill the world
      int n = 0;
      for(int r=0; r<N; r++) 
      {
         WorldLine wl;
         for(int c=0; c<N; c++) 
         {
            file >> n;
            wl.push_back(n);
         }

         world.push_back(wl);
      }

      file.close();
   }
   else //cout << "Unable to open file: " + world_file << endl;

   return world;
}

double simulate_world(World2D world, int &generations)
{   
   double total = 0;
   
   int vivas=0;
   int N = world.size();

   vector<Cell> cells;
   
   //START THE SIMULATION
   clock_t begin = clock();

   // //cout << "Generación: 0" << endl;   
   // print_world_beautiful(world);
   // //cout << endl;

   for(int i=0; i<generations; i++)
   {
      //Detect cells that die or born
      for(int r=0; r<N; r++)
      {
         for(int c=0; c<N; c++)
         {
            vivas = celulas_vivas(world, r, c);
            if(!world[r][c])
            { //if its dead
               if(vivas == 3) cells.push_back({r, c}); 
            }
            else
            {
               if(vivas != 2 && vivas != 3) cells.push_back({r, c});
            }
         }
      }
      //Change the cells
      for(Cell cell : cells)      
         world[cell.r][cell.c] = !world[cell.r][cell.c];
      
      cells.clear();       

      // usleep(200000);
      // system("clear");
      
      // //cout << "Generación: " << i+1 << endl;
      // //print_world(world);
      // print_world_beautiful(world);
      //cout << endl;        
      
   }

   //END SIMULATION
   clock_t end = clock();
   total = double(end - begin)*1000 / CLOCKS_PER_SEC;   

   return total;
}


int main(int argc, char *argv[]) 
{   
   string folder = "";
   int generations = 0, M = 0;

   if(argc < 3)
   {
      //cout << "Not enough arguments" << endl;
      //cout << "./gameoflife [dir folder] [num generations] [num patterns]" << endl;
   }
   else
   {
      folder = argv[1];
      generations = atoi(argv[2]);
      M = atoi(argv[3]);
      double time=0, totalTime=0, avgTime=0;

      World2D *worlds = (World2D*)malloc(sizeof(World2D)*M);

      for(int i=0; i<M; i++)               
         worlds[i] = readFile(folder+"world"+to_string(i));
      

      for(int i=0; i<M; i++)
      {
         ////cout << "World: " << i << endl;
         time = simulate_world(worlds[i], generations);         
         totalTime += time;
      }

      avgTime = totalTime/M;      
      //cout << "AvgTime: " << avgTime << endl;
   }
}
