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

/*функция заполняет массив размера size упорядоченными элементами от 0 до size-1, 
необходимо не оставлять пробелы между соседними элементами, потому что в противном случае для
конкретного значения элемента мы не бдуем знать, лежит он в массиве или нет и не сможем разделить
процесс поиска элемента, который точно лежит в массиве или не лежит*/
void fill_array_orderly(int size){
    for (int i = 0; i < size; ++ i){
        mass[i] = i;
    }
} 

/*функция осуществляет поиск элемента в массиве размера size полным перебором*/
bool full_find(int number, int size){ 
    for (int i = 0; i < size; i ++){
            if (mass[i] == number){
                return true;
                return 0;
            }
    }
    return false;
}

/*функция осуществляет бинарный поиск элемента в массиве размера size*/
bool bin_find(int number, int size){
    int beg = 0;
    int end = size; 
    while (end > beg){
        int mid = beg + (end - beg + 1) / 2;
        if (mass[mid] == number){
            return true;
        }
        else if (number < mass[mid]){
            end = mid - 1;
        }
        else if (number > mass[mid]) {
            beg = mid + 1;
        }             
    }
    if (mass[beg + (end - beg + 1) / 2] == number){
        return true;
    }
    return false;
}

/*функция делает 100 запусков функции полного перебора full_find для
фиксированного размера массива size и выводит среднее время работы функции*/
float find_time_lin(int number, int size){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt){
        full_find(number, size);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*осуществляет 100 запусков функции бинарного поиска для фиксированного 
значения size и выводит среднее время работы*/
float find_time_bin(int number, int size){ 
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 1000000; cnt != 0; --cnt){
        bin_find(number, size);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/* запускает find_time_lin для 100 длин массива от 100 до 1000000 для числа, которого точно нет в массиве(-10)
и выводит время поиска этого элемента для каждой длины массива*/
void data_max_lin(){ 
    for (int size = 100; size <= 1000000; size+=9999) {
        fill_array(size);
        cout << size << ' ' << find_time_lin(-10, size) << '\n';
    }
    cout << '\n';
}

/*запускает find_time_bin для 100 длин массива от 100 до 1000000 для элемента, которого точно нет в массиве(-10)
 и выводит для каждой длины массива время поиска этого элемента */
void data_max_bin(){ 
    for (int size = 100; size <= 1000000; size+=9999) {
        fill_array_orderly(size);
        cout << size << ' ' << find_time_bin(-10, size) << '\n';
    }
    cout << '\n';
}

/*для каждой длины массива генерирует случайное число 50 раз и 50 раз ищет его при помощи функции бинарного поиска,
выводит среднее значение времени поиска элемента*/
void average_data_bin(){
    srand((int)time(0));
    for (int size = 100; size <= 1000000; size+=9999) {
        float timesum = 0;
        for (int i = 0; i < 50; ++i) {
            fill_array_orderly(size);
            int randnumb = rand() % size;
            timesum += find_time_bin(randnumb, size);
        }
        std::cout << size << ' ' << (((float)timesum)/50) << '\n';
    }
        
}

/*для каждой длины массива генерирует случайное число, 50 раз заполняет массив различным образом,
50 раз ищет его в массиве при помощи функции линейного поиска и выводит среднее время поиска*/
void average_data_lin(){
    srand((int)time(0));
    for (int size = 100; size <= 1000000; size+=9999) {
        float timesum = 0;
        for (int i = 0; i < 50; ++i) {
            fill_array(size);
            int randnumb = rand() % size;
            timesum += find_time_lin(randnumb, size);
        }
        std::cout << size << ' ' << (((float)timesum)/50) << '\n';
    }
        
} 
int main(){
    //data_max_bin();
    //data_max_lin();
    //average_data_bin();
    average_data_lin();
}





