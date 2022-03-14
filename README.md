# SD-proiect-1

In cadrul proiectului am implementat urmatorii algoritmi de sortare:
 1. Radix sort (base 10)
 2. Radix sort (base 2)
 3. Radix sort (base 8)
 4. Merge sort
 5. Shell sort
 6. Shell sort using Knuth's increments
 7. Quick sort simple
 8. Quick sort (pivot = first element)
 9. Quick sort (pivot = random)
10. Quick sort median of 3
11. TimSort

Pentru un n (numar de elemente) variabil si valMax( valoarea maxima din vector), atunci cand n se deplaseaza de la 10^3 la 10^7, cu pas 10^3, am obtinut urmatoarele:


![_N INTRE10^3 SI 10^6, PAS 10^3,MAXIM 10^4](https://user-images.githubusercontent.com/101597846/158264532-ce8742c8-b075-432d-805f-6741fc6d063c.png)

Putem clasifica, deci, algorimii de la cel mai rapid la cel mai lent in urmatoarea ordine:
 1. Quick sort simple
 2. STL sort
 3. Radix sort (base 10)
 4. Radix sort (base 2)
 5. Radix sort (base 2^16)
 6. Shell sort using Knuth's increments
 7. Merge sort
 8. Quick sort (pivot = first element)
 9. Quick sort (pivot = random)
10. Quick sort median of 3
11. Shell sort

Pentru un n constant si valMax variabil, atunci cand valMax se deplaseaza de la 10^3 la 10^7, cu pas 10^3, clasificand dupa acelasi criteriu ca mai sus, obtinem:

![TIMP EXECUTIE MEDIU MAXIM VARIABIL](https://user-images.githubusercontent.com/101597846/158264911-828dbd81-2828-4cfd-8911-c1578975297f.png)

 1. Radix sort (base 2^16)
 2. Quick sort simple
 3. Quick sort (pivot = first element)
 4. Radix sort (base 10)
 5. Quick sort median of 3
 6. Quick sort pivot random
 7. STL sort
 8. TimSort
 9. Shell sort using Knuth's imcrements
10. Shell sort
11. Merge sort
12. Radix sort (base 2)

RADIX SORT

Observatii:
Atat pentru valMax variabil, cat si pentru n variabil Radix sort base 2 este cel mai ineficient, iar Radix sort base 2^16 este cel mai rapid.

![RADIX SORT (1)](https://user-images.githubusercontent.com/101597846/158265217-9df40c0f-8ada-411f-897f-4d6b5321df22.png)
![RADIX SORT](https://user-images.githubusercontent.com/101597846/158265227-95dc66a1-ac4d-4896-b2b8-9600b718ed15.png)

SHELL SORT

Atat pentru n, cat si pentru valMax variabil, varianta de Shell sort care foloseste Knuth's increments este mai eficienta decat Shell sort-ul simplu.

![SHELL SORT](https://user-images.githubusercontent.com/101597846/158265245-0a0cf5f0-c238-4e76-a8f1-1a633b32f3ef.png)
![SHELL SORT (1)](https://user-images.githubusercontent.com/101597846/158265254-b0970a2d-5b15-4e4b-b674-f21bd2488459.png)


QUICK SORT

Ca si mai sus, putem face urmatoarea clasificare intre algoritmii de Quick sort(de la cel mai eficient la cel mai ineficient):
1. Quick sort simple
2. Quick sort pivot = first
3. Quick sort pivot random
4. Quick sort median of 3

![QUICK SORT](https://user-images.githubusercontent.com/101597846/158265264-7f7c256c-4794-4142-8777-4f4fbc62e784.png)
![QUICK SORT (1)](https://user-images.githubusercontent.com/101597846/158265278-e8d1e1d4-2b33-44dd-b7fc-d8adee0c266f.png)


