# Formal_languages_2022
## Алгоритм решения (задача 10)
Для каждого состояния будем хранить длину требуемого суффикса и длину слова, то есть если у нас на входе 'a', а требуемый суффикс должен быть по 'b', то длина суффикса будет равна 0, а длина слова 1. Аналогично для остальных простых состояний. Теперь перейдём к операторам. Если нам поступил оператор '+', то мы просто объединяем все возможные состояния. Если же на вход попадает оператор '*', то нам нужно добавить в состояния пустое , то есть пару {0, 0}, а также если есть пара {x1, x2}, где x1==x2, то также добавляем пары {x1 * l, x2 * l}, l= 2, 3,.... до тех пор, пока произведение $x1 \cdot l$ не превысит k. Ну и  для последнего случая - '.' - придется рассмотреть все пары состояний L1 и L2: если среди пар одно пустое, то есть {0, 0}, то просто добавляем второе, если же оба не пустые, то если длина суффикса второго слова совпадает с длиной самого слова, то добавляем {len_suf_1 + len_2, len_1 + len_2}, иначе добавляем {len_suf_2, len_1 + len_2}. После просто смотрим все состояния, в которых длина суффикса равна k и берем наименьшую длину, если же такой длины суффикса нет, пишем INF.

#### Запуск
Склонируйте репозиторий на свой компьютер, после чего выполните следующие инструкции
```shell script
git checkout prac1
mkdir build
cd build
cmake ..
cmake --build .
```
После этого для запуска используйте ./formal_run, для запуска тестов ./test/runTests


### Ввод
Пользователь вводит через пробел: регулярное выражение в обратной польской нотации; букву, суффикс которой надо найти; число - длина суффикса.
### Вывод
Пользователь получает ответ в виде числа, "INF" или строки, которая оповещает о неправильных символах или неправильно написаной обратной польской нотации.
