#include <iostream>
#include <sort.h>

using namespace std;

int main(int argc, char *argv[])
{
    unsigned int size;
    cout << "Proszę podać wielkość tablicy: ";
    std::cin >> size;
    while( std::cin.fail() || size<=0 || size>Sort::MAX_ARRAY )
       {
           std::cin.clear();
           cin.ignore( 256 , '\n' );
           std::cout << "Błąd. Proszę podać wielkość tablicy: ";
           std::cin >> size;
       }
    cout << endl;

    Sort mySort(size);
    if(Sort::MAX_ARRAY<=10000)
    {
        mySort.BubbleSort();
        mySort.SelectionSort();
        mySort.InsertSort();
    }
    mySort.QuickSort();
    mySort.CountingSort();
    mySort.HeapSort();
    mySort.MargeSort();

    return 0;
}
