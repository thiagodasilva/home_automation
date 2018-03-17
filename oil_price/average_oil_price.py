#!/usr/bin/env python

import urllib
import paho.mqtt.publish as publish
from bs4 import BeautifulSoup as bs

newenglandoil = urllib.urlopen("http://www.newenglandoil.com/massachusetts/zone10.asp?x=0").read()
soup = bs(newenglandoil, 'lxml')

oil_table = soup.find('table')
tbody = oil_table.find('tbody')
rows = tbody.find_all('tr')
sum = 0
for row in rows:
    td = row.find_all('td')
    sum += float(td[2].get_text()[1:])

average = sum/len(rows)
publish.single('average_oil_price', average)
