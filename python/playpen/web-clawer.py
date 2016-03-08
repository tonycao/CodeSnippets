import urllib2

url = "http://yue.ifeng.com/a/20150717/39747647_0.shtml"
request = urllib2.Request(url) # Write a letter
response = urllib2.urlopen(request) #Send the letter and get the reply 
page = response.read() #Read the reply

# Save source file
webFile = open('webPage.html', 'wb') 
webFile.write(page)
webFile.close()


