## Многопоточность и задача поиска количества простых чисел в списке

<img src="https://github.com/poluyan/saod3kEx/blob/main/bl.png" width="1000" />

## Основная задача

Реализовать многопоточную версию подсчета простых чисел в списке с использованием одного примитива синхронизации (mutex/atomic/semaphore). Например, поместив все числа из списка в очередь для проверки на простоту или создав две переменные - для текущего индекса числа из массива и количества найденных простых чисел. Использование execution policy (`std::execution::par`) и parallel STL запрещается.

## Варианты заданий

1. mutex
2. atomic
3. semaphore

## Требования

Отчет в формате двух картинок, которые демонстрируют ускорение и эффективность вашей реализации по сравнению с блочной версией (можно exel или google таблицы).

```cpp
#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <vector>
#include <limits>
#include <unordered_map>
#include <numeric>
//#include <mutex>
//#include <queue>

typedef unsigned long long int bigint;

bool isPrime(bigint n)
{
  if (n <= 1)
    return false;
  for (bigint i = 2; i <= n / 2; i++)
    if (n % i == 0)
      return false;
  return true;
}

size_t single(const std::vector<bigint>& v)
{
  return std::count_if(v.begin(), v.end(), [](const auto &el)
  {
    return isPrime(el);
  });
}

// примитивная блочная реализация, каждый поток работает со своей частью списка
size_t block_way(const std::vector<bigint>& v, size_t n_threads)
{
  std::vector<size_t> results(n_threads);
  auto lambda = [&v, &results](size_t a, size_t b, size_t thread_id)
  {
    auto sum = std::count_if(v.begin() + a, v.begin() + b, [](const auto &el)
    {
      return isPrime(el);
    });
    results[thread_id] = sum;
  };

  std::vector<std::thread> threads(n_threads);
  int part_size = v.size() / n_threads, a = 0, b = 0;
  for(int thread_id = 0; thread_id != n_threads; thread_id++, a = b)
  {
    b = (thread_id == n_threads - 1) ? v.size() : a + part_size;
    threads[thread_id] = std::thread(lambda, a, b, thread_id);
  }

  for(auto& t : threads)
    t.join();

  return std::accumulate(results.begin(), results.end(), 0);
}

size_t mutex_way(const std::vector<bigint>& v, size_t n_threads)
{
  // ваша реализация
  return 0;
}

int main()
{
  // список, заполненный случайными натуральными числами
  std::vector<bigint> v(2520);
  std::mt19937_64 gen;
  gen.seed(1);
  std::uniform_int_distribution<bigint> dp(1, bigint(std::numeric_limits<int>::max()));
  for(auto & item : v)
    item = dp(gen);

  // однопоточная версия поиска простых чисел
  auto t1 = std::chrono::high_resolution_clock::now();
  auto nsingle = single(v);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto single_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  std::cout << 1 << '\t' << single_time << '\t' << single_time << '\t' << single_time << std::endl;

  // i - число потоков
  for(size_t i = 2; i <= 8; i += 1)
  {
    t1 = std::chrono::high_resolution_clock::now();
    auto nblock = block_way(v, i);
    t2 = std::chrono::high_resolution_clock::now();
    auto block_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    t1 = std::chrono::high_resolution_clock::now();
    auto nmutex = mutex_way(v, i);
    t2 = std::chrono::high_resolution_clock::now();
    auto mutex_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << i << '\t' << single_time << '\t' << block_time << '\t' << mutex_time << '\t' << nsingle << '\t' << nblock << '\t' << nmutex << std::endl;
  }
}
```
