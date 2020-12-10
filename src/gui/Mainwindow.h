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
    void slotAddCarGenerator();
    void slotAddTrafficlight();
    void slotMove();
    void slotAddDockWidget(QWidget* widget);
    void slotRemoveDockWidget(QWidget* widget);
    void sceneScaleChanged(const QString &scale);
signals:
    void signalAction(WorkspaceScene::ActionType);
private:

    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
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
