#include <iostream>
#include <chrono>
#include <random>

int const size = 100000;
unsigned main_array[size];
unsigned arr[size];

int bubble_sort_with_step(unsigned arr[], int const begin_idx, int const end_idx, int step)
{
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

int comb_sort(unsigned arr[], int const begin_idx, int const end_idx)
{
	int sum = 0;
	int scale = 2;
	int step = end_idx / 2;

	while (step > 1)
	{
		sum += bubble_sort_with_step(arr, begin_idx, end_idx, step);
		step /= scale;
	}
	if (step == 1)
	{
		for (int i = 0; i < end_idx - 1; i++)
		{
			for (int j = 0; j < end_idx - i - 1; j++)
			{
				if (arr[j] > arr[j + 1])
				{
					std::swap(arr[j], arr[j + 1]);
					sum += 1;
				}
			}
		}
	}
	return sum;
}

int main()
{
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
		auto begin = std::chrono::steady_clock::now();
		int permutations = comb_sort(main_array, 0, n);
		auto end = std::chrono::steady_clock::now();
		auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

		std::cout << n << " " << time_span.count() << ' ' << permutations << std::endl;
	}
	return 0;
}
