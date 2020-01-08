import requests
from datetime import date

binReq = requests.get("https://www.bathnes.gov.uk/NodeAPI/waste/bins/getRoute/100120027517")
timeReq = requests.get("http://worldtimeapi.org/api/timezone/Europe/London")

binJSON = binReq.json()
timeJSON = timeReq.json()

binDay = binJSON.get("residualNextDate", "0000-01-01")[:10]
recDay = binJSON.get("recyclingNextDate", "0000-01-01")[:10]
currentDay = str(date.today())
print(binDay[:10])
print(recDay[:10])
print(currentDay)

ret = {
    "bin": binDay == currentDay,
    "rec": recDay == currentDay
}
print(str(ret))