#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the size of reference string: ";
    int size; cin >> size;

    int arr[size];
    cout << "Enter the reference string: ";
    for(int i=0; i<size; i++) cin >> arr[i];

    cout << "Enter the number of frame pages: ";
    int frames; cin >> frames;

    int fault[size];
    for(int i=0; i<size; i++) fault[i] = -1;

    /////////////// FIFO ///////////////

    int ptr = 0;

    int matrix[frames][size];

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<frames; j++) 
            matrix[j][i] = -1;
    }


    for(int i=0; i<size; i++)
    {
        int fl1 = 1;
        int fl2 = 1;

        if(i != 0)
        {
            for(int j=0; j<frames; j++) 
                matrix[j][i] = matrix[j][i-1];
        }

        for(int j=0; j<frames; j++)
        {
            if(i==0)
            {
                fl1 = 0;
                matrix[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(matrix[j][i-1] == -1)
            {
                fl1 = 0;
                matrix[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(arr[i] == matrix[j][i-1])
            {
                fl2 = 0;
                matrix[j][i] = arr[i];
                fault[i] = 0;
                break;
            }
        }
        if(fl1==1 && fl2==1)
        {
            fault[i] = 1;
            matrix[ptr][i] = arr[i];
            ptr = (ptr+1)%frames;
        }
    }

    for(int i=0; i<size; i++) cout << arr[i] << " ";
    cout << endl;

    for(int i=0; i<frames; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(matrix[i][j] != -1) cout << matrix[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }

    // /////////////// OPT ///////////////

    int opt[frames][size];
    for(int i=0; i<size; i++) fault[i] = -1;

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<frames; j++) 
            opt[j][i] = -1;
    }

    for(int i=0; i<size; i++)
    {
        int fl1 = 1;
        int fl2 = 1;

        if(i != 0)
        {
            for(int j=0; j<frames; j++) 
                opt[j][i] = opt[j][i-1];
        }
        for(int j=0; j<frames; j++)
        {
            if(i==0) // for the first page
            {
                fl1 = 0;
                opt[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(opt[j][i-1] == -1) // if empty slot is there
            {
                fl1 = 0;
                opt[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(arr[i] == opt[j][i-1]) // if page is already there
            {
                fl2 = 0;
                opt[j][i] = arr[i];
                fault[i] = 0;
                break;
            }
        }
        if(fl1==1 && fl2==1)
        {
            int temp[frames];
            for(int j=0; j<frames; j++) temp[j] = INT_MAX;
            for(int j=0; j<frames; j++)
            {
                int page = opt[j][i];
                for(int z=i+1; z<size; z++)
                {
                    if(arr[z] == page)
                    {
                        temp[j] = z;
                        break;
                    }
                }
            }
            // find the max element in temp and replace that index with incoming page number
            int maxE = INT_MIN;
            int maxid = 0;
            for(int j=0; j<frames; j++)
            {
                if(temp[j] > maxE){
                    maxE = temp[j];
                    maxid = j;
                }
            }
            
            opt[maxid][i] = arr[i];
        }
    }


    for(int i=0; i<size; i++) cout << arr[i] << " ";
    cout << endl;

    for(int i=0; i<frames; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(opt[i][j] != -1) cout << opt[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }


    ///////////// LRU ///////////////

    int lru[frames][size];
    for(int i=0; i<size; i++) fault[i] = -1;

    for(int i=0; i<size; i++)
    {
        for(int j=0; j<frames; j++) 
            lru[j][i] = -1;
    }

    for(int i=0; i<size; i++)
    {
        int fl1 = 1;
        int fl2 = 1;

        if(i != 0)
        {
            for(int j=0; j<frames; j++) 
                lru[j][i] = lru[j][i-1];
        }
        for(int j=0; j<frames; j++)
        {
            if(i==0) // for the first page
            {
                fl1 = 0;
                lru[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(lru[j][i-1] == -1) // if empty slot is there
            {
                fl1 = 0;
                lru[j][i] = arr[i];
                fault[i] = 1;
                break;
            }
            if(arr[i] == lru[j][i-1]) // if page is already there
            {
                fl2 = 0;
                lru[j][i] = arr[i];
                fault[i] = 0;
                break;
            }
        }
        if(fl1==1 && fl2==1)
        {
            int temp[frames];
            for(int j=0; j<frames; j++)
            {
                int page = lru[j][i];
                for(int z=i-1; z>=0; z--)
                {
                    if(arr[z] == page)
                    {
                        temp[j] = z;
                        break;
                    }
                }
            }
            // find the max element in temp and replace that index with incoming page number
            int minE = INT_MAX;
            int minId = 0;
            for(int j=0; j<frames; j++)
            {
                if(temp[j] < minE){
                    minE = temp[j];
                    minId = j;
                }
            }
            lru[minId][i] = arr[i];
        }
    }


    for(int i=0; i<size; i++) cout << arr[i] << " ";
    cout << endl;

    for(int i=0; i<frames; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(lru[i][j] != -1) cout << lru[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }

}