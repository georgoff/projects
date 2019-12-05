import requests
import json
import xml.etree.ElementTree as ET

payload = {'key': '0dfd7ad9-2474-4d67-8508-9fa66333481d'}
resp = requests.get('http://api.pugetsound.onebusaway.org/api/where/arrivals-and-departures-for-stop/1_6050.xml',
                    params = payload)
# add conditional in case resp.status_code != 200

# print(resp.text)
# parsed_json = json.loads(resp.text)

root = ET.fromstring(resp.text)

for child in root:
    print(child.tag, child.attrib)

print(root[4][1][1][0].tag, root[4][1][1][0][7].text)