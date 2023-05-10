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

1. Англоязычный файл с текстом большого размера (порядка 300 мегабайт).
2. Файл генома человека 400 мегабайт.

Все файлы представлены в корне репозитория. 

### Требуемые детали проектирования и реализации приложения

1. Проект разбит на несколько файлов (.cpp/.h).
2. Обработка исключительных ситуаций (try/catch).
3. Параллельность кодирования/декодирования, где возможно (async/future/OpenMP/Boost/etc).
4. *Загрузка и обработка большого файла кусками для уменьшения занимаемой приложением памяти.


### LZ77 

[example1](https://www.researchgate.net/publication/322296027/figure/fig4/AS:579960579346433@1515284785811/An-example-of-LZ77-encoding.png)

```

1. bbbcccacab, 6
2. aadadadcdc, 6
3. cccdddcaad, 6
4. aaaacbcbbc, 6
5. aabbcccbbc, 4
6. bbaaabbcca, 4
7. bbcbacaaab, 4
8. cccbbabaac, 4
9. ddbbbccaba, 6
10. bbbcbacaaa, 6
11. ddccdcadca, 6
12. ccacbaacbb, 6
13. ddaaddabbb, 6
14. bbbacccaab, 4
15. bbccdbcdcb, 6


1. <0,0,b> <1,1,c> <2,3,a> <1,2,c> 
2. <0,0,c> <1,2,b> <0,0,a> <2,4,b> 
3. <0,0,b> <1,2,c> <1,2,a> <1,1,c> <2,0,a> 
4. <0,0,a> <1,2,c> <1,1,b> <1,2,c> <2,0,b> 
5. <0,0,a> <1,1,b> <2,2,c> <4,2,b> <4,0,c> 
6. <0,0,c> <1,2,a> <2,2,a> <0,0,b> <2,1,b> 
7. <0,0,b> <1,1,a> <1,1,b> <3,3,c> <1,0,c> 
8. <0,0,c> <1,2,b> <0,0,a> <2,1,b> <5,2,a> 
9. <0,0,a> <1,2,b> <1,1,a> <3,2,c> <1,0,c> 
10. <0,0,a> <1,2,c> <0,0,b> <1,1,c> <1,2,a> 
11. <0,0,b> <1,1,a> <1,1,c> <2,2,b> <4,1,a> 
12. <0,0,b> <1,3,c> <0,0,a> <1,2,c> <1,0,c> 
13. <0,0,a> <1,1,b> <1,1,c> <2,2,c> <1,1,a> 
14. <0,0,c> <1,2,d> <1,1,a> <2,2,c> <3,0,d> 
15. <0,0,b> <1,1,a> <2,1,c> <3,3,c> <4,0,a> 

```

### LZ78

```
1. ccbcbaaabb
2. abaabccbcb
3. abacbcaccb
4. cbbcaacaca
5. bddcdcdaba
6. bacabcacac
7. bcbcbcaaab
8. bbcaacbccb
9. ccbcbbacab
10. bbdcbddccb
11. babdbdbada
12. ccdcbdcbdd
13. bbcbcaaddd
14. bbaacabbac
15. bdabdacacc
 
1. 0 c, 1 a, 1 b, 0 b, 4 b, 1 a 
2. 0 b, 0 c, 2 d, 1 a, 3 b, 0 a 
3. 0 c, 0 a, 2 d, 3 b, 2 c, 0 b 
4. 0 b, 1 c, 0 a, 3 c, 1 a, 1 a 
5. 0 d, 0 a, 0 b, 3 d, 2 d, 4 b 
6. 0 b, 1 c, 0 c, 3 a, 0 a, 2 a 
7. 0 c, 0 d, 1 d, 0 b, 3 b, 2 c 
8. 0 b, 0 a, 1 d, 2 a, 1 b, 2 d 
9. 0 b, 0 c, 2 b, 1 a, 2 a, 2 a 
10. 0 c, 0 a, 1 b, 2 b, 1 a, 1 b 
11. 0 c, 0 a, 1 a, 2 b, 0 b, 3 b 
12. 0 a, 0 c, 2 b, 0 b, 1 c, 5 b 
13. 0 d, 0 c, 0 a, 3 d, 3 b, 5 c 
14. 0 c, 0 a, 2 b, 1 a, 0 b, 4 c 
15. 0 a, 0 b, 0 c, 1 c, 4 c, 1 b 
```

### LZW
```
1) bacccaccca	
2) abcabbcbcb	
3) abbbabcabc	
4) acbcbcbccb	
5) cababbabab	
6) acaccabacc	
7) abbbabcbba	
8) bcccbcaccb	
9) cccbaccbac	
10) bbbacacbba	
11) acaccaaccb	
12) babababcab	
13) baaacccaac	
14) bbbcccabbc	

1) 		0, 1, 2, 3, 6, 3
2) 		2, 0, 3, 1, 5, 6
3) 		1, 3, 0, 2, 4, 3
4) 		0, 1, 2, 5, 4, 7
5) 		0, 2, 4, 1, 5, 4
6) 		0, 2, 3, 5, 1, 4
7) 		1, 0, 3, 2, 3, 7
8) 		0, 2, 3, 5, 1, 3
9) 		1, 0, 2, 4, 3, 6
10) 		2, 0, 1, 4, 6, 5
11) 		0, 1, 3, 2, 6, 5
12) 		1, 0, 4, 2, 3, 5
13) 		1, 0, 3, 3, 2, 6
14) 		2, 1, 0, 3, 6, 4
15) 		1, 2, 3, 3, 0, 5
16) 		1, 2, 4, 0, 3, 7
```
