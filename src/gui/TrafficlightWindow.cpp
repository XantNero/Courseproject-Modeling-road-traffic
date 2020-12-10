#include "TrafficlightWindow.h"
#include <QtWidgets>

TrafficlightWindow::TrafficlightWindow(LightTimings lighttimings, QWidget *parent, Qt::WindowFlags flags)
    :QWidget(parent, flags), m_StartLight(0)
{
    if (lighttimings.green <= lighttimings.yellow) {
        if (lighttimings.green <= lighttimings.red)
            m_StartLight = 0;
        else
            m_StartLight = 2;
    }
    else {
        m_StartLight = 1;
    }


    QVBoxLayout* mainLayot = new QVBoxLayout();
    QHBoxLayout* horisontalLayout = new QHBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();


    QComboBox* comboBox = new QComboBox();
    comboBox->addItem(tr("Green"));
    comboBox->addItem(tr("Yellow"));
    comboBox->addItem(tr("Red"));

    connect(comboBox, SIGNAL(activated(int)), this, SLOT(slotStartLight(int)));

    for (int i = 0; i < sizeof(m_Sliders) / sizeof(LightSlider*); ++i)
        m_Sliders[i] = new LightSlider();


    for (int i = 0; i < sizeof(m_Sliders) / sizeof(LightSlider*); i += 2) {
        connect(m_Sliders[i], SIGNAL(valueChanged(int)), m_Sliders[i + 1], SLOT(slotKeepInterval(int)));
        connect(m_Sliders[i + 1], SIGNAL(valueChanged(int)), m_Sliders[i], SLOT(slotBackKeepInterval(int)));
    }
    for (int i = 1; i < sizeof(m_Sliders) / sizeof(LightSlider*); i += 2) {
        connect(m_Sliders[i], SIGNAL(valueChanged(int)), m_Sliders[(i + 1) % (sizeof(m_Sliders) / sizeof(LightSlider*))], SLOT(setValue(int)));
        connect(m_Sliders[(i + 1) % (sizeof(m_Sliders) / sizeof(LightSlider*))], SIGNAL(valueChanged(int)), m_Sliders[i], SLOT(setValue(int)));
    }

    //comboBox->addActions()

    for (int i = sizeof(m_Sliders) / sizeof(LightSlider*) - 1; i >= 0; --i) {
        rightLayout->addWidget(m_Sliders[i]);
    }

    slotStartLight(m_StartLight);

    int timings[sizeof(m_Sliders) / sizeof(LightSlider*) / 2];
    timings[0] = lighttimings.green;
    timings[1] = lighttimings.yellow;
    timings[2] = lighttimings.red;
    for (int i = 2 * m_StartLight + 1, cnt = 0; cnt < sizeof(m_Sliders) / sizeof(LightSlider*) / 2; ++cnt, i += 2) {
        m_Sliders[i % (sizeof(m_Sliders) / sizeof(LightSlider*))]->setValue(timings[(i % (sizeof(m_Sliders) / sizeof(LightSlider*))) / 2]);
    }


    QLabel* greenLabel = new QLabel();
    greenLabel->setStyleSheet("QLabel { background-color : green; color : blue; }");
    QLabel* yellowLabel = new QLabel();
    yellowLabel->setStyleSheet("QLabel { background-color : yellow; color : blue; }");
    QLabel* redLabel = new QLabel();
    redLabel->setStyleSheet("QLabel { background-color : red; color : blue; }");

    leftLayout->addWidget(redLabel);
    leftLayout->addWidget(yellowLabel);
    leftLayout->addWidget(greenLabel);

    horisontalLayout->addLayout(leftLayout);
    horisontalLayout->addLayout(rightLayout);

    mainLayot->addWidget(comboBox);
    mainLayot->addLayout(horisontalLayout);
    setLayout(mainLayot);
    //setWidget(layout);
    setMinimumSize(120, 200);
    setMaximumSize(120, 200);
    //show();
}

LightTimings TrafficlightWindow::getTimings() const
{
    int timings[sizeof(m_Sliders) / sizeof(LightSlider*) / 2];
    LightTimings result;
    for (int i = 2 * m_StartLight + 1, cnt = 0; cnt < sizeof(m_Sliders) / sizeof(LightSlider*) / 2; ++cnt, i += 2) {
        timings[(i % (sizeof(m_Sliders) / sizeof(LightSlider*))) / 2] = m_Sliders[i % (sizeof(m_Sliders) / sizeof(LightSlider*))]->value();
    }
    result.green = timings[0];
    result.yellow = timings[1];
    result.red = timings[2];
    return result;
}

void TrafficlightWindow::slotStartLight(int index)
{
    ;
    m_Sliders[2 * m_StartLight]->setMinimum(0);
    m_Sliders[2 * m_StartLight]->setMaximum(99);
    m_Sliders[(2 * m_StartLight - 1 + (sizeof(m_Sliders) / sizeof(LightSlider*))) % (sizeof(m_Sliders) / sizeof(LightSlider*))]->setValue(0);
//    m_Sliders[2 * index]->setValue(0.1f);
//    m_Sliders[2 * index]->setValue(0.0f);


    m_Sliders[2 * index]->setValue(0);
    m_Sliders[2 * index]->setMinimum(0);
    m_Sliders[2 * index]->setMaximum(0);

    m_StartLight = index;
}
