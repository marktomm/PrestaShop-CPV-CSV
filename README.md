!!WARN: names get a bit mixed up when dealing with xxxxxxx0 and xxxxxxxx codes

Get CPV codes into Prestashop Categories

Works like this atm:
 
1.The cpv code list in csv must be in the following format:
 
03000000;Сельскохозяйственные, рыбные продукты, продукция ферм, лесного хозяйства и сопутствующая продукция

03100000;Садоводческая и сельскохозяйственная продукция

03110000;Сельскохозяйственная, садоводческая и садовая продукция для продажи

03111000;Семена

03111100;Бобы сои

03111200;Арахис

03111300;Семена подсолнечника

03111400;Семена хлопка

03111500;Семена кунжута

03111600;Семена горчицы

03111700;Семена овощей

03111800;Семена фруктов

03111900;Семена цветов

03112000;Необработанный табак

03113000;Растения, используемые при производстве сахара

03113100;Сахарная свекла

03113200;Сахарный тростник

03114000;Сено и фуражные культуры

03114100;Сено

03114200;Фуражные культуры

03115000;Растительное сырье

03115100;Растительное сырье, предназначенное для текстильной промышленности

03115110;Хлопок

03115120;Джут

03115130;Лен
...

2.divide it with awk.
codes:
$ awk -F ";" '{print $1"}' file
desc:
$ awk -F ";" '{print $2"}' file
in to two separate files

3.Substitute the file name in this code

4.Compile:
g++ --std=c++0x cpp_cpv_to_presta.cpp -o cpp_cpv_to_presta


5.Run

output will be:
9407?1?"98330000"?"98300000"?Услуги в области поддержания физической формы

9408?1?"98331000"?"98330000"?Услуги в области турецких бань

9409?1?"98332000"?"98330000"?Услуги в области термальных курортов

9410?1?"98333000"?"98330000"?Услуги массажа

9411?1?"98334000"?"98330000"?Услуги в области физического состояния

9412?1?"98336000"?"98330000"?Услуги в области тренировок  физических упражнений или аэробики

9413?1?"98340000"?"98300000"?Услуги в области проживания и офисные услуги

9414?1?"98341000"?"98340000"?Услуги в области проживания

9415?1?"98341100"?"98341000"?Услуги по управлению жилыми площадями
...

In presta:

6.In AdminImportController:

make small change in categoryImport method after

AdminImportController::arrayWalk($info, array('AdminImportController', 'fillInfo'), $category);

```
            // if (isset($category->parent) && is_numeric($category->parent)) {
            //     if (isset($cat_moved[$category->parent])) {
            //         $category->parent = $cat_moved[$category->parent];
            //     }
            //     $category->id_parent = $category->parent;
            // } else
            
            // if (isset($category->parent) && is_string($category->parent)) {
                if (isset($category->parent)) {

```

or override the function

(and probably get_best_path method too, bc its private)

7.In import

Use ? as delimiter (cpv names use ; in desc text)

Columns are
ID, Active, Name, Parent Category, Description

Don't forget to check 'Lines to skip'
