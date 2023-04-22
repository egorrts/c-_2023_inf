#include <iostream>
#include <chrono>
#include <random>
using namespace std;

int mass[1000000] = {};
int count1[1000000] = {};

/*функция заполняет первые size элементов массива значениями от 0 до size-1 в произвольном порядке */
void fill_array(int size){ 
    default_random_engine rng((int)time(0));
    uniform_int_distribution<unsigned>dstr(0, size - 1);
    for (int i = 0; i < size; ++ i){
        mass[i] = dstr(rng);
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

void strategy_A(int number, int size){
    int a;
    for (int i = 0; i < size; i++){
        if (mass[i] == number){
            a = mass[0];
            mass[0] = mass[i];
            mass[i] = a;
        };

    }
}

void strategy_B(int number, int size){
    int a;
    for (int i = 0; i < size; i ++){
        if (mass[i] == number){
            if (i != 0){
                a = mass[i-1];
                mass[i-1] = mass[i];
                mass[i] = a;
            }
        }
    }
}

void strategy_C(int number, int size){
    int a;
    for (int i = 0; i < size; i ++){
        if (mass[i] == number){
            count1[i] += 1;
            if (i != 0){
                if (count1[i] > count1[i-1]){
                    a = mass[i-1];
                    mass[i-1] = mass[i];
                    mass[i] = a;
                    a = count1[i-1];
                    count1[i-1] = count1[i];
                    count1[i] = a;                
                }

            }
        }
    }
}

/*функция делает 100 запусков функции strategy A для
фиксированного размера массива size и выводит среднее время работы функции*/
float find_time_strA(int number, int size){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 10000; cnt != 0; --cnt){
        strategy_A(number, size);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*функция делает 100 запусков функции strategy B для
фиксированного размера массива size и выводит среднее время работы функции*/
float find_time_strB(int number, int size){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt){
        strategy_B(number, size);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*функция делает 100 запусков функции strategy C для
фиксированного размера массива size и выводит среднее время работы функции*/
float find_time_strC(int number, int size){
    auto begin = chrono::steady_clock::now();
    for (unsigned cnt = 100; cnt != 0; --cnt){
        strategy_C(number, size);
    }
    auto end = chrono::steady_clock::now();
    auto time_span = chrono::duration_cast<chrono::milliseconds>(end-begin);
    return (((float)time_span.count()));
}

/*возвращает рандомное число от 1 до x-1*/
int random_ravn(int x){
    srand((int)time(0));
    return rand() % x;
}

/*возвращает рандомное число для неравномерного запроса*/
int random_neravn(int x){
    srand((int)time(0));
    return (x/10) + rand() % (x/2);
}

/*функция для фикс размера массива 50 раз выбирает рандомный элемент и ищет его,
затем выводит размер массива и время работы*/
void result_time_A_ravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_ravn(size);
        sum += find_time_strA(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
}

void result_time_B_ravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_ravn(size);
        sum += find_time_strB(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
}

void result_time_C_ravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_ravn(size);
        sum += find_time_strC(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
}

void result_time_A_neravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_neravn(size);
        sum += find_time_strA(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
} 

void result_time_B_neravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_neravn(size);
        sum += find_time_strB(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
}

void result_time_C_neravn(int size){
    srand((int)time(0));
    float sum = 0;
    for (int i = 0; i < 50; ++i) {
        int r = random_neravn(size);
        sum += find_time_strC(r, size);
    }
    std::cout << size << ' ' << sum << '\n';       
}

/*функция для длин массива от 100 до 500 заполянет массив элементами в рандомном порядке, 
затем 100 раз ищет элемент от 0 до длины массива-1, и переставляет элементы массива соотв образом */
void ravn_zapros_A(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for (int i = 0; i < 100; i ++){
            for (int j = 0; j < size1-1; ++j){
                strategy_A(j, size1);
            }
        }
        result_time_A_ravn(size1);  
    }
} 

void ravn_zapsos_B(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for (int i = 0; i < 100; i ++){
            for (int j = 0; j < size1; ++j){
                strategy_B(j, size1);
            }
        }
        result_time_B_ravn(size1);       
    }
}

void ravn_zapros_C(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for (int i = 0; i < 100; i ++){
            for (int j = 0; j < size1; ++j){
                strategy_C(j, size1);
            }
        }
        result_time_C_ravn(size1);       
    }
}

/*функция для размеров массива от 100 до 500 заполняет массив произв элементами, 
затем 100 раз делает цикл поиска элементов от размер массива/20 до размер массива/20 +
размер массива/2, используется остаток от деления j на size1/2 чтобы элементы для поиска начали повторяться
с какого то момента(когда j станет равным size1/2), осуществляются соответствующие перстановки в массиве*/
void neravn_zapr_A(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for(int i = 0; i < 100; i ++){
            for (int j = 0; j < size1; j ++){
                strategy_A(size1/20 + j%(size1/2), size1);
            }
        }
        result_time_A_neravn(size1);
    }
}

void neravn_zapr_B(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for(int i = 0; i < 100; i ++){
            for (int j = 0; j < size1; j ++){
                strategy_B(size1/20 + j%(size1/2), size1);
            }
        }
        result_time_B_neravn(size1);
    }
}

void neravn_zapr_C(){
    for (int size1 = 100; size1 < 500; size1 += 1){
        fill_array(size1);
        for(int i = 0; i < 100; i ++){
            for (int j = 0; j < size1; j ++){
                strategy_C(size1/20 + j%(size1/2), size1);
            }
        }
        result_time_C_neravn(size1);
    }
}

int main(){
    //ravn_zapros_A();
    //ravn_zapros_B();
    //ravn_zapros_C();
    //neravn_zapr_A();
    //neravn_zapr_B();
    neravn_zapr_C();
}