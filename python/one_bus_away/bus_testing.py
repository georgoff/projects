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

# cannot just use the index because the number of sub-elements changes
# (for some reason)
for route in root[4][1][1].iter('arrivalAndDeparture'):
    print(route[7].text, route[15].text)
    

# create functions for:
    # given a bus stop, return which routes stop there
        # pull response using requests.get, pasting in the stop number
            # do we use arrivals-and-departures-for-stop or something else?
        # change future time parameter to 24 hours (?)
        # find child element that gives short route names
        # return unique values of route names
    # given a bus stop, return the next n number of arrivals (route and time)
        # pull response using requests.get, pasting in the stop number
            # do we use arrivals-and-departures-for-stop or something else?
            # need to see if we can supply n to the API call or if we have to just
            # use the number of future buses that it gives us...
        # return a list that contains the upcoming arrivals - route and time
            # should we do estimated arrival time or estimated time to arrival?
    # given a bus stop and route, return the number of minutes until the next n arrivals
        # pull response using requests.get, pasting in the stop number and route
            # pretty sure there is an API call specifically for this, giving only
            # the times for a specified route and stop
        # return a vector that contains the number of minutes until the next n arrivals