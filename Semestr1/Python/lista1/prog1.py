# -*- coding: utf-8 -*-

# ten brzydki komentarz powyżej umożliwia kodowanie używanie polskich znaków (kodowanie utf-8)
# konieczne w pythonie 2.x
# Kodowanie windowsowe nazywa się cp1250
# W Pythonie 3.x należy dopisać nawiasy do instrukcji print

# po znaku "#" rozpoczyna się komentarz

from math import sqrt # pierwiastek kwadratowy


def potega(a,n):
   wynik = 1  # zmienna lokalna
   for i in range(n):
      wynik = wynik * a   # albo: wynik *= a
   return wynik
   
def kwadrat(n):
   for i in range(n):
      for j in range(n):   # pętla w pętli
         print "*",
      print
      
def kwadrat2(n):
   for i in range(n):
      print n * "#"      
  
# wcześniej były definicje, poniżej jest część która się wykonuje

      
for i in range(10):
   print i,2 ** i, potega(2,i), sqrt(i)  # drukujemy kolejne liczby wraz z kolejnymi potęgami dwójki oraz kolejnymi pierwiastkami                  
   
print

for i in range(5):
   print "Przebieg:",i
   print 20 * "-"
   if i % 2 == 0:   # parzysta
      kwadrat(3+2*i)
   else:  # czyli nieparzysta
      kwadrat2(3+i)
   print    # pusty wiersz   
         
     
   
