#include <chrono>
#include <iostream>
#include <random>
#include <array>

int const size = 1000;
unsigned main_array[size];
unsigned forward_array[size];
unsigned backward_array[size];
unsigned arr[size];


bool IsArraySorted(unsigned arr[], int const begin_idx, int const end_idx)
{
    for (int i = begin_idx; i < end_idx - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

void forward_step(unsigned arr[], int const begin_idx, int const end_idx)
{
    for (int i = begin_idx; i < end_idx; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            std::swap(arr[i], arr[i + 1]);
        }
    }
}

void backward_step(unsigned arr[], int const begin_idx, int const end_idx)
{
    for (int i = end_idx; i > begin_idx; --i)
    {
        if (arr[i] < arr[i - 1])
        {
            std::swap(arr[i], arr[i - 1]);
        }
    }
}

void shaker_sort(unsigned arr[], int const begin_idx, int const end_idx)
{
    unsigned left = begin_idx;
    unsigned right = end_idx - 1;

    while (true)
    {

        forward_step(arr, left, right);

        if (IsArraySorted(arr, left, right))
        {
            break;
        }

        --right;

        backward_step(arr, left, right);

        if (IsArraySorted(arr, left, right))
        {
            break;
        }

        ++left;
    }
}

bool IsForwardWork(unsigned arr[], int const begin_idx, int const end_idx)
{
    unsigned tmp[size];

    for (int i = 0; i < size; ++i)
    {
        tmp[i] = arr[i];
    }

    forward_step(arr, begin_idx, end_idx);

    for (int j = 0; j < size; ++j)
    {
        if (tmp[j] != arr[j])
        {
            return true;
        }
    }
    return false;
}

bool IsBackwardWork(unsigned arr[], int const begin_idx, int const end_idx)
{
    unsigned tmp[size];

    for (int i = 0; i < size; ++i)
    {
        tmp[i] = arr[i];
    }

    backward_step(arr, begin_idx, end_idx);

    for (int j = size - 1; j >= 0; --j)
    {
        if (tmp[j] != arr[j])
        {
            return true;
        }
    }
    return false;
}

int main()
{
    for (int j = 0; j < size; j++)
    {
        arr[j] = j;
    }
    unsigned seed = 2;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(0, size);


    for (int s = 0; s < size; s++)
    {
        main_array[s] = arr[dstr(rng)];
        forward_array[s] = arr[dstr(rng)];
        backward_array[s] = arr[dstr(rng)];

    }
    std::cout << "Shaker sort:" << std::endl;
    shaker_sort(main_array, 0, size);
    std::cout << IsArraySorted(main_array, 0, size) << std::endl; // 1 means 'sorted', 0 means 'not sorted'

    std::cout << "Forward step:" << std::endl;
    forward_step(forward_array, 0, size);
    std::cout << IsForwardWork(forward_array, 0, size) << std::endl; // 1 means 'work', 0 means 'does not work'

    std::cout << "Backward step:" << std::endl;
    backward_step(backward_array, 0, size);
    std::cout << IsBackwardWork(backward_array, 0, size) << std::endl; // 1 means 'work', 0 means 'does not work'

    return 0;
}