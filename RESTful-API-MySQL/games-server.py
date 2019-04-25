


#===================================================================#

# Information #

"""

Created by: Paul Dunne
Student Id: C00160133

Contact:	pauliedunne (at) hotmail (dot) com

Notes:

1. tables/list/ MUST have '/' at the end of URL
2. games-server.py is the server file
3. games-post.py is the client post test
4. games-get.py is the client get test


"""

from flask import Flask, request, Response, jsonify
from pprint import pprint
import json
import DBcm

app = Flask(__name__)

# MySQL configurations
DBconfig = { 'host': 'localhost',
'user': 'gamesadmin',
'password': 'gamesadminpw',
'database': 'GamesDB' }

print ("Running on http://localhost:5000")

#===================================================================#



@app.route('/table/list/', methods = ['GET'])
def api_list() -> str:
	if request.method == 'GET':
		with DBcm.UseDatabase(DBconfig) as cursor:

			_SQLlist = "SHOW TABLES;"
			cursor.execute(_SQLlist)
			data = cursor.fetchall()

			Links = { "collection" :
						{
							"version" : "v1.0",
							"hrefs" : 
							[
								{ "href": "http://127.0.0.1:5000/table/list/" + data[0][0] },
								{ "href": "http://127.0.0.1:5000/table/list/" + data[1][0] },
								{ "href": "http://127.0.0.1:5000/table/list/" + data[2][0] }
							]
						}
					}

			json_str = json.dumps(str(Links))
			return json_str
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/showall/<table>', methods = ['GET'])
def api_showAll(table) -> str:
	if request.method == 'GET':
		with DBcm.UseDatabase(DBconfig) as cursor:

			_SQLlist = "SELECT * FROM %s;" % table
			cursor.execute(_SQLlist)
			data = cursor.fetchall()

			Link = { "collection" : 
						{
							"version" : "v1.0",
							"hrefs" : 
							[
								{"href": "http://localhost:5000/table/showall/" + table }
							],
							"data" :
							[
								{ str(data) }
							]
					} 	}
							

			return json.dumps(str(Link))
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/showone/<table>/<int:item_id>', methods = ['GET'])
def api_showOne(table, item_id):
	if request.method == 'GET':
		with DBcm.UseDatabase(DBconfig) as cursor: 
			_SQLshowOne = "SELECT * FROM %s WHERE id = %d;" % (table, item_id)
			cursor.execute(_SQLshowOne)
			data = cursor.fetchall()

			Link = { "collection" : 
						{
							"version" : "v1.0",
							"hrefs" : 
							[
								{"href": "http://localhost:5000/table/showall/" + table },
								{"href": "http://localhost:5000/table/showone/" + table + "/" + str(item_id) }
							],
							"data" :
							[
								{ str(data) }
							]
					} 	}

			return json.dumps(str(Link))

	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)

#===================================================================#

@app.route('/table/post/<table>', methods = ['POST'])
def api_post(table) -> str:
	if request.method == 'POST':
		r = request.get_json(force=True)
		pprint(r)

		if table == "games":
			collection = r["collection"]["games"]
			print(collection[0]["column"] + " : " + collection[0]["value"])
			print(collection[1]["column"] + " : " + collection[1]["value"])
			name = collection[0]["value"]
			description = collection[1]["value"]
			
			with DBcm.UseDatabase(DBconfig) as cursor: 
				_SQLpost = "INSERT INTO games (name, description) values (%s, %s)"
				cursor.execute(_SQLpost, (name, description))

				return "Added Games "

		if table == "players":
			collection = r["collection"]["players"]
			print(collection[0]["column"] + " : " + collection[0]["value"])
			print(collection[1]["column"] + " : " + collection[1]["value"])
			print(collection[2]["column"] + " : " + collection[2]["value"])
			print(collection[3]["column"] + " : " + collection[3]["value"])
			print(collection[4]["column"] + " : " + collection[4]["value"])
			handle = collection[0]["value"]
			first = collection[1]["value"]
			last = collection[2]["value"]
			email = collection[3]["value"]
			passwd = collection[4]["value"]
			
			with DBcm.UseDatabase(DBconfig) as cursor: 
				_SQLpost = "INSERT INTO players (handle, first, last, email, passwd) values (%s, %s, %s, %s, %s)"
				cursor.execute(_SQLpost, (handle, first, last, email, passwd))
				return "Added Players "

		if table == "scores":
			collection = r["collection"]["scores"]
			print(collection[0]["column"] + " : " + str(collection[0]["value"]))
			print(collection[1]["column"] + " : " + str(collection[1]["value"]))
			print(collection[2]["column"] + " : " + str(collection[2]["value"]))
			game_id = collection[0]["value"]
			player_id = collection[1]["value"]
			score = collection[2]["value"]
			
			with DBcm.UseDatabase(DBconfig) as cursor: 
				_SQLpost = "INSERT INTO scores (game_id, player_id, score) values (%s, %s, %s)"
				cursor.execute(_SQLpost, (game_id, player_id, score))
				return "Added Scores "
	else:
		return 'Unsupported HTTP method: {}.'.format(request.method)


app.run(debug=True)

