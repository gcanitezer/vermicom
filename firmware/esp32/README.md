Source codes for vermicom.

# Requirements for the application

## Sensor requirements

* Sensors shall be powered before reading. This will save power and sensor life.
* Sensors data for the last 24 hours shall be saved to export or display graph.

### Temprature sensors

* At least two temprature sensor shall be used. One of them shall be used for water temprature sensing. Other one shall be used for soil temprature sensing.
* Measurements shall be done for every 60 secs.
* Measurement frequency can be increased during PID Control phases.

### Soil humidity sensor

* Measurements shall be done for every 60 secs.
* If hardware supports more than one sensor can be used. 


### Air temprature and humidity

* Measurements shall be done for every 60 secs.


## Trigger requirements

* At least one trigger rule can be set for one sensor. (Can be more than one sensor-relay mapping)
* Following options shall be available for triggering
  * Min
  * Max
  * Between
* Sensor and relay mapping shall be done.
* Time for triggering state shall be set and it cannot be more than 60 secs (time for sensor read frequency).

## Vermicom functionality

* Drop of temprature in soil sensor shall trigger water pump for 10 secs.
* Increase of temprature in soil shall trigger water pump for 10 secs.
* Decrease of temprature in water tank shall trigger water heater for 10 secs.
* Increase of temprature in water tank shall trigger water cooler for 10 secs.
* Decrease of soil humidity shall trigger humidifier for 10 secs.

