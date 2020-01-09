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

       #[:NUMBER]
       C0 = sum(list(map(lambda t: t[1], data1)))
       C1 = sum(list(map(lambda t: t[1], data2)))
       print(C0, C1)
       all_y = dt.sum_dicts(dt.devide_dict(dict(dt.get_words(i[0],'words')), C0),
                            dt.devide_dict(dict(dt.get_words(i[1],'words')), C1),
                                           minus = True)
      # print(C)
       #y = np.array(list(map(lambda t: t[1], toConsider)))
      # x = np.array(list(map(lambda t: t[0], toConsider)))

       #C = sum(y)

       
       
       #y = y/C
       #x = np.log(x)
       #plt.plot(y)
       #plt.plot(np.full(NUMBER,1))
       #result_ = np.array([5281.0, -14394.0, -2.5, 70.0, 4.5])*y[0]/735.0
       #try:
       #result, _ =curve_fit(norm , x, y,
                            #p0 = [1, 5, 20 , 60, 120, 0, -1, 0],
                            #bounds = ([0,-np.inf,-np.inf,0,-np.inf,-np.inf],[np.inf,0,0,np.inf,0,0]),
        #                    maxfev = 10000)
                            
       #x=np.arange(min(x),max(x),0.01)           
       #except:
       #       print('ERR',i)
       #       result, _ =curve_fit(funct, np.arange(NUMBER) + 1, y,
        #                    p0 = [1, 1, 1, 1, 1],
        #                    bounds = ([-np.inf,-np.inf,-np.inf,0,0],np.inf),
        #                    maxfev = 10000)
       #plt.plot(np.arange(NUMBER))
       #result = [1384, -5257, 22.5, 3.5, 3.5]

       #x_ = np.log(x)
       #if i == "Неизвестный автор#Война и мир":
       #plt.plot(x,abs(norm(x, *result)), random.choice(styles), label = i)
       #plt.plot(x,y)
       ##else:
       #       if "Толстой Лев Николаевич#Война и мир" in i:
       #              plt.plot(funct(np.arange(NUMBER) + 1, *result), label = i, color = 'red')
       #       else:
       #              plt.plot(funct(np.arange(NUMBER) + 1, *result), label = i)
       #plt.plot(sum_norm(x,*[5, -1, -2 , 1, -0.2, -3.2]))
       #plt.plot(x,y, label=i)
       #print(list(map(lambda x:float(x), result)))
       all_y = sorted(list(all_y.items()), key = lambda t: t[0])

       x = range(len(all_y))
       
       y = (np.array(list(map(lambda t: t[1], all_y)))**2)**0.5

##       ans = []
##       for j in x:
##              if y[j] > 0.0002:
##                     ans.append(all_y[j])
##       ans = sorted(ans, key = lambda t: -t[1])
##       print(ans)
##       #x = np.log(np.array(list(map(lambda t: t[0], all_y))))
##       print(ans)
##       result, _ =curve_fit(norm , x, y,
##                                   #p0 = [1, 5, 20 , 60, 120, 0, -1, 0],
##                                   #bounds = ([0,-np.inf,-np.inf,0,-np.inf,-np.inf],[np.inf,0,0,np.inf,0,0]),
##                                   maxfev = 10000)
##       plt.plot(x,abs(norm(x, *result)), random.choice(styles), label = i)
       plt.plot(x,y, label = i[0]+' us '+ i[1])
##       plt.legend(loc='upper right')
##       plt.show()

       print(i[0], i[1], sum(y))
plt.legend(loc='upper right')
plt.show()
#words = dt.get_words()

