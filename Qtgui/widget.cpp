#include "widget.h"
#include "ui_widget.h"
//ui_XXXX.h是Qt自动生成的文件，包含了UI设计器中设计的界面元素的定义和布局信息
//  XXXX是UI文件的名称=CPP文件的名称

using namespace TACRnamespace;
// 使用静态局部变量确保只构造一次
TACR& getGlobalTACR(double T, double dt) {
    static TACR globalTACR; // 静态局部变量，只会构造一次
    globalTACR.initXTipValues(T, dt); // 初始化方法
    return globalTACR;
};

Widget::Widget(QWidget* parent) :
    QWidget(parent),    // 父类构造函数
    ui(new Ui::Widget)  // 创建UI对象
{
    ui->setupUi(this);  // 初始化UI对象

    // 连接信号槽
    QObject::connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(slotBtnClear()));  // 清空按钮信号槽
    QObject::connect(ui->btnStartAndStop, SIGNAL(clicked(bool)), this, SLOT(slotBtnStartForLoop()));    // 启动/停止按钮信号槽

    // 创建横纵坐标轴并设置显示范围
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("Time (s)");
    m_axisY->setTitleText("Value");
    m_axisX->setRange(AXIS_MIN_X, AXIS_MAX_X);
    m_axisY->setRange(AXIS_MIN_Y, AXIS_MAX_Y);

    m_line1 = new QLineSeries();                               // 创建曲线绘制对象
    m_line1->setName("实际值");                    // 图例名称

    // 设置曲线样式
    QPen Pen1;
    //Pen1.setColor(QColor("#FF5733"));     // 橙色
    Pen1.setColor(QColor(Qt::red));         // 红色 // 使用Qt预设颜色
    //Pen1.setColor(QColor(255,0,0));       // 或使用RGB值
    Pen1.setWidth(3);                         // 线宽
    //Pen1.setStyle(Qt::SolidLine);                 // 实线
    //Pen1.setStyle(Qt::DashDotLine);        // 点划线
    Pen1.setStyle(Qt::DashLine);             // 虚线
    //Pen1.setStyle(Qt::DotLine);                      // 点线
    m_line1->setPen(Pen1);
    m_line1->setPointsVisible(false);       // 设置数据点可见


    m_line2 = new QLineSeries();                             // 创建曲线绘制对象
    m_line2->setName("参考值");                            // 图例名称
    // 设置曲线样式
    QPen Pen2;
    //Pen2.setColor(QColor("#FF5733"));     // 橙色
    Pen2.setColor(QColor(Qt::blue));         // 红色 // 使用Qt预设颜色
    //Pen2.setColor(QColor(255,0,0));       // 或使用RGB值
    Pen2.setWidth(3);                         // 线宽
    Pen2.setStyle(Qt::SolidLine);                 // 实线
    //Pen2.setStyle(Qt::DashDotLine);        // 点划线
    //Pen2.setStyle(Qt::DashLine);             // 虚线
    //Pen2.setStyle(Qt::DotLine);                      // 点线
    m_line2->setPen(Pen2);
    m_line2->setPointsVisible(false);       // 设置数据点可见


    m_chart = new QChart();                                        // 创建图表对象
    m_chart->addAxis(m_axisX, Qt::AlignBottom);                    // 将X轴添加到横轴上
    m_chart->addAxis(m_axisY, Qt::AlignLeft);                      // 将Y轴添加到纵轴上
    m_chart->addSeries(m_line1);                               // 将曲线对象添加到图表上
    m_chart->addSeries(m_line2);
    m_chart->setAnimationOptions(QChart::SeriesAnimations);        // 动画：能使曲线绘制显示的更平滑，过渡效果更好看

    m_line1->attachAxis(m_axisX);                             // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    m_line1->attachAxis(m_axisY);                             // 曲线对象关联上Y轴，此步骤必须在m_chart->addSeries之后
    m_line2->attachAxis(m_axisX);                             // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    m_line2->attachAxis(m_axisY);                             // 曲线对象关联上Y轴，此步骤必须在m_chart->addSeries之后

    ui->graphicsView->setChart(m_chart);                           // 将图表对象设置到graphicsView上进行显示
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑

    // 初始化定时器
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Widget::updateSimulation);
}

Widget::~Widget()
{
    delete ui;
}

// 启动/停止按钮槽函数
void Widget::slotBtnStartForLoop()
{
    // 只在首次启动或主动清除后重置数据
    if (m_currentTime == 0.0) {
        m_line1->clear();
        m_line2->clear();
        m_axisX->setRange(AXIS_MIN_X, AXIS_MAX_X); // 重置坐标轴范围
        m_axisY->setRange(AXIS_MIN_Y, AXIS_MAX_Y);
    }

    isRunning = true;

    // 更新按钮状态
    ui->btnStartAndStop->setText("停止仿真");
    ui->btnClear->setEnabled(false);

    // 切换信号连接
    disconnect(ui->btnStartAndStop, &QPushButton::clicked, this, &Widget::slotBtnStartForLoop);
    connect(ui->btnStartAndStop, &QPushButton::clicked, this, &Widget::slotBtnStop);

    // 启动定时器
    m_timer->start(1);
}

// 停止按钮槽函数
void Widget::slotBtnStop()
{
    m_timer->stop();
    isRunning = false;
    ui->btnClear->setEnabled(true);
    ui->btnStartAndStop->setText("开始仿真");

    // 恢复信号连接
    disconnect(ui->btnStartAndStop, &QPushButton::clicked, this, &Widget::slotBtnStop);
    connect(ui->btnStartAndStop, &QPushButton::clicked, this, &Widget::slotBtnStartForLoop);
}

// 清空按钮槽函数
void Widget::slotBtnClear()
{
    if (!isRunning) {
        m_line1->clear();
        m_line2->clear();
        m_axisX->setRange(AXIS_MIN_X, AXIS_MAX_X);
        m_axisY->setRange(AXIS_MIN_Y, AXIS_MAX_Y);
        m_currentTime = 0.0; // 重置时间戳
    }
}

// 仿真更新函数
void Widget::updateSimulation()
{
    if (m_currentTime > T) {
        slotBtnStop();
        return;
    }

    TACR& globalTACR = getGlobalTACR(T, dt);
    double value1 = globalTACR.getXTipPosition(m_currentTime);
    double value2 = globalTACR.getRefePosition(m_currentTime);

    // 更新曲线
    m_line1->append(m_currentTime, value1);
    m_line2->append(m_currentTime, value2);

    // 动态扩展X轴范围
    if (m_currentTime > m_axisX->max()) {
        m_axisX->setMax(m_currentTime + 1.0);
    }

    m_currentTime += dt;
    qApp->processEvents();
}