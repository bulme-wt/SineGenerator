#include "mainwindow.h"

#include "sinedataproducer.h"

#include <QGraphicsView>
#include <QTimer>

MainWindow::MainWindow(SineDataProducer& sine_producer, QWidget *parent)
    : QMainWindow{parent}
    , m_sine_producer{sine_producer}
{
    setupUi(this);

    connect(&m_update_data_timer, SIGNAL(timeout()),
            this, SLOT(produceAndDisplayData()));


    m_chart  = new QChart;
    m_chart_view = new QChartView{m_chart};
    m_chart_view->setRenderHint(QPainter::Antialiasing);
    main_layout->addWidget(m_chart_view, 4, 1);

    m_sine_producer.setFrequency(frequency_input->value());
    m_sine_producer.setAmplitude(amplitude_input->value());
    m_sine_producer.setSampleRate(sample_rate_input->value());

    m_update_rate = update_rate_input->value();
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_produceSineDataButton_clicked()
{
    produceAndDisplayData();
}


void MainWindow::on_startButton_clicked()
{
    if (!m_update_data_timer.isActive())
    {
        m_update_data_timer.start(1000/m_update_rate);
        startButton->setText("Stop");
    }
    else
    {
        m_update_data_timer.stop();
        startButton->setText("Start");
    }
}

void MainWindow::produceAndDisplayData()
{
    QTime current_time = QTime::currentTime();

    // auto = std::map<QTime, double>
    const auto& data = m_sine_producer.getData(m_segment_start_time, current_time);

    m_dataOutputTable->clearContents();
    m_dataOutputTable->setRowCount(data.size());
    int row = 0;

    QLineSeries* series = new QLineSeries();
    series->setName("sine data");

    // auto = std::pair<QTime, double>
    for(const auto& data_point : data)
    {
        QTableWidgetItem* time_item = new QTableWidgetItem(
            data_point.first.toString("hh:mm:ss.zzz"));
        m_dataOutputTable->setItem(row, 0, time_item);

        QTableWidgetItem* value_item = new QTableWidgetItem(
                    QString::number(data_point.second));
        m_dataOutputTable->setItem(row, 1, value_item);
        row++;

        // Need to convert to QDateTime because QDateTimeAxis expects appropriate values
        QDateTime dt{QDate::currentDate(), data_point.first};
        double time = dt.toMSecsSinceEpoch();
        series->append(time, data_point.second);
    }

    m_chart->removeAllSeries();
    m_chart->addSeries(series);

    m_chart->legend()->hide();
    m_chart->setTitle("Sine Chart");

    for(auto axis : m_chart->axes())
    {
        m_chart->removeAxis(axis);
    }

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(5);
    axisX->setFormat("hh:mm:ss.zzz");
    axisX->setTitleText("time");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%f");
    axisY->setTitleText("[V]");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    m_segment_start_time = current_time;
}

void MainWindow::on_update_rate_input_valueChanged(int arg1)
{
    m_update_rate = arg1;
    if (m_update_data_timer.isActive())
    {
        m_update_data_timer.stop();
        m_update_data_timer.start(1000/m_update_rate);
    }
}


void MainWindow::on_frequency_input_valueChanged(int arg1)
{
     m_sine_producer.setFrequency(arg1);
}

void MainWindow::on_amplitude_input_valueChanged(double arg1)
{
    m_sine_producer.setAmplitude(arg1);
}

void MainWindow::on_sample_rate_input_valueChanged(int arg1)
{
    m_sine_producer.setSampleRate(arg1);
}
















