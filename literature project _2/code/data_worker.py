import os#, sys
import json

def add_book(name, author = 'Unknown', year = 0):
       descriptor[name] = {'author':author, 'year':year, 'read_bytes': 0}

def get_books_by(val, prop='author'):

       to_return = []
       
       for i in descriptor:
              if descriptor[i] [prop] == val:
                     to_return.append(i)
       return to_return
def get_book_of(val, prop = 'author'):
       for i in descriptor:
              if descriptor[i] [prop] == val:
                     return i
def get_val(name, prop='author'):
       return descriptor[name][prop]
def get_descriptor():
       return descriptor
def get_file(name):
       return main + '/data/literature/' + name + '/text.txt'
def get_data_dir():
       return main + '/data'
def get_book():
       for i in descriptor:
              return i
def get_all_books():
       r=[]
       for i in descriptor:
              r.append(i)
       return r

def get_endings():
       r=[]
       for i in endings:
              r+=endings[i]
       return r
def flush():
       json_descriptor = open(main + '/data/descriptors/main.json', 'w')
       json.dump(descriptor, json_descriptor)
       json_descriptor.close()

def get_words_file(name,type_='words'):
       return main + '/data/literature/' + name + '/'+type_+'.json'

def save_words_as(words,name, type_='words'):
       json_words = open(get_words_file(name, type_), 'w') 
       json.dump(words,json_words)
       json_words.close()

def get_words(name, type_='words'):
       json_words = open(get_words_file(name, type_), 'r')
       words = json.load(json_words)
       json_words.close()
       return words


def no_description(name):
       return not os.path.isfile(get_words_file(name))


def get(dict1,i,default=0):
       return dict1[i] if i in dict1 else default

def devide_dict(dict1,m):
       for i in dict1:
              dict1[i]/=m
       return dict1
def sum_dicts(dict1, dict2, minus = False):
       dict_ = {}
       for i in set(list(dict1.keys())+list(dict2.keys())):
              dict_[i] = get(dict1,i)+ (-get(dict2,i) if minus else get(dict2,i))
       return dict_




main = os.path.dirname(os.getcwd())
#sys.path.append(main)

json_descriptor = open(main + '/data/descriptors/main.json', 'r')
descriptor = json.load(json_descriptor)
json_descriptor.close()

json_endings = open(main + '/data/special/endings.json', 'r')
endings = json.load(json_endings)
json_endings.close()
