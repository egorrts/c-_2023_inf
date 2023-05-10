struct subvector {
    int *mas; //указателя на массив в куче
    unsigned int top; //размер той памяти, с которой мы работаем, в которой есть осмысленные данные
    unsigned int capacity; //размер памяти, выделенной в этой куче
};

//инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)
bool init (subvector *qv) {
    qv->capacity = 0;
    qv->top = 0;
    qv->mas = NULL;
} 

// добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
bool push_back (subvector *qv, int d) {
    if (qv->top < qv->capacity) {
        int link = qv->top;
        qv->mas[link] = d;
        qv->top += 1; 
        return true;  
    } 
    else {
        resize(qv, (qv->top)+1);
        int link = qv->top;
        qv->mas[link] = d;
        qv->top += 1;
        return true;
    }
} 

//удаление элемента с конца недовектора, значение удаленного элемента вернуть (если недовектор пустой, вернуть ноль)
int pop_back (subvector *qv) {
    if (qv->top != 0) {
        qv->top -= 1;
        return qv->mas[qv->top];
    }
    return 0;
} 

//увеличить емкость недовектора (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)
bool resize (subvector *qv, unsigned int new_capacity) {
    int* a = new int[new_capacity];
    if (new_capacity >= qv->capacity){
        for (int i = 0; i < qv->top; i++){
            a[i] = (qv->mas)[i];
        }
    } 
    else {
    for (unsigned int i = 0; i < new_capacity; ++i) {
        a[i] = qv->mas[i];
    }
    qv->top = new_capacity;
    }
    qv->capacity = new_capacity;
    delete[] qv->mas;
    qv->mas = a;
    return true;
}

// очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top
void shrink_to_fit (subvector *qv) {
    int* a = new int[qv->top];
    for (unsigned int i = 0; i < qv->top; ++i) {
        a[i] = qv->mas[i];
    }
    delete[] qv->mas;
    qv->mas = a;
    qv->capacity = qv->top;
} 

//очистить содержимое недовектора, занимаемое место при этом не меняется
void clear (subvector *qv) {
    qv->top = 0;
} 

//очистить всю используемую память, инициализировать недовектор как пустой
void destructor (subvector *qv) {
    qv->top = 0;
    qv->capacity = 0;
    delete[] qv->mas;
}	