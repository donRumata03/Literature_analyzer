import data_worker as dt



for i in dt.get_all_books():
       f = open(dt.get_file(i),'r')
       text = f.read()
       f.close()
       
       while True:
              i1 = text.find('[')
              i2 = text.find(']',i1)
              if i1==-1 or i2==-1:
                     break
              text= text[:i1] + text[i2+1:]
       
       f = open(dt.get_file(i),'w')
       f.write(text)
       f.close()
