#ifndef _TRAFFICLIGHTWINDOW_H_
#define _TRAFFICLIGHTWINDOW_H_
#include "QDockWidget"
#include "QDoubleSpinBox"

class LightSlider : public QSpinBox
{
    Q_OBJECT
public:
    LightSlider(QWidget *parent = nullptr) : QSpinBox(parent) { }
public slots:
    void slotKeepInterval(int val) { if (val > value()) { setValue(val); emit valueChanged(val); } }
    void slotBackKeepInterval(int val) { if (val < value()) { setValue(val); emit valueChanged(val); } }
};

struct LightTimings{
    int green;
    int yellow;
    int red;
};

class TrafficlightWindow : public QWidget
{
    Q_OBJECT
public:
    TrafficlightWindow(LightTimings timings, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    LightTimings getTimings() const;
private slots:
    void slotStartLight(int index);
private:
    LightSlider* m_Sliders[6];
    int m_StartLight;
};

#endif
