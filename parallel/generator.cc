#include <omp.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;


class Pattern
{
private:
    bool rng()
    {
        return (rand() % 2);
    }
    unsigned int n;
    bool** cells;
    //time in milliseconds
    long double elapsed_time;
    void init()
    {
        cells = new bool *[n];
        #pragma omp parallel for
        for (unsigned int i = 0; i < n; ++i)
            cells[i] = new bool[n];
        elapsed_time = 0;
    }
public:
    Pattern(unsigned int n)
    {
        clock_t c_start = std::clock();
        this->n = n;
        init();
        #pragma omp parallel for collapse(2)
        for (unsigned int i = 0; i < n; i++)
        {
            for (unsigned int j = 0; j < n; j++)
            {
                cells[i][j] = rng();
            }
        }
        clock_t c_end = std::clock();
        elapsed_time = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;
    }
    long double getTime()
    {
        return elapsed_time;
    }
    ~Pattern();
    void save_as_file(string filename)
    {
        ofstream file = ofstream(filename);
        if (file.is_open())
        {
            file << n << endl;
            for (unsigned i = 0; i < n; i++){
                for (unsigned j = 0; j < n; j++)
                    file << cells[i][j];
                file << endl;
            }
        }
        else {cerr << "ERROR OPENING FILE";}
    }
};

void write_results(Pattern **patterns, unsigned n, unsigned m)
{
    ofstream file = ofstream("patterns_report");
    if (file.is_open())
    {
        file << left  << setw(15) << "Num_Pattern";
        file << left  << setw(15) << "Value_N";
        file << left  << setw(15) << "Num_Cells";
        file << left  << setw(15) << "Time" << endl;
        unsigned total_time = 0;
        for (unsigned i = 0; i < m; i++)
        {
            file << left << setw(15) << i;
            file << left << setw(15) << n;
            file << left << setw(15) << n*n;
            file << left << setw(15) << patterns[i]->getTime() << endl;
            total_time += patterns[i]->getTime();
        }
        file << endl << endl;
        file << left << setw(15) << "Total_Patterns";
        file << left << setw(15) << "Total_Cells";
        file << left << setw(15) << "Total_Time";
        file << left << setw(15) << "Time_By_Pattern" << endl;
        file << left << setw(15) << m;
        file << left << setw(15) << m*n*n;
        file << left << setw(15) << total_time;
        file << left << setw(15) << (double) (total_time/m) << endl;
    }
    else
        cerr << "ERROR_WRITING_FILE" << endl;
}

void read_params(unsigned int& n, unsigned int& m)
{
    cout << "Input N:";
    cin >> n;
    cout << "Input M: ";
    cin >> m;
}

void save_all_patterns(Pattern** patterns, unsigned m)
{
    system("rm patterns/*");
    for (unsigned i = 0; i < m; i++)
    {
        string filename = "patterns/pattern_" + to_string(i); 
        patterns[i]->save_as_file(filename);
    }
}

int main()
{
    srand(time(NULL));
    unsigned int n, m;
    read_params(n, m);
    Pattern** patterns = new Pattern* [m];
    #pragma omp parallel for
    for (unsigned int i = 0; i < m; i++)
        patterns[i] = new Pattern(n);
    write_results(patterns, n, m);
    save_all_patterns(patterns, m);
    delete[] patterns;
    return 0;
}