#include "sort.h"

Sort::Sort(unsigned int _iSize) : iSize(_iSize)
{
    pSourceArray = new int[_iSize];
    pom = new int[iSize];
    GenerateArray();
    pSourceArray_CONST = new int[_iSize];
    std::copy(pSourceArray, pSourceArray+iSize, pSourceArray_CONST);
    DisplayArray("Początkowe");
}

Sort::~Sort()
{
    delete [] pom;
    delete [] pSourceArray;
    delete [] pSourceArray_CONST;
}

void Sort::DisplayArray(std::string _strType, clock_t _t)
{
    std::cout<<"Sortowanie "<<_strType<<std::endl;    
    if(_t)
        std::cout << std::fixed << std::setprecision(10) <<"CPU time used: "
                  << 1000.0 * _t/ CLOCKS_PER_SEC << " ms\n"<<std::endl;

    for(int i = 0 ; i < iSize ; i++)
        //std::cout<<"Tablica ["<<i<<"]= "<<pSourceArray[i]<<std::endl;
        std::cout<< pSourceArray[i] <<",";
    std::cout<<std::endl<<std::endl;
}

void Sort::GenerateArray()
{
    srand (time(NULL));
    for(int i = 0 ; i < iSize ; i++)
        pSourceArray[i] = rand() % 99 + 1;
}

void Sort::BubbleSort()
{
    /* start clock */
    std::clock_t c_start = std::clock();

    /* bubble algorythim */
    int flag,temp;
    do
    {
        flag=0;
        for( int i = (iSize-1) ; i > 0 ; --i )
        {
            if( pSourceArray[i] < pSourceArray[i-1])
            {
                /* swap elements */
                temp = pSourceArray[i];
                pSourceArray[i] = pSourceArray[i-1];
                pSourceArray[i-1] = temp;
                flag=1;
            }
        }
    }
    while( flag != 0);

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("Bąbelkowe",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

void Sort::SelectionSort()
{
    /* start clock */
    std::clock_t c_start = std::clock();

    /* selection sort algorythim */
    int min,temp;
    for(int i = 0 ; i < iSize ; ++i)
    {
        min=i;
        for(int j = i+1 ; j < iSize ; ++j)
            if(pSourceArray[j]<pSourceArray[min]) min=j; // find minimum

        /* swap */
        temp = pSourceArray[min];
        pSourceArray[min] = pSourceArray[i];
        pSourceArray[i] = temp;
    }

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("przez zamianę",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

/* for QuickSort() */
void Sort::quicksort(int *array, int left, int right)
{
    int i=left;
    int j=right;
    int pivot;
    int swap;

    pivot = array[(i+j)/2];

    while(i<=j)
    {
        while(*(array+i) < pivot) i++;
        while(*(array+j) > pivot) j--;

        if(i<=j)
        {
            swap = *(array+i);
            array[i] = *(array + j);
            array[j] = swap;
            i++;
            j--;

        }
    }
    if(left<j)  quicksort(array,left,j);
    if(i<right) quicksort(array,i,right);

}

void Sort::QuickSort()
{
    /* start clock */
    std::clock_t c_start = std::clock();

    quicksort(pSourceArray,0,iSize-1);

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("Quick",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

void Sort::InsertSort()
{
    /* start clock */
    std::clock_t c_start = std::clock();

    /* insert sort algorythim */
    int temp, j;
    for( int i = 1; i < iSize; ++i )
    {
        temp = pSourceArray[ i ];

        for( j = i - 1; j >= 0 && pSourceArray[ j ] > temp; j-- )
        {
            pSourceArray[ j + 1 ] = pSourceArray[ j ];
        }
        pSourceArray[ j + 1] = temp;
    }

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("Insert",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

/* for CountingSort() */
void Sort::findminmax(int *array, int size, int &max, int &min)
{
    max=0,min=MAX_ARRAY+1;
    for(int i = 0 ; i < size ; i++)
    {
        if(array[i]>max) max = array[i];
        if(array[i]<min) min = array[i];
    }
}

void Sort::CountingSort()
{
    /* start clock */

    std::clock_t c_start = std::clock();
    int i,max,min,z=0;
    findminmax(pSourceArray,iSize,max,min);

    int nlen = (max-min)+1;
    int * helpArray = new int[nlen];

    for(i = 0 ; i < nlen ; ++i) helpArray[i]=0;
    for(i = 0 ; i < iSize ; ++i) helpArray[pSourceArray[i]-min]++;

    for(i = 0 ; i <=(max-min) ; i++)
    {
        while(helpArray[i]!=0)
        {
            pSourceArray[z++]= i + min;
            helpArray[i]--;
        }
    }

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("Counting",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

/* for HeapSort() */
void Sort::shiftRight(int* array, int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;

        /*Check if root is less than left child*/
        if (array[swapIdx] < array[leftChild])
        {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (array[swapIdx] < array[rightChild]))
        {
            swapIdx = rightChild;
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            int tmp = array[root];
            array[root] = array[swapIdx];
            array[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;

        }
        else
        {
            break;
        }

    }
}

/* for HeapSort() */
void Sort::heapify(int* array, int low, int high)
{
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int midIdx = (high - low -1)/2;
    while (midIdx >= 0)
    {
        shiftRight(array, midIdx, high);
        --midIdx;
    }
}

void Sort::HeapSort()
{
    /* start clock */
    std::clock_t c_start = std::clock();

    assert(pSourceArray);
    assert(iSize > 0);
    /*This will put max element in the index 0*/
    heapify(pSourceArray, 0, iSize-1);
    int high = iSize - 1;
    while (high > 0)
    {
        /*Swap max element with high index in the array*/
        int tmp = pSourceArray[high];
        pSourceArray[high] = pSourceArray[0];
        pSourceArray[0] = tmp;
        --high;
        /*Ensure heap property on remaining elements*/
        shiftRight(pSourceArray, 0, high);
    }

    /* stop clock */
    std::clock_t c_end = std::clock();
    DisplayArray("Heap",(c_end-c_start));
    std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}

/* for MargeSort() */
void Sort::Marge(int * array, int left, int middle, int right)
{

  int i, j;

  /* Save left part of subarray in helpArray */
  for(i = middle + 1; i>left; i--)
    pom[i-1] = array[i-1];

  /* Save right part of subarray in helpArray */
  for(j = middle; j<right; j++)
    pom[right+middle-j] = array[j+1];

  /* marge two subarrays and save in good one */
  for(int k=left;k<=right;k++)
    if(pom[j]<pom[i])
      array[k] = pom[j--];
    else
      array[k] = pom[i++];
}

/* for MargeSort() */
void Sort::margesort(int * array, int left, int right)
{
  /* only one element */
  if(right<=left)
        return;

  /* middle of subarray */
  int middle = (right+left)/2;

  margesort(array, left, middle);
  margesort(array, middle+1, right);

  /* marge two sorted arrays */
  Marge(array, left, middle, right);
}

void Sort::MargeSort()
{
  /* start clock */
  std::clock_t c_start = std::clock();

  margesort(pSourceArray, 0, iSize-1);

  /* stop clock */
  std::clock_t c_end = std::clock();
  DisplayArray("Marge",(c_end-c_start));
  std::copy(pSourceArray_CONST, pSourceArray_CONST+iSize, pSourceArray);
}
