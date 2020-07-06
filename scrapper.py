import re
import requests
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager

import os

os.system("pip install -r requirements.txt")

driver = webdriver.Chrome(ChromeDriverManager().install())
driver.implicitly_wait(3)

BlogList = "study-blog-list.txt"

try:
	file = open(BlogList, "r")
except: 
	print("[error]: cannot find %s" % BlogList)
	print("[log]: exit")
	exit()

links = file.readlines()

count = 0
for line in links:
	_list = list(line)

	i = 0
	while(i != len(_list)):
		if(_list[i] == '\r'):
			del _list[i] 
			break
		if(_list[i] == '\n'):
			del _list[i]
			break
		if(_list[i] == 0):
			break
		i += 1

	link = ''.join(_list);

	#http | https request 
	
	driver.get(link)
	path = "./blogs/" + str(count) + ".html"

	out = open(path, "wb")
	out.write(driver.page_source.encode("utf-8"))
	out.close()
	
	count += 1

file.close()
driver.quit()

exit()