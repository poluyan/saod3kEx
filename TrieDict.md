## Префиксное дерево для решения задачи подсчета слов

### Постановка задачи

Имеется большой ASCII файл (дамп wiki статьей на simple english), который рассматривается как одна строка и представлен в объекте типа std::string. Рассматривается задача подсчета вхождения каждого слова в строке, т.е. составление ассоциативного котнейнера вида (слово -> число вхождений слова в строку) с помощью префиксного дерева. Под словом подразумевается последовательность, которая содержит символы [a-zA-Z] и апостроф (порядок символов не важен, как и количество). Префиксное дерево необходимо оформить как контейнер с методами (insert, find, size, можно некоторые методы определить операторами). Требуется реализовать через class, использование шаблонов не требуется. При реализации префискного дерева необходимо использовать умные указатели. После реализации требуется сравнить время формирования словаря, реализованного с помощью дерева, с хеш-таблицей (пример ниже). Результаты сравнения времени необходимо с помощью ранее реализованной вами функции boxplot, замерив несколько раз время формирования словаря. Число вхождения каждого слова в вашем словаре и общее число уникальных слов (dict.size()) должны быть идентичны значениям в хеш-таблице в примере. Т.е. число вхождений, например, слова the в вашем словаре и в хеш-таблице будут одинаковые при идентичном принципе определения слова при проходе по строке. Проверку работы вашего словаря требуется оформить в функции с аналогичной сигнатурой.

```cpp
void triedict(const std::string &text, std::string word) { }
```

### Пример префиксного дерева

Интерактивно: https://www.cs.usfca.edu/~galles/visualization/Trie.html

Пример построения дерева для строки `are they the most fun and these are a fun`. Количество вхождений: are 2, they 1, the 1, most 1, fun 2, and 1, these 1, a 1. В каждом узле дерева храниться символ, указатели на дочерние узлы, 
маркер конца слова и счетчик количества вхождений слова. Маркер конца слова можете связать со счетчиком.

<img src="https://github.com/poluyan/saod3kEx/blob/main/saod_trie.png" width="500" />

### Подсчет вхождения слова

Слово `wiki` встречается 491 раз в файле `engwiki_ascii.txt`.
```
$ file engwiki_ascii.txt 
engwiki_ascii.txt: ASCII text, with very long lines (6231)
$ grep -o '\<wiki\>' engwiki_ascii.txt | wc -l
491
```
Для некоторых слов подсчет через `grep` может отличаться, но незначительно. Файл `engwiki_ascii.zip` лежит в корне репозитория.

```cpp
import std;

void umap(const std::string &text, std::string word)
{
  using namespace std;
  unordered_map<std::string, size_t> dict;
  string str = "";
  for(const auto & ch : text) // кроме последнего слова
  {
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
      str += ch;
    else if(str.size() > 0)
    {
      ++dict[str];
      str = "";
    }
  }
  cout << "\ndict size: " << dict.size() << endl;
  cout << word << ": " << dict[word] << endl;
}

struct hash_pair
{
  std::size_t operator()(const std::pair<const char*, size_t>& p) const
  {
    return std::hash<std::string_view> {}(std::string_view(p.first, p.second));
  }
};

struct equal_pair
{
  bool operator()(const std::pair<const char*, size_t>& lhs, const std::pair<const char*, size_t>& rhs) const
  {
    return std::strncmp(lhs.first, rhs.first, rhs.second) == 0;
  }
};

void umap_slice(const std::string &text, std::string word)
{
  using namespace std;
  std::unordered_map<std::pair<const char*, size_t>, size_t, hash_pair, equal_pair> dict;
  pair<const char*, size_t> p;
  for(size_t i = 0, j = 0; i < text.size(); i++) // кроме последнего слова
  {
    if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') || text[i] == '\'')
      ++j;
    else if(j > 0)
    {
      ++dict[ {text.c_str() + i - j, j}];
      j = 0;
    }
  }
  cout << "\ndict size: " << dict.size() << endl;
  cout << word << ": " << dict[ {word.c_str(), word.length()}] << endl;
}

int main()
{
  using namespace std;
  string text;
  ifstream fin("engwiki_ascii.txt", ios::binary);
  if(!fin.is_open())
  {
    cout << "not open!" << endl;
    return 0;
  }
  text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

  string word = "wiki"; // слово которое ищем
  auto time_one = chrono::high_resolution_clock::now();
  umap(text, word);
  auto time_two = chrono::high_resolution_clock::now();
  cout << "umap\t" << std::chrono::duration<double>(time_two - time_one) << endl;

  time_one = chrono::high_resolution_clock::now();
  umap_slice(text, word);
  time_two = chrono::high_resolution_clock::now();
  cout << "smap\t" << std::chrono::duration<double>(time_two - time_one) << endl;
}
//clang++ -std=c++23 -fmodules -O3 -march=native -stdlib=libc++ main.cpp
//dict size: 786353
//wiki: 491
//umap	3.07931s

//dict size: 786353
//wiki: 491
//smap	2.59205s

```

