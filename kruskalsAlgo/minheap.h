// A class for Min Heap
#include<iostream>
using namespace std;

class MinHeap{
    int *heap_array; // pointer to array of elements in heap
    int *src; // pointer to array of source vertices
    int *dest; // pointer to array of destination vertices
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap

public:
    // Constructor: Initialise a capacity and heap_array;
    MinHeap(int capacity){
        this->heap_size = 0;
        this->capacity = capacity;
        this->heap_array = new int[capacity];
        this->src = new int[capacity];
        this->dest = new int[capacity];
    }

    // method to heapify a subtree with the root at given index i

    // method to get index of parent of node at index i
    int parent(int i){ return (i-1)/2; }

    // method to get index of left child of node at index i
    int left(int i){ return (2*i + 1); }

    // method to get index of right child of node at index i
    int right(int i){ return (2*i + 2); }

    void MinHeapify(int i){
        /* A recursive method to heapify 'heap_array' */
        int l = left(i);
        int r = right(i);

        int smallest = i;

        if (l < heap_size && heap_array[l] < heap_array[i])
            smallest = l;
        if (r < heap_size && heap_array[r] < heap_array[smallest])
            smallest = r;
        if (smallest != i){
            swap(heap_array[i], heap_array[smallest]);
            swap(src[i], src[smallest]);
            swap(dest[i], dest[smallest]);
            MinHeapify(smallest);
        }
    }

    // method to remove minimum element (or root) from min heap
    int DeleteMin(){
        if (heap_size <= 0)
            return INT_MAX;
        if (heap_size == 1){
            heap_size--;
            return heap_array[0];
        }

        // remove the minimum value from the heap.
        int root = heap_array[0];
        heap_array[0] = heap_array[heap_size-1];
        src[0] = src[heap_size-1];
        dest[0] = dest[heap_size-1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    int getMin(){ return heap_array[0]; }
    int getsrc(){ return src[0]; }
    int getdest(){ return dest[0]; }
    int getSize(){ return heap_size; }

    // method to inserts a new key 'k'
    void insertKey(int k, int s, int d){
        if (heap_size == capacity){
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        // Inserting the new key at the end
        int i = heap_size;
        heap_array[heap_size++] = k;
        src[i] = s;
        dest[i] = d;

        while (i != 0 && heap_array[parent(i)] > heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            swap(src[i], src[parent(i)]);
            swap(dest[i], dest[parent(i)]);
            i = parent(i);
        }
    }
};