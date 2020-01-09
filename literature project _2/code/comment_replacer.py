import data_worker as dt



for i in dt.get_all_books():
       f = open(dt.get_file(i),'r')
       text = f.read()
       f.close()

       j=0
       while True:
              i1 = text.find('[')
              i2 = text.find(']',i1)
              if i1==-1 or i2==-1:
                     break
              text= text[:i1] + text[i2+1:]
              j+=1
       if j!=0:
              print(str(i)+': removed '+str(j)+' comments')
       f = open(dt.get_file(i),'w')
       f.write(text)
       f.close()
