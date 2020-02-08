import requests
from datetime import date, timedelta, datetime, tzinfo
import time

binReq = requests.get("https://www.bathnes.gov.uk/NodeAPI/waste/bins/getRoute/100120027517")
timeReq = requests.get("http://worldtimeapi.org/api/timezone/Europe/London")

binJSON = binReq.json()
timeJSON = timeReq.json()

binDay = binJSON.get("residualNextDate", "0000-01-01")[:10]
recDay = binJSON.get("recyclingNextDate", "0000-01-01")[:10]

thing = datetime.fromtimestamp(time.mktime(time.gmtime()))
thing += timedelta(hours=6)

currentDay = str(thing)[:10]

ret = {
    "bin": binDay == currentDay,
    "rec": recDay == currentDay
}

print(ret)