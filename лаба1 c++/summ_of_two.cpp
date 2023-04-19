#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int mass[1000000] = {};

/*функция заполняет первые size элементов массива значениями от 0 до size-1 в произвольном порядке */
void fill_array(int size){ 
    default_random_engine rng((int)time(0));
    uniform_int_distribution<unsigned>dstr(0, size - 1);
    for (int i = 0; i < size; ++ i){
        mass[i] = dstr(rng);
    }
}

/*функция заполняет массив упорядоченными элементами*/
void fill_array_orderly(int size){
    for (int i = 0; i < size; ++ i){
        mass[i] = i;
    }
}

/*функция ищет элемент в массиве размера size простым перебором*/
bool direct_find(int size, int sum){
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < i; ++j){
            if (mass[i] + mass[j] == sum){
                return true;
            }
        }
    }
    return false;
}
 
 /*делает 100 замеров времени работы функции простого перебора, чтобы найти среднее*/
float find_time_dir(int size, int sum){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10; cnt != 0; --cnt){
        direct_find(size, sum);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*так как массив упорядочен, мы точно знаем, что каждый следующий элемент больше предыдущего,
сначала мы ищем сумму первого и последнего элемента массива, если она больше искомой,
берем вместе последнего элемента предпоследний, чтобы ее уменьшить, если сумма оказалась меньше,
берем второй элемент вместе первого, чтобы ее увеличить и так далее, пока не найдем два элемента
с искомой суммой либо не пройдем весь массив*/
bool smart_algorithm(int size, int sum){
    int beg = 0;
    int end = size - 1;
    while (end > beg){
        if (mass[beg] + mass[end] == sum){
            return true;
        }
        else if (mass[beg] + mass[end] > sum){
            end --;
        }
        else if (mass[beg] + mass[end] < sum){
            beg ++;
        }
    }
    return false;
}

float find_time_smart(int size, int sum){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt){
        smart_algorithm(size, sum);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*запускает функцию простого перебора для 100 длин массивов и суммы,
 которого точно нет в массиве и для каждой выводит время работы*/
void data_max_dir(){ 
    for (int size = 100; size <= 100000; size+=999) {
        fill_array(size);
        cout << size << ' ' << find_time_dir(size, -10) << '\n';
    }
    cout << '\n';
}

/*запускает умный алгоритм для 100 длин массива от 100 до 1000000 для суммы которой
 точно нет в массиве(-10) и выводит для каждой длины массива время поиска суммы */
void data_max_smart(){ 
    for (int size = 100; size <= 1000000; size+=9999) {
        fill_array_orderly(size);
        cout << size << ' ' << find_time_smart(size, -10) << '\n';
    }
    cout << '\n';
}

/*для каждой длины массива генерирует случайную сумму 50 раз и 50 раз ищет ее
 при помощи функции простого перебора, выводит среднее значение времени поиска*/
void average_data_dir(){
    srand((int)time(0));
    for (int size = 100; size <= 10000; size+=99) {
        float timesum = 0;
        for (int i = 0; i < 50; ++i) {
            fill_array(size);
            int randnumb = rand() % ((size-1)*size/2);
            timesum += find_time_dir(size, randnumb);
        }
        std::cout << size << ' ' << (((float)timesum)) << '\n';
    }
        
}

/*для каждой длины массива генерирует случайную сумму 50 раз и 50 раз ищет ее
 при помощи умного алгоритма, выводит среднее значение времени поиска*/
void average_data_smart(){
    srand((int)time(0));
    for (int size = 100; size <= 100000; size+=999) {
        float timesum = 0;
        for (int i = 0; i < 50; ++i) {
            fill_array_orderly(size);
            int randnumb = rand() % (size-1)*size/2;
            timesum += find_time_smart(size, randnumb);
        }
        std::cout << size << ' ' << (((float)timesum)) << '\n';
    }
        
}

int main(){
    //data_max_dir();
    //data_max_smart();
    //average_data_dir();
    average_data_smart();
}