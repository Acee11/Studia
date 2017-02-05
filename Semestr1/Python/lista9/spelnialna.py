def ciagi(N, dziedzina):
  if N == 0:
    return [[]]
  return [ [d] + reszta for d in dziedzina for reszta in ciagi(N-1, dziedzina)]
  
def wartosciowania(zmienne):
   C = ciagi(len(zmienne), [True, False])
   return [ dict(zip(zmienne,c)) for c in C ]

def zmienne(f):
 return set(f) - set('()+*! ')

def wartoscFormuly(f, w):
  f = f.replace('!',' not ').replace('*',' and ').replace('+',' or ')
  return eval(f, w)
       
def spelnialna(f):
   return any( [wartoscFormuly(f,w) for w in wartosciowania(zmienne(f))])
      
for f in ['p', 'a * !a', 'a + !a',  'p * q + !(p*q)']:
  print f, spelnialna(f)   
  
