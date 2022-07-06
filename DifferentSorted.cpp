#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

double global_lead_time = 0;

class options {
public:
    char** key;
    char** option;

public:
    options(int argc, char** argv) {
        this->argc = argc;
        key = new char* [20];
        option = new char* [50];
        static char str = '\0';

        mass_size = 0;
        cout << endl;
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] == '-' && argv[i][1] == '-') {
                if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--generate-array") == 0) {
                    key[mass_size] = argv[i];
                    option[mass_size] = &str;
                }
                else {
                    key[mass_size] = argv[i];
                    option[mass_size] = argv[i + 1];
                }
                cout << key[mass_size] << " " << option[mass_size] << endl;
                mass_size++;
            }
        }
    }
    ~options() {
        delete[] key;
        delete[] option;
    }

    bool isKey(const char* new_key) const {
        for (int i = 0; i < mass_size; i++) {
            if (strcmp(new_key, key[i]) == 0)
                return true;
        }
        return false;
    }

    int whatTheNumberKey(const char* new_key) {
        for (int i = 0; i < mass_size; i++)
            if (strcmp(new_key, key[i]) == 0) {
                return i;
            }
        return -1;
    }

protected:
    int argc = -1;
    int mass_size;
};

void generateSimpleArray(int* array, int size) {
    srand(time(0));
    for (int iterator = 0; iterator < size; iterator++) {
        array[iterator] = rand() % 1000000 + 1;
    }
}

void ofstreamArrayTXT(ofstream &out, int* array, int size) {
    out << global_lead_time<<'\t'<<size<<"\n";
    if (out.is_open()) {
        for (int iterator = 0; iterator < size; iterator++) {
            out << array[iterator] << " ";
        }
    }
}

void ofstreamArrayJSON(ofstream& out, int* array, int size) {
    out << "{\n" << "\"sort-size\": " << size << ",\n";
    out << "\"sort-time\": " << global_lead_time << ",\n";
    out << "\"sorted-array\": [ ";
    for (int i = 0; i < size-1; i++) {
        out << array[i] << ", ";
    }
    out << array[size - 1] << "],";
}

bool isExtension(char* word,const char* extension) {
    if (strlen(word) > strlen(extension)) {
        for (int i = strlen(word) - strlen(extension), j = 0; i < strlen(word); i++, j++)
            if (word[i] != extension[j])
                return false;
        return true;
    }
    else
        return false;
}

int generateArraySize() {
    int size = 0;
    cout << "Введите размерность генерируемого массива\n";
    cin >> size;
    return size;
}

int generateArrayType() {
    cout << "Выберите какой массив вы хотите сгенерировать\n"
        "1-Рандомный\n2-Рандомный на правую половину\n"
        "3-Рандомный на левую половину\n4-Массив отсортированный в обратном подярке\n";
    int type_generate_massive = 0;
    cin >> type_generate_massive;
    return type_generate_massive;
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
    global_lead_time = time_end - time_begin;
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
    global_lead_time = time_end - time_begin;
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
    global_lead_time = time_end - time_begin;
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
        delete[] L;
        delete[] R;
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
    delete[] left_array;
    delete[] right_array;
  }
    
}

int sortType() {
    cout << "Выберите тип сортировки:\n1-Сортировка выбором\n2-Сортировка пузырьком\n"
        "3-Сортировка вставками\n4-Сортировка слиянием\n5-Быстрая сортировка\n6-Стандартная сортировка\n";
    int type_sorted = 0;
    cin >> type_sorted;
    return type_sorted;
}

void generateArray(int* array, int size, int generate_type)
{
    ofstream out_parent;
    out_parent.open("parentArray.txt");
    switch (generate_type) {
    case 1: {
        generateSimpleArray(array, size);
        break;
    }
    case 2: {
        generateSimpleArray(array, size);
        selectionSort(array, size / 2, 0, false);
        break;
    }
    case 3: {
        generateSimpleArray(array, size);
        selectionSort(array, size, size / 2, false);
        break;
    }
    case 4: {
        generateSimpleArray(array, size);
        selectionSort(array, size, 0, false);
        reverse(array, size);
        break;
    }
    }
    ofstreamArrayTXT(out_parent, array, size);
}

int comparator(const void* x1, const void* x2)   // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

