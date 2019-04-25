
import requests
from pprint import pprint
from flask import jsonify

URL = 'http://127.0.0.1:5000'
API_games = '/table/post/games'
API_players = '/table/post/players'
API_scores = '/table/post/scores'

print()
playload = """{
                "collection": 
                    {
                        "games": [
                                    {
                                        "column": "name",
                                        "value": "Final Fantasy"
                                    },

									{
										"column" : "description",
										"value" : "Fantasy/Action-Adventure Game!"
									}
                                ]
                    } 
             }"""

playerload = """ {

                "collection": 
                    {
                        "players": 
							[
                                    {
                                        "column": "handle",
                                        "value": "Robot"
                                    },

									{
										"column" : "first",
										"value" : "Optimus"
									},

									{
										"column" : "last",
										"value" : "Prime"
									},

									{
										"column" : "email",
										"value" : "auto@bots.com"
									},

									{
										"column" : "passwd",
										"value" : "decepticon"
									}
								]
                    } 
             }"""

scoreLoad = """ {
                "collection": 
                    {
                        "scores": [
                                    {
                                        "column": "game_id",
                                        "value": 1337
                                    },

									{
										"column" : "player_id",
										"value" : 9000
									},

									{
										"column" : "score",
										"value" : 42
									}
                                ]
                    }
             }"""



r = requests.post(URL+API_games, data=playload)
print(r.status_code)
print(r.headers)
#print(r.json()))

r = requests.post(URL+API_players, data=playerload)
print(r.status_code)
print(r.headers)
#pprint(r.json())

r = requests.post(URL+API_scores, data=scoreLoad)
print(r.status_code)
print(r.headers)
#pprint(r.json())


