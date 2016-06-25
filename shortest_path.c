#include <stdio.h>

#define N 6

// adjacency matrix
int distance[N][N] = { {0, 7, 9, 0, 0, 14},
                       {7, 0, 10, 15, 0, 0},
                       {9, 10, 0, 11, 0, 2},
                       {0, 15, 11, 0, 6, 0},
                       {0, 0, 0, 6, 0, 9},
                       {14, 0, 2, 0, 9, 0}
};

// record current optimized cost.. set start location cost to 0.
int optimal_cost[N] = {0, 
                       0x7FFFFFFF, 
                       0x7FFFFFFF, 
                       0x7FFFFFFF, 
                       0x7FFFFFFF, 
                       0x7FFFFFFF
                       };

// give the entry index
int find_shortest_path(int idx)
{
    int i, j;

    // do not count 0, it makes no sense to go back to origin
    for (i = 1; i < N; i++)
    {
        // check where there exists a connection
        if (distance[idx][i] && (idx != i))
        {
            // if cost of new path is higher, skip
            if (optimal_cost[i] >= (distance[idx][i] + optimal_cost[idx]))
            {
                // find a cost effective path, replace original optimum value
                optimal_cost[i] = distance[idx][i] + optimal_cost[idx];
                find_shortest_path(i);
            }
        }
    }

    return 0;
}

int main()
{
    int i;
    find_shortest_path(0);
    printf("most effective cost to reach the location from 0: \n\t");
    for (i = 0; i < N; i ++)
    {
        printf("%d ", optimal_cost[i]);
    }
    printf("\n");

    return 0;
}

