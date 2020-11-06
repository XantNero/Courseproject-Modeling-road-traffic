#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtWidgets>
#include <QMainWindow>

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
    void slotDocumentWasModified();

private:

    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fileName);

private:
    QPlainTextEdit *m_Workspace;
    QString m_CurFile;
};
#endif // MAINWINDOW_H
