import data_worker as dt
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import random

def funct(x, A, B, C, D, E):
       return A/(x + D) + (B/((x+E)**0.5)) + C

NUMBER = 200

styles=['-','--','-.',':','']

#books = dt.get_all_books()
#books = dt.get_books_by("Толстой Лев Николаевич", prop='author')
books = ["Толстой Лев Николаевич#Война и мир#1", "Толстой Лев Николаевич#Война и мир#2",
         "Толстой Лев Николаевич#Война и мир#3", "Толстой Лев Николаевич#Война и мир#4",
         "Толстой Лев Николаевич#Анна Каренина", "Тургенев Иван Сергеевич#Отцы и дети",
         "Достоевский Федор Михайлович#Преступление и наказание", "Неизвестный автор#Война и мир"]
for i in books:
       toConsider = dt.get_words(i)[:NUMBER]
       C = sum(list(map(lambda t: t[1], dt.get_words(i))))
       print(C)
       y = np.array(list(map(lambda t: t[1], toConsider)))

       #C = sum(y)

       y = y/C

       #plt.plot(y)
       #plt.plot(np.full(NUMBER,1))
       #result_ = np.array([5281.0, -14394.0, -2.5, 70.0, 4.5])*y[0]/735.0
       try:
              result, _ =curve_fit(funct, np.arange(NUMBER) + 1, y,
                            p0 = [1000, -1, -1, 1, 1],
                            bounds = ([-np.inf,-np.inf,-np.inf,0,0],np.inf),
                            maxfev = 10000)
       except:
              print('ERR',i)
              result, _ =curve_fit(funct, np.arange(NUMBER) + 1, y,
                            p0 = [1, 1, 1, 1, 1],
                            bounds = ([-np.inf,-np.inf,-np.inf,0,0],np.inf),
                            maxfev = 10000)
       #plt.plot(np.arange(NUMBER))
       #result = [1384, -5257, 22.5, 3.5, 3.5]


       lab = i + ' ; '+ str(dt.get_val(i, 'year'))
       
       if i == "Неизвестный автор#Война и мир":
              plt.plot(funct(np.arange(NUMBER) + 1, *result),random.choice(styles), label = lab, color = 'black')
       else:
              if "Толстой Лев Николаевич#Война и мир" in i:
                     plt.plot(funct(np.arange(NUMBER) + 1, *result),random.choice(styles), label = lab, color = 'red')
              else:
                     plt.plot(funct(np.arange(NUMBER) + 1, *result),random.choice(styles), label = lab)
       #plt.plot(y, label=i+'-real')
       #print(list(map(lambda x:float(x), result)))
plt.legend(loc='upper right')
plt.show()
#words = dt.get_words()

