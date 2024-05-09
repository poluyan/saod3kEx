## Для односвязного списка

```cpp
void print_lst(const LList<char> &l) {
  // вывод списка на экран с помощью l[i]
}
int main() {
  LList<char> lst; // ваш список
  std::cout << std::boolalpha << lst.empty() << std::endl;
	
  for(int i = 0; i < 5; i++)
    lst.push_back(char('a' + i));
	
  print_lst(lst);
	
  for(int i = 0; i < 5; i++) 
    lst.insert(0, char('z' - i));
	
  print_lst(lst);
	
  for(size_t i = 0; i != lst.size(); i++)
    lst[i] = char('a' + i);
	
  print_lst(lst);
	
  lst.pop_back();
  lst.pop_front();

  print_lst(lst);
	
  lst.remove_at(5);
  lst.insert(3, 'o');
	
  print_lst(lst);
	
  lst.clear();
	
  lst.push_back('q');
  lst.push_back('w');
	
  std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;
}  // деструктор освободит оставшиеся узлы

// // Вывод приложения
// true
// a -> b -> c -> d -> e
// v -> w -> x -> y -> z -> a -> b -> c -> d -> e
// a -> b -> c -> d -> e -> f -> g -> h -> i -> j
// b -> c -> d -> e -> f -> g -> h -> i
// b -> c -> d -> o -> e -> f -> h -> i
// 2 false

// // Для проверки итераторов
// LList<int> l = { 3, 5, 2, 7, 8 };
// int s = 0;
// for (auto &i : l) s += i*10;
// auto lambda = [](int a, int b) { return a + b*10; };
// std::cout << s << '\t' << std::accumulate(l.begin(), l.end(), 0, lambda) << '\n';//250
```

