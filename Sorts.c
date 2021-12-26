#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "CarStruct.c"
#include "Comporators.h"

void new_swap(void * a, void * b, size_t size) {
	void * buf = malloc(size);
	memcpy(buf, a, size);
	memcpy(a, b, size);
	memcpy(b, buf, size);
	free(buf);
}

void gnome_sort(void * first, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
	void * cars = first;

	for (size_t i = 1; i < number; ++i) {
		for (size_t j = i; j; --j) {
			void * p1 = (void*) ((size_t) cars + size*(j - 1));
			void * p2 = (void*) ((size_t) cars + size*j);
			if (comparator(p1, p2) >= 0) {
				new_swap(p1, p2, size);
			}
		}
	}
}

size_t binarySearch(void * cars, void * el, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    size_t left = 0, right = number;
    while (left != right) {
        size_t m = (left+right)/2;
        void * p = (void*) ((size_t) cars + size*m);
        if (comparator(el, p) > 0) left = m + 1;
        else if (comparator(el, p) < 0) right = m;
        else return m;
    }
    return left;
}

// Функция для сортировки массива a [] размера 'n'
void insertionSort(void * cars, size_t number, size_t size, int (*comparator) (const void*, const void*)) {
    size_t i, loc;
    for (i = 1; i < number; ++i) {
        void * el = (void*)((size_t)cars+i*size);
        void * buf = malloc(size);
        memcpy(buf, el, size);
        // найти место, где выбрано, может быть
        loc = binarySearch(cars, el, i, size, comparator);

        // Переместить все элементы после расположения, чтобы создать пространство
        void* donor = (void*) ((size_t)cars + (loc)*size);//OK
        void* recipient = (void*) ((size_t)cars + (loc+1)*size);//OK
        size_t len = i-loc;//OK
        memmove(recipient, donor, len*size);
        memmove(donor, buf, size);
        free(buf);
    }
}

//должна возвращать указатель на индексованный байт с конца и размер элемента, по которому идёт
// если индекс -1 то указатель на начало
void* el(void * first, size_t index, size_t * size_ell, char *** el_ptr, size_t max_len, char field) {
    void * ptr = NULL;
    struct Car* car = (struct Car*)first;
    switch (field) {
        case 0:
            *size_ell = 16;
            if (index == -1)
                return ptr = (void*)(car->mark);
            else
                return ptr = (void*)((size_t)(car->mark)+(*size_ell- sizeof(char)*(index+1)));
            //break;
        case 2:
            *size_ell = 10;//sizeof(long double)-6;
            if (index == -1)
                return ptr = (void*)&(car->mileage);
            else
                return ptr = (void*)((size_t)&(car->mileage)+(sizeof(char)*(index)));
            //ptr = (void*)&(car->mileage);
            //break;
        case 1: {
            char ** p = &(car->name);
            *el_ptr = p;

            if (index == -1)
                return ptr = (void*)(car->name);
            else
                return ptr = (void*)((size_t)(car->name)+sizeof(char)*(max_len-(index+1)));
                //ptr = (void*)((size_t)(car->name)+(*size_ell- sizeof(char)*(index+1)));
            //ptr = (void*)(car->name);
            *size_ell = strlen(car->name)+1;
            //break;
        }
        default:
            return NULL;
            break;
    }
    //return ptr;
}

