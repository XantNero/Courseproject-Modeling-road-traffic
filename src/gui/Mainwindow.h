#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "WorkspaceScene.h"
#include "Workspace.h"
#include <QPlainTextEdit>
#include <QMainWindow>
#include <QGraphicsView>

//QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
//QT_END_NAMESPACE

struct LoadFileData
{
    QVector<CarGenerator*> carGenerators;
    QVector<int> carGeneratorsConnections;
    QVector<int> trafficlightConnections;
    QVector<RoadPoint*> points;
    QVector<QVector<QPair<int, int>>> conn;
    QVector<Trafficlight*> trafficLights;
};

struct SaveFileData
{
    QVector<CarGenerator*> carGenerators;
    QVector<RoadPoint*> points;
    QVector<QList<RoadPoint*>> conn;
    QHash<RoadPoint*, int> hash;
    QVector<Trafficlight*> trafficlights;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void loadFile(const QString &fileName);
protected:
    virtual void closeEvent(QCloseEvent *event) override;
private slots:
    void slotNewFile();
    void slotOpen();
    bool slotSave();
    bool slotSaveAs();
    void slotAbout();
    void slotWorkspaceIsModified();
    void slotRun();
    void slotAddRoad();
    void slotAddRoadPoint();
    void slotAddCarGenerator();
    void slotAddTrafficlight();
    void slotMove();
    void slotAddDockWidget(QWidget* widget);
    void slotRemoveDockWidget(QWidget* widget);
    void sceneScaleChanged(const QString &scale);
signals:
    void signalAction(WorkspaceScene::ActionType);
private:
    void createMenuBarActions();
    void createToolBarActions();
    void createScaleAction();
    void createItemMenuActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool loadCarGenerators(QTextStream &in,
                           int &line,
                           QVector<CarGenerator*> &carGenerators,
                           QVector<int> &carGeneratorsConnections);
    bool loadPoints(QTextStream &in,
                    int &lineCount, QVector<RoadPoint*> &points);
    bool loadConnections(QTextStream &in,
                         int &lineCount,
                         QVector<QVector<QPair<int, int>>> &conn);
    bool loadTrafficLights(QTextStream &in,
                           int &lineCount,
                           QVector<Trafficlight*> &trafficLights,
                           QVector<int> &trafficlightConnections);
    bool loadData(QFile* file, LoadFileData &data, int &lineCount);
    void handleData(LoadFileData &data);
    bool saveFile(const QString &fileName);
    void writeSaveData(SaveFileData &data);
    void saveCarGenerators(QTextStream &out,
                           QVector<CarGenerator*> &carGenerators,
                           QHash<RoadPoint*, int> &hash);
    void savePoints(QTextStream &out, QVector<RoadPoint*> &points);
    void saveConnections(QTextStream &out,
                         QVector<RoadPoint*> points,
                         QVector<QList<RoadPoint*>> conn,
                         QHash<RoadPoint*, int> &hash);
    void saveTrafficLights(QTextStream &out,
                           QVector<Trafficlight*> &trafficLights,
                           QHash<RoadPoint*, int> hash);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fileName);
    QMenu* createItemMenu();
private:
    //QPlainTextEdit *m_Workspace;
    Workspace *m_View;
    WorkspaceScene *m_Scene;
    QString m_CurFile;
    QMenu* m_itemMenu;
    QDockWidget* m_DockWidget;
};
#endif // MAINWINDOW_H
