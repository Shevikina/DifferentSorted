﻿#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;
void generateArray(int* array, int size) {
    srand(time(NULL));
    for (int iterator = 0; iterator < size; iterator++) {
        array[iterator] = rand() % 100 + 1;
    }
}

void ofstreamArray(ofstream &out, int* array, int size) {
    if (out.is_open()) {
        for (int iterator = 0; iterator < size; iterator++)
            out << array[iterator] << " ";
        out << array[size - 1];
    }
}

void lookArray(int* array, int size) {
    for (int iterator = 0; iterator < size; iterator++) {
        cout << array[iterator] << " ";
    }
    cout << endl;
}

void selectionSort(int* array, int size, int begin = 0, bool tipe = true) {
    double time_begin = clock();
    int new_iterator = 0;
    int temporary_num = 0;
    for (int iterator = begin; iterator < size; iterator++) {
        new_iterator = iterator;
        for (int iter = iterator; iter < size; iter++) {
            if (array[new_iterator] > array[iter])
                new_iterator = iter;
        }
        temporary_num = array[iterator];
        array[iterator] = array[new_iterator];
        array[new_iterator] = temporary_num;
    }
    double time_end = clock();
    if (tipe)
        cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
}

void reverse(int* array, int size) {
    int tmp = 0;
    for (int iterator = 0; iterator < size / 2; iterator++) {
        tmp = array[iterator];
        array[iterator] = array[size - iterator-1];
        array[size - iterator-1] = tmp;
    }

}

void bubbleSort(int* array, int size) {
    double time_begin = clock();
    int tmp = 0;
    for (int first_iterator = 0; first_iterator < size; first_iterator++) {
        for (int second_iterator = size - 1; second_iterator >= first_iterator + 1; second_iterator--) {
            if (array[second_iterator] < array[second_iterator - 1]) {
                tmp = array[second_iterator];
                array[second_iterator] = array[second_iterator - 1];
                array[second_iterator - 1] = tmp;
            }
        }
    }
    double time_end = clock();
    cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
}

void instertionSort(int* array, int size) {
    double time_begin = clock();
    int key = 0;
    int main_iterator = 0;
    for (int side_iterator = 1; side_iterator < size; side_iterator++) {
        key = array[side_iterator];
        main_iterator = side_iterator - 1;
        while (main_iterator >= 0 && array[main_iterator] > key) {
            array[main_iterator + 1] = array[main_iterator];
            main_iterator--;
            array[main_iterator + 1] = key;
        }
    }
    double time_end = clock();
    cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
}

void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR) {
    int i = 0;
    int j = 0;
    while (i < lenL || j < lenR) {
        if (i < lenL && j < lenR) {
            if (L[i] <= R[j]) {
                merged[i + j] = L[i];
                i++;
            }
            else {
                merged[i + j] = R[j];
                j++;
            }
        }
        else if (i < lenL) {
            merged[i + j] = L[i];
            i++;
        }
        else if (j < lenR) {
            merged[i + j] = R[j];
            j++;
        }
    }
}

void mergeSort(int* array, int size) {
    if (size > 1) {
        int middle = size / 2;
        int rem = size - middle;
        int* L = new int[middle];
        int* R = new int[rem];
        for (int itetator = 0; itetator < size; itetator++) {
            if (itetator < middle) {
                L[itetator] = array[itetator];
            }
            else {
                R[itetator - middle] = array[itetator];
            }
        }
        mergeSort(L, middle);
        mergeSort(R, rem);
        merge(array, size, L, middle, R, rem);
    }
}

