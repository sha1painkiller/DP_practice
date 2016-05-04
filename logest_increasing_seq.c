// Find the longest increasing sequence
#include <stdio.h>
#include <stdlib.h>

int longest_increasing_seq_ptr(int *seq, int *size, int *output)
{
  int i, j, k, pivot;
  int arr_size = *size;

  // a structure to keep the integer numbers and its length
  typedef struct LIS {
    int *s;
    int len;
  } LIS;
  LIS *L;

  // allocate the whole array space
  L = (LIS *)malloc(arr_size * sizeof(LIS));

  // walk through tuples and allocate buffers
  for (i = 0; i < arr_size; i++)
    L[i].s = (int *)malloc(arr_size * sizeof(int));

  int max_len = 0;
  int result_idx = 0;
  int last_idx;

  printf("input size: %d\n", arr_size); printf("seq: "); for (i = 0; i < arr_size; i++) printf("%d ", seq[i]); printf("\n");

  // assign the first value to evaluation array (no need to compare)
  L[0].s[0] = seq[0]; L[0].len = 1;
  printf("L[0]: %d\n", seq[0]);

  // begin tuple comparison
  for (i = 1; i < arr_size; i++)
  {
    pivot = seq[i];
    L[i].len = 1;
    L[i].s[0] = pivot;
    // compare current pivot value with previous tuples
    // find the longest existing path, which last value is less than pivot
    for (j = 0; j < i; j++)
    {
      int plen = L[j].len;
      if ((L[i].len <= L[j].len) && (pivot > L[j].s[plen-1]))
      {
        // hit!! refresh current sequence with current best fit
        // maybe just memcpy the whole LIS struct? (would be clearer expressed)
        for (k = 0; k < L[j].len; k++)
          L[i].s[k] = L[j].s[k];
        last_idx = L[i].len = L[j].len;
        // add pivot to the last component. len++
        L[i].s[last_idx] = pivot;
        L[i].len++;
      }
    }
    // enumerate each tuple for debug(observation)
    printf("L[%d]: ", i); for (k = 0; k < L[i].len; k++) printf("%d ", L[i].s[k]); printf("\n");
  }

  // find the longest sequence (biggest length)
  for (i = 1; i < arr_size; i++)
  {
    if ( L[i].len >= max_len )
    {
      max_len = L[i].len;
      result_idx = i;
    }
  }

  // write back to the result space
  for ( i = 0; i < max_len; i++)
    output[i] = L[result_idx].s[i];
  // indicate the result length
  *size =  L[result_idx].len;

  // free allocated memories
  for (i = 0; i < arr_size; i++)
    free(L[i].s);   
  free(L);  

  return 0;
}

int main(int argc, char* argv[])
{

  int input[] = {3, 2, 6, 4, 5, 1, 6, 12, 4, 15, 9, 10};
  //int input[] = {2, 3};
  int arr_size = sizeof(input) / sizeof(int);
  int *out_result = malloc(sizeof(input));
  int i = 0;
  int result;

  result = longest_increasing_seq_ptr(input, &arr_size, out_result);

  printf("longest inc seq is (%d): \n", arr_size);
  for (i = 0; i < arr_size; i ++)
  {
    printf("%d ", out_result[i]);
  }
  printf("\n");
  free(out_result);

  return 0;
}
