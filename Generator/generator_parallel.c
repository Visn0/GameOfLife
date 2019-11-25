#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdlib.h"
#include "omp.h"

static unsigned int g_seed;

inline void fast_srand(int seed)
{
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
inline int fast_rand(void)
{
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

char rng()
{
    return '0' + (fast_rand() % 2);
}

void seed_matrix(char** cells, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
            cells[i][j] = rng();
    }
}

void save_as_file(char* filename, char** cells, unsigned n)
{
    FILE* file = fopen(filename, "w");
    fprintf(file, "%d\n", n);

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
            fprintf(file, "%c ", cells[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(int argc, char** argv)
{
    unsigned n, m;
    if (argc != 3)
    {
        printf("Invalid options.\n");
        printf("Usage: ./generator_parallel N_size num patterns\n");        
        exit(1);
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    fast_srand(time(NULL));

    unsigned i;
    char** pattern;
    FILE* report = fopen("reports/report_parallel.txt", "w");
    fprintf(report, "Num_Pattern Value_N Num_Cells Time \n");
    unsigned num_pattern = 0;
    double total_time = 0;

    #pragma omp parallel for private(i, pattern) shared(report, num_pattern) reduction(+: total_time) schedule(static, 50)
        for (i = 0; i < m; i++)
        {
            double start = omp_get_wtime();
            pattern = (char**) malloc(sizeof(char) * n * n);

            for (unsigned j = 0; j < n; j++)
                pattern[j] = (char*) malloc(sizeof(char) * n);

            seed_matrix(pattern, n);
            double end = omp_get_wtime();
            float total = (end - start) * 1000;
            total_time += total;
            fprintf(report, "%d %d %d %f\n", num_pattern++, n, n*n, total);

            char filename[30];
            sprintf(filename, "patterns/pattern_%d.txt", i);
            save_as_file(filename, pattern, n);

            for (unsigned j = 0; j < n; j++)
                free(pattern[j]);
            free(pattern);
        }

    fprintf(report, "Total_Patterns: %d   Total_Cells: %d, Time_by_pattern: %f", n, n*m*n, total_time / m);
    fclose(report);

    return 0;
}