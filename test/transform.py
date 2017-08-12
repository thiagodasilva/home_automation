import json
import datetime

with open('/tmp/temperature.json') as temp_json:
    data = json.load(temp_json)

cd = [] 
m_time = datetime.datetime.today()
data_s = sorted(data, key=lambda x: x['created_at'], reverse=True)
for m in data_s:
    m_time = m_time - datetime.timedelta(seconds=20)
    p = {
        "measurement": "temp",
        "time": m_time.strftime("%Y-%m-%d %H:%M:%S"),
        "tags": {
            "device": "attic"
        },
        "fields": {
            "value": float(m["value"])
        }}
    cd.append(p)

with open('/tmp/temp_sample.json', 'w') as clean_json:
    json.dump(cd, clean_json)

