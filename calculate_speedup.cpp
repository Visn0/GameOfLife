#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

void writeSpeedUp(string folder, vector<vector<float>> data_parallel, vector<float> data_sequential)
{     
    for(int i = 0; i < data_parallel.size(); i++)
    {   
        ofstream speedup;
        speedup.open(folder + "/speedup." + to_string(i+1) + ".thread");

        if(speedup.is_open())
        {
            for(int j = 0; j < data_sequential.size(); j++)
            {
                float value = (data_parallel[i][j] == 0) ? 0 : data_sequential[j] / data_parallel[i][j];
                speedup << 50*(j+1) << " " << value << endl;
            }
            
            speedup.close();
        }
    }
}

vector<float> readFile(string filename)
{
    ifstream file;
    file.open(filename);

    vector<float> data;

    if(file.is_open() || true)
    {                
        string s;
        while(file >> s && file >> s)
        {            
            data.push_back(stof(s));  
        }

        file.close();
    }

    return data;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Invalid options." << endl;
        cout << "Usage: ./calculate_speedup folder_times num_threads" << endl << endl;
        exit(1);
    }
    string folder = argv[1];
    int threads = atoi(argv[2]);
    
    vector<float> data_sequential = readFile(folder+"/sequential.time");
    vector<vector<float>> data_parallel;

    for(int i = 0; i < threads; i++)
    {
        string filename = folder + "/parallel." + to_string(i+1) + ".thread.time";       

        vector<float> data = readFile(filename);
        
        data_parallel.push_back(data);
    }

    writeSpeedUp(folder, data_parallel, data_sequential);

    return 0;
}