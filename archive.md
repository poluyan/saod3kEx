## Разработка приложения для кодирования и декодирования текстовых ASCII-файлов

### Постановка задачи

Требуется реализовать архиватор для упаковки текстового ASCII файла в файл-архив с поддержкой распаковки ранее созданных архивов. 
ASCII таблица - 128 символов, 8-битная кодировка, только положительные значения символов.
Кодирование/декодирование в архиваторе должно быть выполнено с использованием одного из перечисленных методов:
1. Универсальный код Фибоначчи
2. Алгоритм Лемпеля — Зива — Велча
3. Метод Лемпеля — Зива LZ77
4. Метод Лемпеля — Зива LZ78
5. Рекурсивный код Элиаса
6. Алгоритм Хаффмана


### Пример с bitset
```cpp
#include <bitset>
#include <iostream>
#include <string>
#include <fstream>
int main() {
    std::string bits = "10010101";
    std::bitset<8> bs;
    for(int i = 0; i < 8; i++)
        bs[7-i] = bits[i] == '0' ? 0 : 1;
    std::cout << bs.to_string() << std::endl;
    std::cout << bits << std::endl;
    
    std::ofstream fOut("out.zippa", std::ios::binary);
    fOut << static_cast<char>(bs.to_ulong());
    fOut.close();
    
    std::ifstream fIn("out.zippa", std::ios::binary);
    char ch;
    fIn >> ch;
    fIn.close();
    
    std::bitset<8> bsin(ch);
    std::cout << bsin.to_string() << std::endl;
}
```


### Результат работы

Программа-архиватор, консольное приложение, реализованное на языке C++, позволяющее создавать файл-архив для указанного текстового ASCII файла. 
Приложение должно поддерживать распаковку ранее созданных архивов в идентичные текстовые файлы.  
Минимальный пользовательский функционал должен предоставлять краткую инструкцию разъясняющую, как использовать данное приложение и 
показывать степень сжатия исходного файла. Функционал может выглядеть следующим образом:
```
$ mycompressor.exe -h
This is Elias gamma coding compressor for ASCII text files.
General options:
  -c [ --compress ]          Compress file (-c init.txt output.compressed)
  -d [ --decompress ]        Decompress file (-d output.compressed check.txt)
  -h [ --help ]              Show help

$ mycompressor.exe -c init.txt output.compressed
Done!
Compression ratio: 1185237 bytes / 813211 bytes = 1.4
Compression time: 0.352 sec

$ mycompressor.exe -d input.compressed output.txt
Done!
Decompression time: 0.876 sec

$ mycompressor.exe -d test1.compressed output1.txt
Fail! It is not a .compressed archive!

$ mycompressor.exe -d test2.compressed output2.txt
Fail! The archive is corrupt!

$ mycompressor.exe -d test2.compressed
Fail! The output file must be specified!
```
### Выполнить поверку и проанализировать результат на примере сжатия файлов с различным содержанием

1. [Файл всех статей википедии на simple english.](https://github.com/poluyan/saod3kEx/blob/main/engwiki_ascii.7z)
2. [Файл генома человека 400 мегабайт.](https://github.com/poluyan/saod3kEx/blob/main/400mb.fa.7z)
3. [Файл генома человека 3005 мегабайт.](https://drive.google.com/file/d/1VqfGVzhiS-ldPFuDFus77i_xxAIA4OGH/view?usp=sharing)

Все три файла являются ASCII текстами. 

### Требуемые детали проектирования и реализации приложения

1. Проект разбит на несколько файлов (.cpp/.h).
2. Обработка исключительных ситуаций (try/catch).
3. Параллельность кодирования/декодирования, где возможно (async/future/OpenMP/Boost/etc).
4. Загрузка и обработка большого файла кусками для уменьшения занимаемой приложением памяти.
5. Возможность архивировать каталоги с файлами, включая все подкаталоги.
