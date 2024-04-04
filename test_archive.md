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
1) bcbcabca		
2) babababc		
3) cccbaccb		
4) cabababa		
5) bcacacac		
6) cccabcca		
7) cacacacb		
8) abcbcbcb		
9) cccaccab		
10) cbacbcbc	
11) bbbcbbca	
12) ababcabc	
13) aaabaabc	
14) acccbccb	
15) bbbabbac	

1) 2, 3, 1, 4, 0
2) 0, 2, 3, 1, 5
3) 0, 3, 2, 1, 4
4) 2, 1, 3, 0, 5
5) 0, 1, 3, 5, 2
6) 1, 2, 3, 5, 0
7) 0, 3, 2, 4, 1
8) 1, 0, 2, 3, 6
9) 1, 3, 0, 2, 4
10) 2, 1, 0, 4, 6
11) 1, 3, 2, 0, 4
12) 1, 0, 2, 4, 6
13) 2, 1, 4, 0, 5
14) 1, 2, 0, 3, 6
15) 0, 2, 3, 5, 1
```
