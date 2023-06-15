#ifndef _SENSOR_FACTORY_H_
#define _SENSOR_FACTORY_H_

class Eye;
class Ear;
class Bug;

class SensorFactory {
private:
    static SensorFactory* factory;
    SensorFactory();
    SensorFactory(const SensorFactory& sensorFactory) = delete;
    SensorFactory& operator=(const SensorFactory& sensorFactory) = delete;

public:
    ~SensorFactory();
    static SensorFactory* getSensorFactory();
    void attachEye(Bug* bug) const;
    void attachEar(Bug* bug) const;
    void attachSensors(Bug* bug) const;
};

#endif
