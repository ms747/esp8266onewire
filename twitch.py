import urllib.request
from pprint import pprint
import json
import sys


#user = input("Twitch user : ")
user = str(sys.argv[1])
#d -> s
client = "4u0hc5wbl14ppu8620x75j95mc2chjd"
url = "https://api.twitch.tv/kraken/streams/" + user + "?client_id=" + client


#print(url)

responce = urllib.request.urlopen(url)

data = responce.read().decode("utf-8")

#pprint(data)

jdata = json.loads(data)

#pprint(jdata)

#pprint(jdata["stream"])

d2 = str(jdata["stream"])
#print(d2 == "None")

if d2 == "None" :
    print("User offline")
else :
    print("\n-----------------------User streaming-------------------------\n")
    print("Name : " + str(jdata["stream"]["channel"]["display_name"]))    
    print("Game : " + str(jdata["stream"]["channel"]["game"]))    
    print("Language : " + str(jdata["stream"]["channel"]["language"]))    
    print("Viewers : " + str(jdata["stream"]["viewers"]))    
    print("--------------------------------------------------------------\n")
    print("\n\n")


