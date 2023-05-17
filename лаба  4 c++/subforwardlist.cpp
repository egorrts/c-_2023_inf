#include <iostream>
 
 //при загрузке в lms удаляем эту часть
struct subforwardlist {
     int data;
     subforwardlist* next;
};

//инициализация пустого недосписка
bool init(subforwardlist **sfl) {
    *sfl = NULL;
    return true;
} 

/*добавление элемента в конец недосписка, функция получает какой то двойной указатель, позже мы проверим,
является ли он указателем на указатель на первый элемент списка*/
bool push_back(subforwardlist **sfl, int d) {
    subforwardlist *link = *sfl;//теперь link-указатель на первый элемент недосписка
    subforwardlist *first = new subforwardlist;//выделяем место в куче место для одного элемента недосписка, first-указатель на первый элемент
    if (*sfl == NULL) {//проверка, пустой ли список
        *sfl = first;
        (*sfl)->data = d;
        (*sfl)->next = NULL;
        return true;
    } 
    else {
        while (link->next != NULL) {//добираемся до последнего элемента
        link = link->next;
        }
        link->next = first;
        link->next->next = NULL;
        first->data = d;

        return true;
    }
} 

/*удаление элемента с конца недосписка*/
int pop_back(subforwardlist **sfl) {
    subforwardlist *link = *sfl;
    if (*sfl == NULL) {           
        return 0;
    } if ((*sfl)->next == NULL) {
        int deleted = (*sfl)->data;
        delete *sfl;
        *sfl = NULL;
        return deleted;
    } else {
        while (link->next->next != NULL) {//пока не дойдем до предпоследнего элемента
        link = link->next;
        }
        int deleted = link->next->data;
        delete link->next;
        link->next = NULL;
        return deleted;
    }
} 

/*добавление элемента в начало недосписка*/
bool push_forward(subforwardlist **sfl, int d) {
    subforwardlist *first = *sfl;
    if (*sfl == NULL) {
        push_back(sfl, d);
        return true;
    } else {
        *sfl = new subforwardlist;
        (*sfl)->data = d;
        (*sfl)->next = first;
        return true;
    }
} 	

/*удаление элемента из начала недосписка, если пустой - возвращать 0*/
int pop_forward(subforwardlist **sfl) {
    if (*sfl == NULL) {           
        return 0;
    } else {
        subforwardlist *deleted = *sfl;
        int data_deleted = deleted->data;
        *sfl = (*sfl)->next; 
        delete deleted;
        return data_deleted;
    }
}

/*добавление элемента с порядковым номером where*/
bool push_where(subforwardlist **sfl, unsigned int where, int d) {
    subforwardlist *link = *sfl;
    subforwardlist *first = new subforwardlist;
    if (where == 0) {
        return push_forward(sfl, d);
    }
    for (unsigned int i = 0; i <where-1;++i) {
        link = link->next;
    }
    first->data = d;
    first->next = link->next;
    link->next = first;
    return true;
}   

/*удаление элемента с порядковым номером where, если пустой - вернуть 0*/
int erase_where(subforwardlist **sfl, unsigned int where) {
    subforwardlist *link = *sfl;
    if (where == 0) {
        return pop_forward(sfl);
    }
    for (unsigned int i = 0; i < where-1; ++i) {
        link = link->next;
    }
    if (link->next == NULL) {
        return 0;
    } else {
        int deleted = link->next->data;
        subforwardlist *link1 = link->next->next;
        delete link->next;
        link->next = link1;
        return deleted;
    }
}
	
/*определить размер недосписка*/
unsigned int size(subforwardlist **sfl) {
    subforwardlist *link = *sfl;
    unsigned int i = 0;
    while (link != NULL) {
        link = link->next;
        ++i;
        }
    return i;
}	 

/*очистить содержимое недосписка*/
void clear(subforwardlist **sfl) {
    while (*sfl != NULL) {
        pop_forward(sfl);
    }
}
