import data_worker as dt
import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
import random

def funct(x, A, B, C, D, E):
       return A/(x + D) + (B/((x+E)**0.5)) + C


def sum_norm(x, A, B, C, D, E, F):
       return A*np.e**(B*(x+C)**2)+D*np.e**(E*(x+F)**2)

def alternative(x, A, B, C, D , E, F, G, H):
       return (A*x**5+B*x**4+C*x**3+D*x**2+E*x+F)*np.e**(x*H+G)

def norm(x, A, B, C):
       return A*np.e**(-B*(x+C)**2)

NUMBER = 700

styles=['-','--','-.',':','']

#books = dt.get_all_books()
#books = dt.get_books_by("Толстой Лев Николаевич", prop='author')
#books = ["Толстой Лев Николаевич#Война и мир#1",# "Толстой Лев Николаевич#Война и мир#2",
         #"Толстой Лев Николаевич#Война и мир#3", "Толстой Лев Николаевич#Война и мир#4",
         #"Толстой Лев Николаевич#Анна Каренина", "Тургенев Иван Сергеевич#Отцы и дети",
#         "Достоевский Федор Михайлович#Преступление и наказание", "Неизвестный автор#Война и мир"]
book_pairs=[("Толстой Лев Николаевич#Война и мир#1", "Достоевский Федор Михайлович#Преступление и наказание"),
            ("Толстой Лев Николаевич#Война и мир#2", "Толстой Лев Николаевич#Война и мир#1"),
            ("Толстой Лев Николаевич#Война и мир#1", "Толстой Лев Николаевич#Анна Каренина"),
            ('Толстой Лев Николаевич#Война и мир#1', 'Стругацкие#Сборник-1'),
            ("Толстой Лев Николаевич#Анна Каренина",'Стругацкие#Сборник-1')]

all_y = {}
for i in book_pairs:
       
       data1 = dt.get_words(i[0])
       data2 = dt.get_words(i[1])

       C0 = sum(list(map(lambda t: t[1], data1)))
       C1 = sum(list(map(lambda t: t[1], data2)))
       print(C0, C1)
       all_y = dt.sum_dicts(dt.devide_dict(dict(dt.get_words(i[0],'words')), C0),
                            dt.devide_dict(dict(dt.get_words(i[1],'words')), C1),
                                           minus = True)

       all_y = sorted(list(all_y.items()), key = lambda t: t[0])
       
       y = (np.array(list(map(lambda t: t[1], all_y)))**2)**0.25
       plt.plot(y, label = i[0]+' us '+ i[1])

       print(i[0], i[1], sum(y))
plt.legend(loc='upper right')
plt.show()
#words = dt.get_words()

