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

int main()
{
    unsigned n = 500;
    unsigned m = 500;
    fast_srand(time(NULL));
    unsigned i;
    char** pattern;
    // #pragma omp parallel for private(i, pattern) schedule(static, 50) num_threads(4)
    for (i = 0; i < m; i++)
    {
        pattern = (char**) malloc(sizeof(char) * n * n);
        for (unsigned j = 0; j < n; j++)
            pattern[j] = (char*) malloc(sizeof(char) * n);
        seed_matrix(pattern, n);
        char filename[20];
        sprintf(filename, "patterns/pattern_%d", i);
        save_as_file(filename, pattern, n);
        for (unsigned j = 0; j < n; j++)
            free(pattern[j]);
        free(pattern);
    }
    return 0;
}