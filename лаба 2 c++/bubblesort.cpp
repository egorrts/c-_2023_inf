#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int rand_uns(int min, int max) {
unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
static std::default_random_engine e(seed);
std::uniform_int_distribution<int> d(min, max);
return d(e);
}

void bubblesort(int size, int* mass){ //сортировка пузырьком
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size-1; j ++){
            if (mass[j] > mass[j+1]){
                int temp = mass[j];
                mass[j] = mass[j+1];
                mass[j+1] = temp;
            }
        }
    }
}

void insertionsort(int size, int* mass){ //сортировка вставками
    for(int i = 1; i < size; i++)
	{
		int j = i - 1;
		while(j >= 0 && mass[j] > mass[j + 1])
		{
			swap(mass[j], mass[j + 1]);
			j--;
		}
	}
}

void cocktailsort(int size, int* mass){ //сортировка шейкером
    int low = 0;
    int up = size-1;
    int last, tmp;
    while (low < up){
        last = -1;
        for (int i = low; i < up; i++){
            if (mass[i] > mass[i+1]){
                tmp = mass[i];
                mass[i] = mass[i+1];
                mass[i+1] = tmp;
                last = 1;
            }
        }
        up = last;
        last = size;
        for (int i = up-1; i>= low; i --){
            if (mass[i] > mass[i+1]){
                tmp = mass[i];
                mass[i] = mass[i+1];
                mass[i+1] = tmp;
                last = 1;
            }
        }
        low = last + 1;
    }

}

float find_time_bubble(int size, int* mass){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10; cnt != 0; --cnt){
        bubblesort(size, mass);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

float find_time_insertion(int size, int* mass){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10; cnt != 0; --cnt){
        insertionsort(size, mass);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

float find_time_cocktail(int size, int* mass){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10; cnt != 0; --cnt){
        cocktailsort(size, mass);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

void data_bubble(){
    for (int size = 1000; size < 10000; size += 99){
        int* mass = new int[size];
        for (int i = 0; i < size; i ++){
            mass[i] = rand_uns(0, size);
        }
        cout << size << ' ' << find_time_bubble(size, mass) << '\n';
    }
}

void data_insertion(){
    for (int size = 1000; size < 10000; size += 99){
        int* mass = new int[size];
        for (int i = 0; i < size; i ++){
            mass[i] = rand_uns(0, 10*size);
        }
        cout << size << ' ' << find_time_insertion(size, mass) << '\n';
    }
}

void data_cocktail(){
    for (int size = 10000; size < 1000000; size += 9900){
        int* mass = new int[size];
        for (int i = 0; i < size; i ++){
            mass[i] = rand_uns(0, size);
        }
        cout << size << ' ' << find_time_cocktail(size, mass) << '\n';
    }
}

int main(){
    //data_bubble();
    //data_insertion();
    data_cocktail();
}




