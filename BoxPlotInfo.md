### Постановка задачи: ###

В задании необходимо релазовать два класса: `Timer`, для замера времени выполнения участка кода, и `BoxPlot`, для вывода необходимой информации в формате диаграммы размаха.

1) Реализовать класс `Timer`, который содержит метод `reset` обнуляющий значение таймера и методы, возвращающие прошедшее время с последнего сбрасывания таймера.
```cpp
#include <chrono>
#include <iostream>

long fibonacci(unsigned n) {
  return n < 2 ? n : fibonacci(n-1) + fibonacci(n-2);
}

template <typename T>
class Timer {
public:
  static void reset();
  //static T elapsed_nanoseconds();
  //static T elapsed_microseconds();
  //static T elapsed_milliseconds();
  static T elapsed_seconds();
  //static T elapsed_minutes();
private:
  typedef std::chrono::high_resolution_clock clock_;
  static std::chrono::time_point<std::chrono::high_resolution_clock> beg_;
};

template <typename T>
void Timer<T>::reset() {
  beg_ = clock_::now();
}

template <typename T>
T Timer<T>::elapsed_seconds() {
	return std::chrono::duration_cast<std::chrono::duration<T, std::ratio<1> >>(clock_::now() - beg_).count();
}

template<typename T>
std::chrono::time_point<std::chrono::high_resolution_clock> Timer<T>::beg_ = std::chrono::high_resolution_clock::now();

int main() {
  Timer<double>::reset();
  std::cout << "f(42) = " << fibonacci(42) << '\n';
  std::cout << Timer<double>::elapsed_seconds() << std::endl;
}
//f(42) = 267914296
//0.583735
```


2) Создать класс `BoxPlot`, который будет содержать указанные в примере ниже методы. Методы для произвольного непустого набора вещественных (не обязательно) чисел демонстрирует значения [диаграммы размаха](https://ru.wikipedia.org/wiki/%D0%AF%D1%89%D0%B8%D0%BA_%D1%81_%D1%83%D1%81%D0%B0%D0%BC%D0%B8), а также [среднего](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%B5_%D0%B0%D1%80%D0%B8%D1%84%D0%BC%D0%B5%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5) и [среднеквадратичного отклонения](https://ru.wikipedia.org/wiki/%D0%A1%D1%80%D0%B5%D0%B4%D0%BD%D0%B5%D0%BA%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%BE%D0%B5_%D0%BE%D1%82%D0%BA%D0%BB%D0%BE%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5). 

Аргумент каждого метода -- список значений, через `std::vector`. 

Каждый метод возвращает одно из следующих значений: среднее, медиана и стандартное отклонение.

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
int main() {
  std::vector<double> x = {0.0855298042e+00,1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00};
  std::cout.precision(2);
  std::cout << std::scientific << "min:    " <<  BoxPlot::min(x) << std::endl;
  std::cout << std::scientific << "lq:     " <<  BoxPlot::lq(x) << std::endl;
  std::cout << std::scientific << "median: " <<  BoxPlot::median(x) << std::endl;
  std::cout << std::scientific << "mean:   " <<  BoxPlot::mean(x) << std::endl;
  std::cout << std::scientific << "stddev: " <<  BoxPlot::stddev(x) << std::endl;
  std::cout << std::scientific << "uq:     " <<  BoxPlot::uq(x) << std::endl;
  std::cout << std::scientific << "max:    " <<  BoxPlot::max(x) << std::endl;
  auto outs = BoxPlot::out(x);
  std::cout << "out: "
  for(const auto & it : out) 
    std::cout << std::scientific << it << std::endl;
  std::cout << std::endl;
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

1. Реализовать с использованием алгоритмов и функций STL, а также лябмда-выражений (`std::accumulate` и т.п.).
2. Требований к вычислительной сложности для получения значений нет.

### Без отчета
