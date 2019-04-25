# RESTful APIs using MongoDB
# Student: Paul Dunne
# StudentID: C00160133
# Class: Web Cloud Dev
# Lecturer: Paul Barry
# Due Date: 19/02/2016

import requests
import datetime
from pprint import pprint
from flask import jsonify

URL = 'http://127.0.0.1:5000'
API_Unicorns = '/table/post/unicorns'

uni = """{ "collection": { "unicorns": [
         	{ "column": "name","value": "Paul" },
			{ "column": "dob","value": "1993, 4, 13, 13, 0" },
			{ "column": "loves","value": "carrot, sugar" },
			{ "column": "weight","value": "500" },
			{ "column": "gender","value": "m" },
			{ "column": "vampires","value": "200" } ] } }"""

r = requests.post(URL+API_Unicorns, data=uni)
print(r.status_code)
print(r.headers)
print(uni)
print(r.json())


