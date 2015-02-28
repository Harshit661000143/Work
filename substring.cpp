#include<stdio.h>
#include<string.h>
#include<iostream> 
int findLength(char *str)
{
    int n = strlen(str);
    int maxlen =0;  // Initialize result
 
    // Choose starting point of every substring
    for (int i=0; i<n; i++)
    {
        // Choose ending point of even length substring
        for (int j =i+1; j<n; j += 2)
        {
            int length = j-i+1;//Find length of current substr
 
            // Calculate left & right sums for current substr
            int leftsum = 0, rightsum =0;
            for (int k =0; k<length/2; k++)
            {
                leftsum  += (str[i+k]);
                rightsum += (str[i+k+length/2]);
            }
 
            // Update result if needed
            if (leftsum == rightsum && maxlen < length)
                    maxlen = length;
        }
    }
    return maxlen;
}
 
// Driver program to test above function
int main(void)
{
    char str[] = "1538023";
    int n = strlen(str);
    printf("Length of the substring is %d\n", n);
    printf("Length of the substring is %d\n", findLength(str));
    return 0;
}

