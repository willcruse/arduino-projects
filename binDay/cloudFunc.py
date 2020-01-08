import requests
from datetime import date
import json

def getData(request):
    """Responds to any HTTP request.
    Args:
        request (flask.Request): HTTP request object.
    Returns:
        The response text or any set of values that can be turned into a
        Response object using
        `make_response <http://flask.pocoo.org/docs/1.0/api/#flask.Flask.make_response>`.
    """ 
    # Set CORS headers for the preflight request
    if request.method == 'OPTIONS':
        # Allows GET requests from any origin with the Content-Type
        # header and caches preflight response for an 3600s
        headers = {
            'Access-Control-Allow-Origin': '*',
            'Access-Control-Allow-Methods': 'GET',
            'Access-Control-Allow-Headers': 'Content-Type',
            'Access-Control-Max-Age': '3600'
        }

        return ('', 204, headers)

    headers = {
        'Access-Control-Allow-Origin': '*',
    }
    binReq = requests.get("https://www.bathnes.gov.uk/NodeAPI/waste/bins/getRoute/100120027517")
    binJSON = binReq.json()

    binDay = binJSON.get("residualNextDate", "0000-01-01")[:10]
    recDay = binJSON.get("recyclingNextDate", "0000-01-01")[:10]
    currentDay = str(date.today())

    ret = {
        "bin": binDay == currentDay,
        "rec": recDay == currentDay
    }
    print(str(ret))
    return (json.dumps(ret), 200, headers)
