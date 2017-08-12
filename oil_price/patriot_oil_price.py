#!/usr/bin/env python

import urllib
import paho.mqtt.publish as publish
from BeautifulSoup import BeautifulSoup as bs

patriotweb = urllib.urlopen("http://www.patriotliquidenergy.com/").read()
soup = bs(patriotweb)

price = soup.find(id='price').text

publish.single('oil_price', price)
