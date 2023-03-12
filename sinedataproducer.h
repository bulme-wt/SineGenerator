#pragma once

#include <QTime>
#include <map>

class SineDataProducer
{
public:
    SineDataProducer(double frequency = 1.0, double amplitude = 1.0, double sample_rate = 100.0);

public:
    std::map<QTime, double> getData(const QTime& from, const QTime& to ) const;

    double getFrequency() const;
    void setFrequency(double newFrequency);

    double getAmplitude() const;
    void setAmplitude(double newAmplitude);

    double getSampleRate() const;
    void setSampleRate(double newSample_rate);

private:
    double m_frequency;
    double m_amplitude;
    double m_sample_rate;
    QTime m_start_time;
};

