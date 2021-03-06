# DifferentSorted
Программа сортирует или автоматически сгенерированные массивы типа выбранного пользователем, или массивы, которые были считаны из файла.
---
### Программа поддерживает работу через консоль и содердит ключи:

**--help** &emsp; Выводит информацию о доступных командах

**--generate-array**  &emsp;  Генерирует массива типа, размера и сортировки заданных в соответсующих ключах _--generate-array-type, --generate-array-size_ и _--sort-type_
                                       <br>Либо по умолчанию <br>(Тип генерируемого массива по умолчанию: _рандомный_; 
                                                          <br>Тип сортировки по умолчанию: _сортировка выбором_;
                                                          <br>Размер по умолчанию: _100_)
                                                          
**--generate-array-size _<число>_** &emsp;  Задает размер геренируемого массива

**--generate-array-type _<число>_** &emsp;  Задает тип генерируемого массива: <br>&emsp; 1-Рандомный
                                                                 <br>&emsp; 2-Рандомный на правую половину
                                                                 <br>&emsp; 3-Рандомный на левую половину
                                                                 <br>&emsp; 4-Отсортированный в обратном порядке
                                                                  
**--sort-type _<число>_** &emsp;  Задает вид сортировки сгенерированного или считанного массива: <br>&emsp; 1-Сортировка выбором
                                                                                          <br>&emsp; 2-Сортировка пузырьком
                                                                                          <br>&emsp; 3-Сортировка вставками
                                                                                          <br>&emsp; 4-Сортировка слиянием
                                                                                          <br>&emsp; 5-Быстрая сортировка
                                                                                          <br>&emsp; 6-Стандарная сортировка
                                                                                           
**--input _<имя_файла.txt>_** &emsp;  Загружает исходный массив из файла для дальнейшей сортировки  

**--output _<имя_файла.txt или имя_файла.json>_** &emsp;  Сохраняет отсортированный массив в файл

**--json** &emsp; Сохраняет отсортированный массив в файл с разрешением .json


---

В качестве определения вида О-нотации алгоритма сортировки массива была сделана puthon-программа, которая явно на графиках показала, 
что в пределах погрешности выбора генерируемого массива сортировки _выбором, пузырьком_ и _вставками_ имеют **О(n^2)**, 
а сортировки _слиянием, быстрая_ и _стандартная_ имеют **О(n)**, что можно увидеть на следующих графиках:

![1](https://user-images.githubusercontent.com/88945775/179029209-d64b88e5-aa48-4e65-b7a4-968d048d9309.png)
![2](https://user-images.githubusercontent.com/88945775/179029262-880c0406-9938-4e54-a7ff-ff5fb6776e38.png)
![3](https://user-images.githubusercontent.com/88945775/179029265-9268dc5b-2611-4f8a-95d9-14a4b94a3dc9.png)
![4](https://user-images.githubusercontent.com/88945775/179029269-8871d208-9e05-4350-977b-8336d01a73c3.png)
![5](https://user-images.githubusercontent.com/88945775/179029276-320cf720-a264-4d81-a727-f36f59b692ca.png)
![6](https://user-images.githubusercontent.com/88945775/179029279-0745fbb0-3696-40ca-8f40-b963df570cf1.png)
