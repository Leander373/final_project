#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nachbar_check(int N, int row, int col, int gitter[N][N]);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Falsche Parameteranzahl, zwei werden benötigt!\n");
        printf("Gittergröße und Anzahl der Zeitschritte\n");
        exit(1);
    }

    int N = atof(argv[1]);
    int M = atof(argv[2]);

    srand(time(NULL));

    int gitter[N][N];

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            gitter[i][j] = rand() % 2;
        }
    }

    /*
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d", gitter[i][j]);
        }
        printf("\n");
    }
    */

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
        // **gitter = temp;

        FILE *file;
        file = fopen("2d_states/2d_state_%04d.txt", "w");

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                fprintf(file, "%d", gitter[i][j]);
                if (j < N - 1)
                fprintf(file, " ");
            }
            fprintf(file, "\n");
        }
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