char* selfTest(int* array, int size) {
    static char OK[]="OK";
    static char NOTOK[]= "NOT OK";
    for (int i = 0; i < size-1; i++)
    {
        if (array[i] < array[i + 1])
            i++;
        else
            return NOTOK;
    }
    return OK;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    cout <<"argc:" << argc << endl << "argv:";
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }

    options o(argc, argv);

    if (o.isKey("--help")) {

        cout << "ОСНОВНЫЕ КОМАНДЫ:\n" <<
            "--help\tвыводит информацию о всех командах и их аргументах.\n" <<
            "--input <имя_файла.txt>\tзагружает исходный массив из файла для дальнейшей сортировки\n" <<
            "--output <имя_файла.txt>\tсохраняет отсортированный массив в файл\n" <<
            "--generate-array\tгенерирует исходный массив для дальнейшей сортировки\n" <<
            "--generate-array-type <число>\tвыбор типа генерируемого массива:\n\t\t\t\t" <<
            "1 - рандомный\n\t\t\t\t2 - рандомный на правую половину\n\t\t\t\t"
            "3-рандомный на левую половину\n\t\t\t\t4-массив отсортированный в обратном подярке\n" <<
            "--generate-array-size <число>\tвыбор размера генерируемого массива.\n" <<
            "--sort-type <число>\tвыбор типа сортировки массива:\n\t\t\t\t" <<
            "1-сортировка выбором\n\t\t\t\t2-сортировка пузырьком\n\t\t\t\t"
            "3-сортировка вставками\n\t\t\t\t4-сортировка слиянием\n\t\t\t\t5-быстрая сортировка\n"<<
            "--json\t сохраняет отсортированный массив с расширением .json\n";
        return 0;
    }
    
    int size = 100;//по умолчанию-размер массива 100
    int generate_type = 1;//по умолчанию- рандомный массив
    int sort_type = 0;
   
    if (o.isKey("--generate-array-size")) {
        if (!o.isKey("--input")) {
            size = atoi(o.option[o.whatTheNumberKey("--generate-array-size")]);
            if (size < 0) {
                cout << "Задана отрицательная размерность массива\n";
                return -1;
            }
    }
    }
    

     if (o.isKey("--input")) {
         if (!o.isKey("--generate-array-size")) {

             ifstream sizeNum(o.option[o.whatTheNumberKey("--imput")]);
             size = 0;
             while (sizeNum.eof())
                 size++;
             
         }
    }

     if (o.isKey("--generate-array")) {
         if (!o.isKey("--generate-array-size") && !o.isKey("--input")) {
             size = generateArraySize();
             if (size < 0) {
                 cout << "Задана отрицательная размерность массива\n";
                 return -1;
             }
         }
     }

     int* array = new int[size];

     if (o.isKey("--input")) {
         if (!o.isKey("--generate-array-size")) {
             ifstream in(o.option[o.whatTheNumberKey("--imput")]);
             if (in.is_open()) {
                 for (int i = 0; i < size; i++)
                     in >> array[i];
             }
         }
     }

     if (o.isKey("--generate-array")) {
         if (!o.isKey("--generate-array-type")) {
             generate_type = generateArrayType();
             if (generate_type < 1 || generate_type>4) {
                 cout << "Ошибка. Нет такого номера для выбора генерации массива.\n";
                 return -1;
             }
                 
         }
         generateArray(array, size, generate_type);
         if (!o.isKey("--sort-type"))
             sort_type = sortType();
     }

    if (o.isKey("--generate-array-type")) {
        if (!o.isKey("--input"))
            generate_type =atoi( o.option[o.whatTheNumberKey("--generate-array-type")]);
        else
        {
            cout << "Нельзя сгенерировать тип экспортированного массива\n";
            return -1;
        }
    }
    
   
    if (o.isKey("--sort-type")) {
        sort_type = atoi(o.option[o.whatTheNumberKey("--sort-type")]);
    }
    cout << endl;
    
    if (!o.isKey("--input") && !o.isKey("--generate-array")) {
        cout << "Генерация массива по умолчанию:\n";
        if (!o.isKey("--generate-array-size"))
            cout << "Размер по умолчанию: " << size <<endl;
        if(!o.isKey("--generate-array-type"))
            cout << "Тип генерации по умолчанию: Рандомный массив\n";
        generateArray(array, size, generate_type);
    }
    if (!o.isKey("--sort-type")&&sort_type==0) {
        cout << "Сортировка по умолчанию: Сортировка выбором\n";
        sort_type = 1;//по умолчанию-сортировка выбором 1
        selectionSort(array, size, 0, true);
    }
    else
        switch (sort_type) {
            case 1: {
                selectionSort(array, size, 0, true);                
                break;
            }
            case 2: {
                bubbleSort(array, size);
                break;
            }
            case 3: {
                instertionSort(array, size);
                break;
            }
            case 4: {
                double time_begin = clock();
                mergeSort(array, size);
                double time_end = clock();
                cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
                global_lead_time = time_end - time_begin;
                break;
            }
            case 5: {
                double time_begin = clock();
                quickSort(array, size);
                double time_end = clock();
                cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
                global_lead_time = time_end - time_begin;
                break;
            }
            case 6: {
                double time_begin = clock();
                std::qsort(&array, size, sizeof(int), comparator);
                double time_end = clock();
                cout << "Время выполнения сортировки " << time_end - time_begin << " мс\n";
                global_lead_time = time_end - time_begin;
                break;
            }
            default: {
                cout << "Ошибка. Нет такого номера для выбора сортировки массива.\n";
                return -1;
            }
            }
    

    char* test = selfTest(array, size);
        if (o.isKey("--output")) {
            
            ofstream sorted(o.option[o.whatTheNumberKey("--output")]);

            if (o.isKey("--json") || isExtension(o.option[o.whatTheNumberKey("--output")], ".json")) {
                ofstreamArrayJSON(sorted, array, size);
                sorted << "\n\"self-test: " << test << "\n}";
            }
            else {
                ofstreamArrayTXT(sorted, array, size);
                sorted << "\n" << test << "\n";
            }
            
            if (sorted.good())
                cout << "Запись прошла успешно\n";
            else {
                cout << "Произошла ошибка записи\n";
                return -1;
            }
            
        }
        else {
            cout << "Сохранение по умолчанию: SortedArray.txt\n";
            ofstream out_child("SortedArray.txt");
            ofstreamArrayTXT(out_child, array, size);
            if (out_child.good())
                cout << "Запись по умолчанию прошла успешно\n";
            else {
                cout << "Произошла ошибка записи по умолчанию\n";
                return -1;
            }
        }
        delete[] array;
        return 0;
}

