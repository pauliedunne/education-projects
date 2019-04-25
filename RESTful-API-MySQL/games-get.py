
import requests
import pprint

def request_results(r:'request object') -> None:
    print('-' * 50)
    print('HTTP status code ->', r.status_code)
    for h in sorted(r.headers):
        print(h, '->', r.headers[h])
    print()
    pprint.pprint(r.json())
    print('-' * 50)

URL = 'http://127.0.0.1:5000'
API_List = '/table/list/'
API_ShowAll = '/table/showall/games'
API_ShowOne = '/table/showone/games/1'


print()
request_results(requests.get(URL+API_List))
print()
request_results(requests.get(URL+API_ShowAll))
print()
request_results(requests.get(URL+API_ShowOne))



