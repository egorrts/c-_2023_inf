#include <iostream>
#include <chrono>
#include <random>
#include <math.h>

int const size = 100000;
unsigned main_array[size];
unsigned arr[size];

int bubble_sort_with_step(unsigned arr[], int const begin_idx, int const end_idx, int step){
	int count = 0;
	for (int i = begin_idx; i + step < end_idx; i++)
	{
		if (arr[i] > arr[i + step])
		{
			std::swap(arr[i], arr[i + step]);
			count += 1;
		}
	}
	return count;
}

int shell_sort_1(unsigned arr[], int const begin_idx, int const end_idx)
{
	int sum = 0;
	int scale = 2;
	int step = end_idx;

	while (step > 1)
	{
		sum += bubble_sort_with_step(arr, begin_idx, end_idx, step);
		step /= scale;
	}
	if (step == 1)
	{
		for (int i = end_idx - 1; i != 0; --i)
		{
			for (int j = i - 1; j != end_idx - 1; ++j)
			{
				if (arr[j] <= arr[j + 1])
				{
					break;
				}
				{
				std::swap(arr[j], arr[j + 1]);
				sum += 1;
				}
			}
		}
	}
	return sum;
}

int shell_sort_2(unsigned arr[], int const begin_idx, int const end_idx)
{
	int sum = 0;
	int scale = log(end_idx) / log(2);
	int step = pow(2, scale) - 1;

	while (step > 1)
	{
		sum += bubble_sort_with_step(arr, begin_idx, end_idx, step);
		scale -= 1;
		step = pow(2, scale) - 1;
	}
	if (step == 1)
	{
		for (int i = end_idx - 1; i != 0; --i)
		{
			for (int j = i - 1; j != end_idx - 1; ++j)
			{
				if (arr[j] <= arr[j + 1])
				{
					break;
				}
				{
					std::swap(arr[j], arr[j + 1]);
					sum += 1;
				}
			}
		}
	}
	return sum;
}

int main(){
	int permutations = 0;
	unsigned long long summary = 0;
	int count = 0;
	int choose;
	std::cout << "Enter 1 (for classic shell), 2 (for Habbard shell): " << std::endl;
	std::cin >> choose;
	for (int j = 0; j < size; j++)
	{
		arr[j] = j;
	}
	unsigned seed = 15;
	std::default_random_engine rng(seed);
	std::uniform_int_distribution<unsigned> dstr(0, size);
	for (int n = 0; n <= size; n += 2000)
	{
		for (int s = 0; s < n; s++)
		{
			main_array[s] = arr[dstr(rng)];
		}
		if (choose == 1)
		{
			auto begin = std::chrono::steady_clock::now();
			permutations = shell_sort_1(main_array, 0, n);
			auto end = std::chrono::steady_clock::now();
			auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << n << " " << time_span.count() << ' ' << permutations << std::endl;
			summary += permutations;
		}

		else if (choose == 2)
		{
			auto begin = std::chrono::steady_clock::now();
			int permutations = shell_sort_2(main_array, 0, n);
			auto end = std::chrono::steady_clock::now();
			auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

			std::cout << n << " " << time_span.count() << ' ' << permutations << std::endl;
			summary += permutations;
		}
	}
	std::cout << "Average permutations: " << std::endl;
	count = size / 2000;
	std::cout << summary / count << std::endl;
	return 0;
}