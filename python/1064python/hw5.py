file_name = input('Enter file name:')
file = open(file_name,"r")
pre_word=''
count_line=1
for linestr in file:
    linestr=linestr.strip()
    words=linestr.split()
    for index,word in enumerate(words):
        if word==pre_word:
        	print('Found word:',word, 'on line',count_line)
        pre_word=word
    count_line=count_line+1
file.close()
