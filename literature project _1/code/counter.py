import data_worker as dt
import json


from collections import OrderedDict


MIN_LENGTH = 5
MAX_LENGTH = 25

POSTFIXES = ['ся', "сь"]


data_dir = dt.get_data_dir()
endings = dt.get_endings()




def write_word(word):
       if(word.islower()):
              
              if len(word)>MAX_LENGTH or len(word)<MIN_LENGTH:
                     #print(word)
                     return
              
              for i in word:
                     if ord(i)<1072 or ord(i)>1104:
                            return

              #if word[-2:] in POSTFIXES:
              #       word = word[:-2]
              
              if word[-3:] in endings:
                     word = word[:-3]
              elif word[-2:] in endings:
                     word = word[:-2]
              elif word[-1:] in endings:
                     word = word[:-1]
              
              
              
              if word in words:
                     words[word] += 1
                     return
              words[word]=1

def read(book):
       f = open(dt.get_file(book), 'r')

       text = ''

       

       while True:
              string = f.readline().replace('е', "ё")
              if string == '':
                     break
              text += string
              words = string.split()
              for i in words:
                     write_word(i)
       f.close()
       
       
       arr = text.split('.')

       for i in arr:
              l=len(i)
              if l<5 or l>700:
                     continue
              if l in sent:
                     sent[l] += 1
              else:
                     sent[l] = 1

       

def read_all(reread = False):
       global words,sent
       for i in dt.get_all_books():
              if dt.no_description(i) or reread:
                     words = {}
                     sent={}
                     read(i)
                     out = sorted(words.items(), key = lambda t: -t[1])
                     dt.save_words_as(out,i)
                     out = sorted(sent.items(), key = lambda t: t[0])
                     dt.save_words_as(out,i,'sentenses')

words = {}
sent = {}

if __name__ == '__main__':
       read_all(True)
