# RESTful APIs using MongoDB
# Student: Paul Dunne
# StudentID: C00160133
# Class: Web Cloud Dev
# Lecturer: Paul Barry
# Due Date: 19/02/2016

from pymongo import MongoClient
from flask import Flask, request, Response, jsonify
from bson import json_util, ObjectId
from pprint import pprint
import json

app = Flask(__name__) 
client = MongoClient()

@app.route('/', methods = ['GET']) 
def api_test():
	if request.method == 'GET':
		return "Please use another command"
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/list/', methods = ['GET']) 
def api_list():
	if request.method == 'GET':
		db = client['FantasyDB']
		collection = db['unicorns']
		data = db.collection_names()	

		out = { "collection" :
					{
						"version" : "v1.0",
						"href" : "http://127.0.0.1:5000/table/list/",
						"links" :
						[
							{ "href": "http://127.0.0.1:5000/table/showall/" + data[0] },
							{ "href": "http://127.0.0.1:5000/table/showall/" + data[1] },
						]
					}
				}

		json_str = json.dumps(out)
		return json_str
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/showall/<coll>', methods = ['GET']) 
def api_showall(coll) -> str:
	if request.method == 'GET':
		db = client['FantasyDB']
		collection = db[str(coll)]

		json_str = ""
		for x in collection.find():
			json_str += json.dumps(x, default=json_util.default)

		output = '[' + json_str + ']'

		Link = { "collection" : 
					{
						"version" : "v1.0",
						"hrefs" : "http://localhost:5000/table/showall/" + coll,
						"items" : output

				} 	}

		return json.dumps(Link)
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/showone/<coll>/<_id>', methods = ['GET']) 
def api_showone(coll, _id) -> str:
	if request.method == 'GET':
		db = client['FantasyDB']
		collection = db[str(coll)]
		
		d = str(_id)
		p = collection.find_one({"_id" : ObjectId(d)})
		Link = { "collection" : 
					{
						"version" : "v1.0",
						"hrefs" : "http://localhost:5000/table/showone/" + d,
						"items" : p

				} 	}

		return json.dumps(Link, default=json_util.default)

	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/post/<coll>',methods=['POST'])
def api_post(coll) -> str:
	if request.method == 'POST':
		r = request.get_json(force=True)
		pprint(r)
		template = r["collection"]["unicorns"]

		db = client['FantasyDB']
		collection = db[str(coll)]

		unicorn = {

		"name": template[0]["value"],
		"dob": template[1]["value"],
		"loves": template[2]["value"],
		"weight": template[3]["value"],
		"gender": template[4]["value"],
		"vampires": template[5]["value"]
		}

		collection.insert(unicorn)

		jsonlist = {}    
		jsonlist['links'] = {}
		jsonlist['links']['showall/unicorns'] = "http://127.0.0.1:5000/table/showall/unicorns/"
		jsonlist['links']['post/unicorns'] = "http://127.0.0.1:5000/table/post/unicorns/"
		return json.dumps(jsonlist)
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)
#===================================================================#

app.run(debug=True)