void radix_sort_uni(void * cars, size_t number, size_t size, char field) {
    int sc = sizeof(char);
    char ** buf = NULL;
    //находим максимальную длину той памяти, которую будем сравнивать
    size_t max_len = 0;
    for (size_t index = 0; index < number; ++index) {
        size_t len = 0;
        void* car = (void*) ((size_t)cars + index*size);
        void * p = el(car, -1, &len, &buf, 0, field);
        if (max_len < len) max_len = len;
    }

    // унификация длинн
    for (size_t i = 0; i < number; ++i) {
        size_t len = 0;
        void * car = (void*) ((size_t)cars + i*size);
        char **p = NULL;
        void * byte = el(car, -1, &len, &p, max_len, field);
        if (len < max_len) {

            //void *buf1 = el(car, -1, &len, &p, 0, field);

            // нужен указатель на указатель на имя
            // чтобы положить туда указатель на новую память
            *p = realloc(*p, (1 + max_len) * sc);

            int l = strlen(*p);
            for (int k = l; k <= max_len; ++k) (*p)[k] = '\0';
        }
    }

    // основной цикл:
    // - рассортировать по значению текущего байта
    // - поменять массив
    void * copy_arr = malloc(size*number);
    for (size_t index = 0; index < max_len; ++index) {
        //корзинки для массивов указателей на указатели на элементы: ->|=>
        void *** box = malloc(256*sizeof(void**));
        for (size_t i = 0; i < 256; ++i) {
            box[i] = malloc(sizeof(void**));
            box[i][0] = NULL;
            //*((void***)((size_t)box+i*sizeof(void**))) = malloc(sizeof(void**));
            //**((void***)((size_t)box+i*sizeof(void**))) = NULL;
        }
        //void * copy_arr = malloc(size*number);
        memcpy(copy_arr, cars, size*number);

        // разбрасывам указатели на элементы по корзинкам
        for (size_t i = 0; i < number; ++i) {
            size_t len = 0;
            void * car = (void*) ((size_t)copy_arr + i*size);
            void * byte = el(car, index, &len, &buf, max_len, field);//el(car, -1, &len, &buf, max_len, field);

            //byte = el(car, index, &len, &buf, max_len, field);
            unsigned char n = *((unsigned char*)byte);

            // смотрим сколько уже есть указателей
            // и добавляем к ним ещё один
            size_t k = 0;
            while (box[n][k] != NULL) k++;
            box[n] = realloc(box[n], sizeof(void *) * (k + 2));
            box[n][k + 1] = NULL;
            box[n][k] = car;
        }

        int a = 0;
        // переставляем индексы в массиве в соответствии с корзинками
        for (size_t i = 0; i < 256; ++i) {
            int k = 0;
            while (box[i][k] != NULL) {// вероятно ошибка при выделении памяти
                memcpy((void*)((size_t)cars+a*size), box[i][k], size); // ошибка индекса i
                k++;
                a++;
            }
        }
        //free(copy_arr);
        for (size_t i = 0; i < 256; ++i) free(box[i]);
        free(box);
    }
    free(copy_arr);
    //освобождаем нулёвую память
    for (size_t i = 0; i < number; ++i) {
        size_t len = 0;
        void * car = (void*) ((size_t)cars + i*size);
        void * byte = el(car, -1, &len, &buf, max_len, field);

        if (len < max_len) {
            char **p = NULL;
            void *buf1 = el(car, -1, &len, &p, 0, field);

            // нужен указатель на указатель на имя
            // чтобы положить туда указатель на новую память
            *p = realloc(*p, (1 + strlen((char*)buf1)) * sc);
        }
    }
}

void sort(struct Car ** all_cars, int number_of_cars, char index_of_sort) {
	printf("With which characteristic do you wanna sort array?\n");
	printf("1) Mark\n");
	printf("2) Name\n");
	printf("3) Mileage\n");
	int chose = -1;
	while (scanf("%d", &chose) <= 0) { getchar(); printf("Error!\n"); } getchar();
	if (chose > 3 || chose < 1) {
		printf("Wrong number. Try again.\n");
		sleep(3);
		return;
	}
	chose--;
	int (*comp[3])(const void*, const void*) = {comp_mark, comp_name, comp_mileage};

	switch(index_of_sort) {
		case 0: gnome_sort(*all_cars, number_of_cars, sizeof(struct Car), comp[chose]); break;
		case 1: insertionSort(*all_cars, number_of_cars, sizeof(struct Car), comp[chose]); break;
		case 2: radix_sort_uni(*all_cars, number_of_cars, sizeof(struct Car), (char) chose); break;
		default: return;
	}
}
