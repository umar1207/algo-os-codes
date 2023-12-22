#include <bits/stdc++.h>
using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int partition(int arr[], int p, int r)
{
    int x = arr[p];
    int i = p-1;
    int j = r+1;
    
    while(true)
    {
        do{j--;} while(arr[j] > x);
        do{i++;} while(arr[i] < x);
        if(i < j) swap(arr[i], arr[j]);
        else return j;
    }
}

int randomPartitioning(int arr[], int p, int r)
{
    srand(time(NULL));
    int pivot = p + rand()%(r-p+1);

    cout << "\nPivot \nIndex = " << pivot << "\n";
    cout << "Number = " << arr[pivot] << endl;

    swap(arr[pivot], arr[p]);
    
    return partition(arr, p, r);
}

void quickSort(int arr[], int p, int r, int n)
{
    if(p < r)
    {
        int q = randomPartitioning(arr, p, r);

        cout << "\np = " << p << "\tr = " << r << endl; 
        cout << "Hoare index: " << q << endl;

        cout << "Intermediate array: ";
        for(int i=0; i<n; i++) cout << arr[i] << " ";
        cout << endl;

        quickSort(arr, p, q, n);
        quickSort(arr, q+1, r, n);
    }
}

int main()
{
    cout <<"Enter the number of elements: ";
    int n; cin >> n;

    cout << "Enter " << n << " elements of the array: ";
    int arr[n];

    for(int i=0; i<n; i++) cin >> arr[i];

    quickSort(arr, 0, n-1, n);
    cout << "\nSorted array is: ";

    for(int i=0; i<n; i++) cout << arr[i] << " ";

    return 0;
}