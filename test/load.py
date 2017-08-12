from influxdb import InfluxDBClient
import json
from pprint import pprint

with open('/home/vagrant/temp_sample.json') as json_file:
    data = json.load(json_file)

client = InfluxDBClient(database='sensors_db')
client.write_points(data)
