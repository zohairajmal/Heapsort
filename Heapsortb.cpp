/*
In the first step it also builds a max-heap. 
In the second step, it also proceeds as the Heap Sort does, but
instead of calling MAX-HEAPIFY , it always floats the new root all the way down to a
leaf level. Then, it checks whether that was actually correct and if not fixes the max-heap by
moving the element up again. This strategy makes sense when considering that the element
that was swapped to become the new root is typically small and thus would float down to a
leaf level in most cases. Hence, one would save the additional tests when floating down the
element. And, the fixing step (moving the element upwards again) would be a rare case.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
using namespace std;

void MaxHeapify(int A[], int n, int i);
void heapSort(int A[], int n);
void displayarray(int A[], int n);
void check(int A[],int i);
inline int parent(int i);

int main()
{
    int n=1000;
    int a[n];
    srand(time(NULL));
    for (int j = 0 ; j < n  ; j++) { //Populating a[] by random values
        a[j] = rand() % 10000000;
    }
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(a, n);
    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Heapsortb Variant Case Elapsed time: " << elapsed.count() * (1000) << " ms |"<< " N : "<< n<<endl;
    displayarray(a, n);
}

void MaxHeapify(int A[], int n, int i) //heapify function
{
    int left = 2*i + 1;
    int right = 2*i + 2;
    int max;
    if(right  > n) {
        if(left > n) { //i is leaf node
            return check(A,i);
        }
        else { //left is definitely leaf node
            int temp = A[i];
            A[i] = A[left];
            A[left] = temp;
            return check(A,left);
        }
    }

    if(A[left] < A[right]) {
        max = right;
    }
    else {
        max = left;
    }
    int temp = A[i];
    A[i] = A[max];
    A[max] = temp;
    MaxHeapify(A,n,max);

}

void check(int A[],int i) {
    int par = parent(i);
    while(A[par] < A[i] && par >= 0)
    {
        //Swap A[par] and A[i]
        int temp = A[i];
        A[i] = A[par];
        A[par] = temp;
        //Make sure to "climb" indexes
        i = par;
        par = parent(par);
    }
}

inline int parent(int i) {
    return ceil(i/2.00f)-1;
}

void heapSort(int A[], int n) //heapsort function
{
    int temp; //Creating temp variable so that we can swap later on
    for(int i = floor(n/2.00f) - 1 ; i>=0; i=i-1) //Creating a max heap
        MaxHeapify(A,n,i);
    for(int i=n-1; i>=0; i=i-1)
    {
        temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        MaxHeapify(A,i-1,0); //Recursively calling MaxHeapify function made earlier
    }
}

void displayarray(int A[], int n) //function to display array elements, will be recursively called in main function
{
    for(int i=0; i<n; i++)
        cout << A[i] << ";"; //displaying the array, the semi colons are so that it shows a semi colon after every number that is printed
    cout<<endl;
}