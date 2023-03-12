#pragma once

#include "ui_mainwindow.h"


#include <QtCharts/QtCharts>
#include <QMainWindow>
#include <QTime>

class QTimer;

class SineDataProducer;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(SineDataProducer& sine_producer, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_produceSineDataButton_clicked();
    void on_startButton_clicked();
    void produceAndDisplayData();
    void on_update_rate_input_valueChanged(int arg1);

    void on_frequency_input_valueChanged(int arg1);

    void on_amplitude_input_valueChanged(double arg1);

    void on_sample_rate_input_valueChanged(int arg1);

private:
    QTime m_segment_start_time{QTime::currentTime()};
    SineDataProducer& m_sine_producer;

    QTimer m_update_data_timer;
    int m_update_rate;

    QChart* m_chart;
    QChartView* m_chart_view;
};
