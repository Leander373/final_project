#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nachbar_check(int N, int row, int col, int gitter[N][N]);

int main()
{
    int N = 200;
    int M = 200;

    int gitter[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            gitter[i][j] = 0;
        }
    }

    int raumschiff[4][5] = {
        {0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 0}};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            gitter[i + 98][j + 150] = raumschiff[i][j];
        }
    }

    for (int t = 0; t < M; t++)
    {
        int temp[N][N];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gitter[i][j] == 1)
                {
                    if (nachbar_check(N, i, j, gitter) < 2)
                    {
                        temp[i][j] = 0;
                    }
                    else if (nachbar_check(N, i, j, gitter) > 3)
                    {
                        temp[i][j] = 0;
                    }
                    else
                    {
                        temp[i][j] = 1;
                    }
                }
                else
                {
                    if (nachbar_check(N, i, j, gitter) == 3)
                    {
                        temp[i][j] = 1;
                    }
                    else
                    {
                        temp[i][j] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                gitter[i][j] = temp[i][j];
            }
        }

        FILE *file;

        char filename[50];
        snprintf(filename, sizeof(filename), "2d_states/2d_state_%04d.txt", t + 1);

        file = fopen(filename, "w");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(file, "%d ", gitter[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }

    return 0;
}

int nachbar_check(int N, int row, int col, int gitter[N][N])
{
    int one_counter = 0;

    for (int i = row - 1; i < row + 2; i += 2)
    {
        for (int j = col - 1; j < col + 2; j++)
        {
            if (i > -1 && i < N && j > -1 && j < N)
            {
                if (gitter[i][j] == 1)
                {
                    one_counter++;
                }
            }
        }
    }

    for (int j = col - 1; j < col + 2; j += 2)
    {
        if (j > -1 && j < N)
        {
            if (gitter[row][j] == 1)
            {
                one_counter++;
            }
        }
    }

    return one_counter;
}