void quickSort(int* array, int const size) {
    

    int middle_array = 0;
    int middle = size / 2;
    int iterator, left_iterator = 0, right_iterator = 0;
    if (size > 1) {
    int* left_array = new int[size];
    int* right_array = new int[size];
    middle_array = array[middle];
    for(iterator=0;iterator<size;iterator++){
      if(iterator!=middle){
        if(array[iterator]<middle_array){
          left_array[left_iterator] = array[iterator];
          left_iterator++;
        }
        else{
          right_array[right_iterator] = array[iterator];
          right_iterator++;
        }
      }
    }
    quickSort(left_array,left_iterator);
    quickSort(right_array,right_iterator);
    for(int iterator=0;iterator<size;iterator++){
      if(iterator<left_iterator){
        array[iterator] = left_array[iterator];;
      }
      else if(iterator==left_iterator){
        array[iterator] = middle_array;
      }
      else{
        array[iterator] = right_array[iterator-(left_iterator+1)];
      }
    }
  }
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int size = 0;
    cout << "Введите размерность генерируемого массива\n";
    cin >> size;
    if (size > 0) {
        int* array = new int[size];
        cout << "Выберите какой массив вы хотите сгенерировать\n"
            "1-Рандомный\n2-Рандомный на правую половину\n"
            "3-Рандомный на левую половину\n4-Массив отсортированный в обратном подярке\n";
        int tipe_generate_massive = 0;
        cin >> tipe_generate_massive;
        ofstream out_parent;
        out_parent.open("parentArray.txt");
        if (out_parent.is_open()) {
        switch (tipe_generate_massive) {
        case 1: {
            generateArray(array, size);
            cout << " Ваш исходный массив:\n";
            lookArray(array, size);
            
                /*for (int iterator = 0; iterator < size; iterator++)
                    out_parent << array[iterator] << " ";
                out_parent << array[size - 1];
            */
            ofstreamArray(out_parent, array, size);
            break;
        }
        case 2: {
            generateArray(array, size);
            selectionSort(array, size / 2, 0, false);
            cout << " Ваш исходный массив:\n";
            lookArray(array, size);
            
                for (int iterator = 0; iterator < size; iterator++)
                    out_parent << array[iterator] << " ";
                out_parent << array[size - 1];
            
            break;
        }
        case 3: {
            generateArray(array, size);
            selectionSort(array, size, size / 2, false);
            cout << " Ваш исходный массив:\n";
            lookArray(array, size);
            
                for (int iterator = 0; iterator < size; iterator++)
                    out_parent << array[iterator] << " ";
                out_parent << array[size - 1];
            
            break;
        }
        case 4: {
            generateArray(array, size);
            selectionSort(array, size, 0, false);
            reverse(array, size);
            cout << " Ваш исходный массив:\n";
            lookArray(array, size);
            
                for (int iterator = 0; iterator < size; iterator++)
                    out_parent << array[iterator] << " ";
                out_parent << array[size - 1];
            
            break;
        }
        default: {
            cout << "Ошибка. Нет такого номера для выбора генерации массива.";
            return -1;
        }
        }
    }
        else {
            cout << "Ошибка открытия файла parentArray.txt для записи\n";
            return -1;
        }
        cout << "Выберите тип сортировки:\n1-Сортировка выбором\n2-Сортировка пузырьком\n"
            "3-Сортировка вставками\n4-Сортировка слиянием\n5-Быстрая сортировка\n";
        int tipe_sorted = 0;
        cin >> tipe_sorted;
        ofstream out_child("childArray.txt");
        if (out_child.is_open()) {
            switch (tipe_sorted) {
            case 1: {
                selectionSort(array, size, 0, true);
                cout << "Отсортированный массив:\n";
                lookArray(array, size);
                for (int iterator = 0; iterator < size; iterator++)
                    out_child << array[iterator] << " ";
                out_child << array[size - 1];
                break;
            }
            case 2: {
                bubbleSort(array, size);
                cout << "Отсортированный массив:\n";
                lookArray(array, size);
                for (int iterator = 0; iterator < size; iterator++)
                    out_child << array[iterator] << " ";
                out_child << array[size - 1];
                break;
            }
            case 3: {
                instertionSort(array, size);
                cout << "Отсортированный массив:\n";
                lookArray(array, size);
                for (int iterator = 0; iterator < size; iterator++)
                    out_child << array[iterator] << " ";
                out_child << array[size - 1];
                break;
            }
            case 4: {
                double time_begin = clock();
                mergeSort(array, size);
                double time_end = clock();
                cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
                cout << "Отсортированный массив:\n";
                lookArray(array, size);
                for (int iterator = 0; iterator < size; iterator++)
                    out_child << array[iterator] << " ";
                out_child << array[size - 1];
                break;
            }
            case 5: {
                double time_begin = clock();
                quickSort(array, size);
                double time_end = clock();
                cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
                cout << "Отсортированный массив:\n";
                lookArray(array, size);
                for (int iterator = 0; iterator < size; iterator++)
                    out_child << array[iterator] << " ";
                out_child << array[size - 1];
                break;
            }
            default: {
                cout << "Ошибка. Нет такого номера для выбора сортировки массива.";
                return -1;
            }
            }
            return 0;
        }
        else {
            cout << "Ошибка открытия файла childArray.txt для записи\n";
            return -1;
        }
    }
    else
        return -1;
}
