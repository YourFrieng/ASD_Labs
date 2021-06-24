#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

size_t change_count = 0;
size_t compare_count = 0;


template<class type>
void bubble_sort(type* container, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            ++compare_count;
            if (container[j] > container[j + 1]) {
                
                // меняем элементы местами
                type temp = container[j];
                container[j] = container[j + 1];
                container[j + 1] = temp;
                ++change_count;
            }
        }
    }
}



template<class type>
void quick_sort(type* container, const int& left, const int& right) {

    int i = left;
    int j = right;
    int pivot = container[(left + right) / 2];


    do {
        ++compare_count;
        while (container[i] < pivot) { ++compare_count; i++; }
        ++compare_count;
        while (container[j] > pivot) { ++compare_count; j--; }
        ++compare_count;
        ++compare_count;
        if (i <= j) {
            type temp = container[i];
            container[i] = container[j];
            container[j] = temp;
            ++change_count;
            i++; j--;
        }
    } while (i <= j);
    ++compare_count;
    if (left < j) { quick_sort(container, left, j); }
    ++compare_count;
    if (i < right) { quick_sort(container, i, right); }
}





int main()
{
    srand(time(0));
    int size;

    std::cin >> size;

    size = size <= 0 ? 1 : size;
    int* arr = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % 1512 + 1;
    }
    //std::vector<int> arr(size);

    //for presentation

    std::cout << "\nInput massive: ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl << std::endl;

    clock_t start = clock();
#if 1
    bubble_sort(arr, size);
    //bubble_sort(arr, size);
#endif
#if 0
    //quick_sort(arr, size, size, 0);
    quick_sort(arr, 0, size - 1);

#endif 
    clock_t end = clock();
    std::cout << std::endl;


    std::cout << "Sorted massive: ";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Compare count: " << compare_count << std::endl;
    std::cout << "Change count(algorithmic): " << change_count << std::endl;
    std::cout << "Change count(factually): " << 3 * change_count << std::endl;
    std::cout << "Time: " << (double)(end - start) / (CLOCKS_PER_SEC / 1000) << std::endl;
    
    return 0;
}
