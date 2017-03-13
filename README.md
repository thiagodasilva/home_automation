# The GMNI Project

The GMNI project is just a hobby project to learn a little bit more about IoT
devices and their use in the home. To start, I'm using an ESP8266 to collect
temperature and humidity measurements from a DHT22 sensor, then sending that
information to a central server to be stored and graphed. For collecting,
storing and graphing I'm using what I dubbed the _GMNI stack_:
  * **G**rafana - Used to build a Dashboard to display all collected data from
    sensors
  * **M**osquitto - _"A message broker that implements the MQTT broker"_. The IoT
    devices will publish their sensors data to this message broker, which is
    responsible to deliver the message to the appropriate subscriber(s).
  * **N**ode-Red - _"A Visual Tool for wiring the Internet of Things"_. Node-Red
    allows me to graphically create a subscriber of the mqtt broker, massage
    the data and send it to InfluxDB to be stored in the correct format.
  * **I**nfluxDB - A time series database. InfluxDB is used to store the data
    from the sensors. It will then serve as the data source for Grafana.

This repo contains ansible scripts to install the GMNI stack on a server. It
currently supports CentOS and Fedora (_It is also very close to working on
a Raspberry Pi with Fedora 25_).

The ``Vagrantfile`` allows you to test on a virtual machine, to get started
simply run ``vagrant up`` and stack will be configured for you, the ports for
each service is printed at the end of the ansible output.

The ``temperature_sensor`` directory contains the code used to run on the
ESP8266 devices. The ``sample`` directory contains sample data to test loading
the data into InfluxDB. It was usefult to start playing with Grafana dashboards.

In the future, I'd like to provide some Dashboard templates.

Let me know what you think and patches are welcome.
     
