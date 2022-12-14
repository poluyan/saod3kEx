### Постановка задачи: ###

Создание функции (шаблон) `std::tuple<double, double, double> boxinfo(arg1, arg2)`, которая для произвольного непустого набора вещественных (не обязательно) чисел демонстрирует значения [диаграммы размаха](https://ru.wikipedia.org/wiki/%D0%AF%D1%89%D0%B8%D0%BA_%D1%81_%D1%83%D1%81%D0%B0%D0%BC%D0%B8), а также [среднего](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%B5_%D0%B0%D1%80%D0%B8%D1%84%D0%BC%D0%B5%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5) и [среднеквадратичного отклонения](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5). 

Аргументы функции:

1. arg1: Массив вещественных значений, через `std::vector`. 

2. arg2: Количество знаков после запятой для каждого из значений. При выводе использовать экспоненциальную запись числа: [`std::scientific`](https://en.cppreference.com/w/cpp/io/manip/fixed).

Функция возвращает кортеж `std::tuple` состоящим из значений (последовательно): среднее, медиана и стандартное отклонение.

Вывод должен содержать.

1. min: Нижняя граница. Коэффициент 1.5.

2. lq: Нижний (первый) квартиль.

3. median: [Медиана](https://ru.wikipedia.org/wiki/%D0%9C%D0%B5%D0%B4%D0%B8%D0%B0%D0%BD%D0%B0_(%D1%81%D1%82%D0%B0%D1%82%D0%B8%D1%81%D1%82%D0%B8%D0%BA%D0%B0)). Если только два значения в выборке вывод среднего.

4. mean: [Среднее](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%B5_%D0%B0%D1%80%D0%B8%D1%84%D0%BC%D0%B5%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5).

5. stddev: [Среднеквадратическое отклонение
](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5)

6. uq: Верхний (третий) квартиль.

7. max: Верхняя граница. Коэффициент 1.5.

8. out: Выбросы (если есть).


### Результат работы: ###

```cpp
#include <iostream>
#include <vector>
// ..
int main()
{
  std::vector<double> x = {0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00};
  auto res = boxInfo(x, 2);
  std::cout << std::get<0>(res) << ' ' << std::get<1>(res) << ' ' << std::get<2>(res) << std::endl;
}
```
Результат:
```c
min:    6.58e-01
lq:     1.04e+00
median: 1.32e+00
mean:   1.23e+00
stddev: 4.61e-01
uq:     1.42e+00
max:    1.77e+00
out:    8.55e-02 2.08e+00 
1.23e+00 1.32e+00 4.61e-01
```
### Пример на R ###
 
[По этой ссылке](https://www.mycompiler.io/view/5XcsOEV). 
Либо используйте указанный ниже код в любом компиляторе (онлайн) R. **Внимание**, значения квартилей в вашем случае могут незначительно отличаться от представленных в R, но  медиана, среднее и стандартное отклонение должны совпасть.
```R
x <-c(0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00)
y <-c(2.1147451401e+00,1.5606760979e+00,1.0568326712e+00,1.1379202604e+00,8.5802090168e-01,1.2779158354e+00,1.1540910006e+00,2.2799887657e+00,1.5069425106e+00,2.4955313206e+00,1.1681622267e+00,1.3716301918e+00,1.3439905643e+00,8.5801953077e-01,1.5243546963e+00)

options(digits = 3, scipen = -6)

boxplot(x,y, ylim = c(0, 3))

A <- boxplot(x,y,range = 1.5, plot=FALSE)
mytable <- A$stats
colnames(mytable) <- A$names
rownames(mytable) <- c('min','lq','median','uq','max')
print(mytable)

cat("\nmean\n")
cat(mean(x), "\n")
cat(mean(y), "\n")

cat("\nstd dev\n")
cat(sd(x), "\n")
cat(sd(y), "\n")

cat("\noutliers\n")
outliers = boxplot(x,range = 1.5, plot=FALSE)$out
cat(outliers, "\n")
outliers = boxplot(y,range = 1.5, plot=FALSE)$out
cat(outliers, "\n")
```

### Приложение должно содержать: ###

1. Один или два файла (шаблон функции в можно заголовочный).
2. Несколько примеров работы функции.
3. Реализовать с использованием алгоритмов и функций STL, а также лябмда-выражений (`std::accumulate` и т.п.).
4. Требований к вычислительной сложности для получения значений нет.

### Без отчета
