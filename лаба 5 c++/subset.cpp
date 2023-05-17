#include<iostream>
#include <cstdlib>

struct subset_node {
    int key;
    subset_node *left;
    subset_node *right;
};

/*инициализация пустого дерева (аналогично списку, пустое дерево это указатель на NULL)*/
bool init(subset_node **sn) {
    *sn = NULL;
    return true;
}

/*добавление элемента в дерево, дубли игнорировать (ничего не добавлять в дерево, если там уже есть элемент с таким же key) и возвращать false*/
bool insert(subset_node **sn, int k) {
    if (*sn == NULL) {//проверка на пустое дерево
        *sn = new subset_node;//выделяем место в куче под элемент типа subset_node
        (*sn)->left = NULL;
        (*sn)->right = NULL;
        (*sn)->key = k;
        return true;
    }
    else if (k < (*sn)->key) {
        return insert(&((*sn)->left), k);//рекурсия
    }
    else if (k > (*sn)->key) {
        return insert(&((*sn)->right), k);
    }
    return false;
}
 /*функция, которая ищет самый левый элемент в поддереве с данной вершиной*/
subset_node* findMinElement(subset_node* sn) {
    while (sn->left != NULL) sn = sn->left;
    return sn;
}

bool remove(subset_node **sn, int k) {
    if (*sn == NULL) {//проверка на пустое дерево
        return false; 
    }
    if (k < (*sn)->key) {
        return remove(&((*sn)->left), k);//рекурсия
    } 
    else if (k > (*sn)->key) {
        return remove(&((*sn)->right), k);
    }//теперь найден нужный узел дерева
    else {
        if ((*sn)->left == NULL && (*sn)->right == NULL) {//если от найденного узла не идет ветвей вниз, просто удаляем 
            delete *sn;
            *sn = NULL;
        }
        else if ((*sn)->left == NULL) {//если идет только ветвь вправо, ставим ближайший узел на место удаляемого
            subset_node *pointer = *sn;
            *sn = (*sn)->right;
            delete pointer;
        } 
        else if ((*sn)->right == NULL) {//аналогично с левой ветвью
            subset_node *pointer = *sn;
            *sn = (*sn)->left;
            delete pointer;
        }
        else {//находим в правом поддереве минимальный элемент и перемещаем его на место удаляемого узла 
            subset_node *temp = findMinElement((*sn)->right);
            (*sn)->key = temp->key;
            return remove(&((*sn)->right), temp->key);
        }
        return true;
    }
}

/*поиск элемента в дереве, нужно вернуть указатель на элемент с тем же key или, если такого элемента не нашлось, то NULL*/
subset_node* find(subset_node *sn, int k) {
    if (sn == NULL) {
        return NULL;
    }
    else if (k < sn->key) {
        return find(sn->left, k);//везде рекурсия))
    }
    else if (k > sn->key) {
        return find(sn->right, k);
    }
    return sn;
}

/*количество элементов в дереве*/
unsigned int size(subset_node *sn) {
    if (sn == NULL) {
        return 0;
    }
    else {
        return (size(sn->left) + size(sn->right) + 1);//ищем размеры поддеревьев, прибавляем 1 за вершину исходного дерева
    }
}

/*высота дерева*/
unsigned int height(subset_node *sn) {
    if (sn == NULL) {
        return 0;
    }
    else {
        unsigned int leftH = height(sn->left);
        unsigned int rightH = height(sn->right);
        if (leftH > rightH){
            return (leftH + 1);
        }
        else{
            return (rightH + 1);
        }
    }
}

/*очистить всю используемую память*/
void destructor(subset_node *sn) {
    if (sn != NULL) {
        destructor(sn->left);
        destructor(sn->right);
        delete sn;
    }
}

/*эта функция вызывается рекурсивно для левого поддерева узла, 
затем сохраняет значение ключа узла в массив и увеличивает счетчик на единицу, 
чтобы указать на следующий элемент в массиве.
 Затем функция вызывается рекурсивно для правого поддерева узла*/
void DFS1(subset_node *sn, int* &result, int &i) {
    if (sn == NULL) return;
    DFS1(sn->left, result, i);
    result[i++] = sn->key;
    DFS1(sn->right, result, i);
}

/*обход в глубину, возвращает указатель на массив из динамической памяти (кучи)*/
/*изначально функция создает массив размером size(sn),
функция вызывает функцию DFSUtil для обхода дерева, 
после чего возвращает указатель на заполненный массив.
в итоге мы получаем отсортированный список всех узлов дерева в порядке возрастания значений ключей*/
int* DFS(subset_node *sn) {
    int *result = new int[size(sn)];
    int i = 0;
    DFS1(sn, result, i);
    return result;
}