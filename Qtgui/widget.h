#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QtCharts>
#include <cmath>

#include <TACR.h>

/* 光添加头文件QChartView还不够，还需要引入QChart的命名空间 */
//高版本不需要
//QT_CHARTS_USE_NAMESPACE

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = 0);
    ~Widget();

private:
    Ui::Widget* ui;

private:
    /* 定时器对象 */
    QTimer* m_timer;

    /* 图表对象 */
    QChart* m_chart;

    /* 横纵坐标轴对象 */
    QValueAxis* m_axisX, * m_axisY;

    /* 曲线图对象 */
    QLineSeries* m_line1;
    QLineSeries* m_line2;

    /* 仿真参数 */
    const double AXIS_MAX_X = 10, AXIS_MAX_Y = 0.2;
    const double AXIS_MIN_X = 0, AXIS_MIN_Y = -0.2;
    const double T = 10.0;      // 总仿真时间
    const double dt = 0.05;      // 时间步长

    double m_currentTime = 0.0;  // 当前仿真时间
    bool isRunning = false;      // 运行状态标志

private slots:
    void slotBtnClear();
    void slotBtnStartForLoop();
    void slotBtnStop();
    void updateSimulation();     // 定时器更新函数
};


#endif // WIDGET_H