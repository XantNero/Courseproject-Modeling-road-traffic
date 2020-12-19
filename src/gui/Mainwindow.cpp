#include "Mainwindow.h"
#include <QtWidgets>
#include "Item.h"
#include <QVector>
#include <QList>
#include <QScreen>
#include <QHash>
#include <cstdio>
#include <QProcess>
#include <QPair>
#include "ItemWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)/*, m_Workspace(new QPlainTextEdit(this))*/
{

    m_itemMenu = createItemMenu();
    m_Scene = new WorkspaceScene(m_itemMenu,
                                 QGuiApplication::screens()[0]->geometry(),
                                 this);
    //m_Scene->addRect(QRectF(0.0f, 0.0f, 100.0f, 100.0f), QPen(QColor(Qt::yellow)), QBrush(Qt::yellow));
    m_View = new Workspace(m_Scene, this);
    setCentralWidget(m_View);

    m_DockWidget = new QDockWidget(tr("Settings widget"));
    createMenuBarActions();
    createScaleAction();
    createToolBarActions();
    createStatusBar();
    createItemMenuActions();
    readSettings();
    connect(m_View, &Workspace::signalModified,
            this, &MainWindow::slotWorkspaceIsModified);
    connect(this, &MainWindow::signalAction,
            m_Scene, &WorkspaceScene::slotSetAction);
    connect(m_Scene, &WorkspaceScene::signalAddDockWidget,
            this, &MainWindow::slotAddDockWidget);

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
    m_Scene->update();
    m_View->update();
}

void MainWindow::createToolBarActions()
{
    QToolBar *toolsToolBar = new QToolBar(tr("Toolbar"), this);
    addToolBar(Qt::LeftToolBarArea, toolsToolBar);

    const QIcon handIcon("res/textures/hand.png");
    QAction *moveAct = new QAction(handIcon, tr("Move hand"), toolsToolBar);
    connect(moveAct, &QAction::triggered, this, &MainWindow::slotMove);
    toolsToolBar->addAction(moveAct);

    const QIcon addRoadPointIcon("res/textures/point.png");
    QAction *addRoadPointAct = 
        new QAction(addRoadPointIcon, tr("Add road point"));
    connect(addRoadPointAct, &QAction::triggered,
            this, &MainWindow::slotAddRoadPoint);
    toolsToolBar->addAction(addRoadPointAct);

    const QIcon addRoadIcon("res/textures/road.png");
    QAction *addRoadAct = 
        new QAction(addRoadIcon, tr("Add road"), toolsToolBar);
    connect(addRoadAct, &QAction::triggered, this, &MainWindow::slotAddRoad);
    toolsToolBar->addAction(addRoadAct);

    const QIcon addCarGeneratorIcon("res/textures/carIcon.png");
    QAction *addCarGeneratorAct = 
        new QAction(addCarGeneratorIcon, tr("Add car generator"), toolsToolBar);
    connect(addCarGeneratorAct, &QAction::triggered,
            this, &MainWindow::slotAddCarGenerator);
    toolsToolBar->addAction(addCarGeneratorAct);

    const QIcon lightIcon("res/textures/traffic-light-icon.png");
    QAction *trafficlightAct =
        new QAction(lightIcon, tr("Add trafficlight"), toolsToolBar);
    connect(trafficlightAct, &QAction::triggered,
        this, &MainWindow::slotAddTrafficlight);
    toolsToolBar->addAction(trafficlightAct);
}

void MainWindow::createScaleAction()
{
    QToolBar *scaleToolbar = addToolBar(tr("&Scale"));

    QComboBox* sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, &QComboBox::currentTextChanged,
            this, &MainWindow::sceneScaleChanged);
    scaleToolbar->addWidget(sceneScaleCombo);
}

void MainWindow::createItemMenuActions()
{
    const QIcon deleteIcon =
        QIcon::fromTheme("edit-delete", QIcon("res/textures/edit-delete.svg"));
    QAction* deleteAction = new QAction(deleteIcon, tr("&Delete"), m_itemMenu);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setToolTip(tr("Delete selected items"));
    connect(deleteAction, &QAction::triggered,
        m_Scene, &WorkspaceScene::slotDelete);
    m_itemMenu->addAction(deleteAction);

    QAction* connectMainAction =
        new QAction(tr("Connect main road"), m_itemMenu);
    connectMainAction->setToolTip(tr("Connect items"));
    connect(connectMainAction, &QAction::triggered,
            m_Scene, &WorkspaceScene::slotConnectMainRoad);
    m_itemMenu->addAction(connectMainAction);


    QAction* connectNotMainAction =
        new QAction(tr("Connect not main road"), m_itemMenu);
    connectNotMainAction->setToolTip(tr("Connect items"));
    connect(connectNotMainAction, &QAction::triggered,
            m_Scene, &WorkspaceScene::slotConnectNotMainRoad);
    m_itemMenu->addAction(connectNotMainAction);

    QAction* disconnectAct = new QAction(tr("&Disconnect"), m_itemMenu);
    disconnectAct->setToolTip(tr("Disconnect items"));
    connect(disconnectAct, &QAction::triggered,
            m_Scene, &WorkspaceScene::slotDisconnect);
    m_itemMenu->addAction(disconnectAct);
}

void MainWindow::createMenuBarActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon newIcon =
        QIcon::fromTheme("document-new",
                         QIcon("res/textures/document-new.svg"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::slotNewFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon =
        QIcon::fromTheme("document-open",
                         QIcon("res/textures/document-open.svg"));
    QAction *openAct = new QAction(openIcon, tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::slotOpen);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon =
        QIcon::fromTheme("document-save",
                         QIcon("res/textures/document-save.svg"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip(tr("Save a file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::slotSave);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon =
        QIcon::fromTheme("document-save-as",
                         QIcon("res/textures/document-save-as.svg"));
    QAction *saveAsAct = new QAction(saveAsIcon, tr("&Save As"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setToolTip(tr("Save a file as"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::slotSaveAs);
    fileMenu->addAction(saveAsAct);
    fileToolBar->addAction(saveAsAct);

    fileMenu->addSeparator();

    const QIcon exitIcon =
        QIcon::fromTheme("application-exit",
                         QIcon("res/textures/application-exit.svg"));
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("&Exit"),
                                           this, &QWidget::close);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setToolTip(tr("Exit the program"));

//    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
//    QToolBar *editToolBar = addToolBar(tr("Edit"));

//    const QIcon cutIcon = QIcon::fromTheme("edit-cut");
//    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
//    cutAct->setShortcut(QKeySequence::Cut);
//    cutAct->setToolTip(tr("Cut current selection to the clipboard"));
//    //connect(cutAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::cut);
//    editMenu->addAction(cutAct);
//    editToolBar->addAction(cutAct);

//    const QIcon copyIcon = QIcon::fromTheme("edit-copy");
//    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
//    copyAct->setShortcut(QKeySequence::Copy);
//    copyAct->setToolTip(tr("Copy current selection to the clipboard"));
//    //connect(copyAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::copy);
//    editMenu->addAction(copyAct);
//    editToolBar->addAction(copyAct);

//    const QIcon pasteIcon = QIcon::fromTheme("edit-paste");
//    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
//    pasteAct->setShortcut(QKeySequence::Paste);
//    pasteAct->setToolTip(tr("Paste current selection from the clipboard"));
//    //connect(pasteAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::paste);
//    editMenu->addAction(pasteAct);
//    editToolBar->addAction(pasteAct);

    QMenu *modelMenu = menuBar()->addMenu(tr("&Model"));

    const QIcon runIcon("res/textures/play.png");
    QAction *runAct = new QAction(runIcon, tr("&Run"));
    connect(runAct, &QAction::triggered, this, &MainWindow::slotRun);
    runAct->setToolTip(tr("Run model application"));
    modelMenu->addAction(runAct);

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"),
                                            this, &MainWindow::slotAbout);
    aboutAct->setToolTip(tr("Show the application's about box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"),
                                              qApp, &QApplication::aboutQt);
    aboutQtAct->setToolTip(tr("Show the Qt about box"));

//    cutAct->setEnabled(false);
//    copyAct->setEnabled(false);
    //connect(m_Workspace, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(m_Workspace, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
}

void MainWindow::slotNewFile()
{
    if (maybeSave()) {
        //m_Workspace->clear();
        setCurrentFile(QString());
    }
}
void MainWindow::slotOpen()
{
    m_View->hide();
    if (maybeSave()) {
        QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                        QDir::currentPath(), tr("MDL (*.mdl)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
    m_View->show();
}
bool MainWindow::slotSave()
{
    if (m_CurFile.isEmpty())
        return slotSaveAs();
    return saveFile(m_CurFile);
}
bool MainWindow::slotSaveAs()
{
    m_View->hide();
    QString fileName =
        QFileDialog::getSaveFileName(this, tr("Save file"),
                                     QDir::currentPath(), tr("MDL (*.mdl)"));
    m_View->show();
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}
void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About application"),
                       tr("Object of my cursework is "
                          "\"Modelling road traffic\". "
                          "This project is gui-application "
                           "with tool for making model of "
                          "road traffic. This model can be "
                           "simulated with animation."));
}
void MainWindow::slotWorkspaceIsModified()
{
    setWindowModified(m_View->isUpdated());
}

 void MainWindow::closeEvent(QCloseEvent *event)
 {
    if (maybeSave()) {
        writeSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
 }

 void MainWindow::loadFile(const QString &fileName)
 {
    QFile file(fileName);
    QString errorMessage;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                             file.errorString()));
        return;
    }
    QList<QGraphicsItem*> items = m_Scene->items();
    for (auto item : items) {
        item->setSelected(true);
    }
    m_Scene->slotDelete();

    QTextStream in(&file);
    LoadFileData data;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    int lineCount = 0;


    QGuiApplication::restoreOverrideCursor();
    if (!loadData(&file, data, lineCount)) {
        errorMessage = tr("Cannot read file %1 line[%2]:\nfile is broken.")
                .arg(QDir::toNativeSeparators(fileName)).arg(lineCount);
        QMessageBox::warning(this, "Application", errorMessage);
        return;
    }
    handleData(data);
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
 }

 void MainWindow::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready!"));
 }
 void MainWindow::readSettings()
 {
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    const QByteArray geometry =
        settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        QSize availableGeometry = qApp->screens()[0]->size();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move(availableGeometry.width() - width() / 2,
             availableGeometry.height() - height() / 2);
    }
    else {
        restoreGeometry(geometry);
    }

 }
 void MainWindow::writeSettings()
 {
    QSettings settings(QCoreApplication::organizationName(),
                       QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
 }
 bool MainWindow::maybeSave()
 {
     if (!m_View->isUpdated())
        return true;
    const QMessageBox::StandardButton ret =
            QMessageBox::warning(this,
                                 tr("Application"),
                                tr("Do you want save your changes?"),
                                 QMessageBox::Save |
                                 QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Save:
            return slotSave();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
 }

 bool MainWindow::loadCarGenerators(QTextStream &in,
                                    int &lineCount,
                                    QVector<CarGenerator*> &carGenerators,
                                    QVector<int> &carGeneratorsConnections)
 {
     QString line;

     while (line != "{") {
         ++lineCount;
         line = in.readLine();
     }
     int connectionID;
     float posX, posY;
     int rate;
     line = in.readLine();
     ++lineCount;
     while (line != "}") {
         int valueCount = 0;
         valueCount = sscanf(line.toStdString().c_str(),
                              "%d%f%f%d",
                               &connectionID, &posX, &posY, &rate);
         if (valueCount != 4) {
             return false;
         }
         carGenerators.push_back(new CarGenerator(m_itemMenu,
                                                  QPointF(posX, posY), rate));
         carGeneratorsConnections.push_back(connectionID);
         line = in.readLine();
         ++lineCount;
     }
     return true;
 }

 bool MainWindow::loadPoints(QTextStream &in,
                             int &lineCount,
                             QVector<RoadPoint*> &points)
 {
     QString line;
     while (line != "{") {
         line = in.readLine();
         ++lineCount;
     }
     int pointID;;
     float posX, posY;
     line = in.readLine();
     ++lineCount;
     while (line != "}") {
         int valueCount = 0;
         valueCount = sscanf(line.toStdString().c_str(),
                             "%d%f%f",
                              &pointID, &posX, &posY);
         if (valueCount != 3) {
            return false;
         }
         RoadPoint* point = new RoadPoint(m_itemMenu, QPointF(posX, posY));
         if (pointID >= points.size()) {
             points.resize(pointID + 1);
         }
         points[pointID] = point;
         line = in.readLine();
         ++lineCount;
     }
     return true;
 }

 bool MainWindow::loadConnections(QTextStream &in,
                                  int &lineCount,
                                  QVector<QVector<QPair<int, int>>> &conn)
 {
     QString line;
     while (line != "{") {
         line = in.readLine();
         ++lineCount;
     }
     int from, to, roadType;
     line = in.readLine();
     ++lineCount;
     while (line != "}") {
         int valueCount = 0;
         valueCount = sscanf(line.toStdString().c_str(),
                             "%d%d%d",
                              &from, &to, &roadType);
         if (valueCount != 3) {
             return false;
         }
         if (from >= conn.size()) {
             conn.resize(from + 1);
         }
         conn[from].push_back({to, roadType});
         line = in.readLine();
         ++lineCount;
     }
     return true;
 }

 bool MainWindow::loadTrafficLights(QTextStream &in,
                                    int &lineCount,
                                    QVector<Trafficlight*> &trafficLights,
                                    QVector<int> &trafficlightConnections)
 {
     QString line;
     while (line != "{") {
         line = in.readLine();
         ++lineCount;
     }
     int green, yellow, red, id;
     float x, y;
     line = in.readLine();
     ++lineCount;
     while (line != "}") {
         int valueCount = 0;
         valueCount = sscanf(line.toStdString().c_str(),
                             "%d%f%f%d%d%d",
                             &id, &x, &y, &green, &yellow, &red);
         if (valueCount != 6) {
             return false;
         }
         trafficLights.push_back(new Trafficlight(m_itemMenu,
                                                  QPointF(x, y),
                                                  {green, yellow, red}));
         trafficlightConnections.push_back(id);
         line = in.readLine();
         ++lineCount;
     }
     return true;
 }

 bool MainWindow::loadData(QFile* file, LoadFileData &data, int &lineCount)
 {
     QTextStream in(file);
     QString line;
     while (!in.atEnd()) {
         line = in.readLine();
         ++lineCount;
         if (line == "#CarGenerators") {
             if (!loadCarGenerators(in, lineCount,
                                    data.carGenerators,
                                    data.carGeneratorsConnections)) {
                  return false;
             }
         }
         else if (line == "#Points") {
             if (!loadPoints(in, lineCount, data.points)) {
                  return false;
             }
         }
         else if (line == "#Connections") {
             if (!loadConnections(in, lineCount, data.conn)) {
                  return false;
             }
         }
         else if (line == "#TrafficLights") {
             if (!loadTrafficLights(in, lineCount, data.trafficLights,
                                    data.trafficlightConnections)) {
                 return false;
             }
         }
         else if (line == "")
             continue;
         else {
             return false;
         }
     }
     return true;
 }

 void MainWindow::handleData(LoadFileData &data)
 {
     data.conn.resize(data.points.size());
     for (int i = 0; i < data.carGenerators.size(); ++i) {
         m_View->scene()->addItem(data.carGenerators[i]);
         Road* road = 
            new Road(m_itemMenu,
                     data.carGenerators[i],
                     data.points[data.carGeneratorsConnections[i]],
                     Road::Connection);
         data.carGenerators[i]->
            connect(data.points[data.carGeneratorsConnections[i]], road);
         data.points[data.carGeneratorsConnections[i]]->
            connected(data.carGenerators[i], road);
     }
     for (int i = 0; i < data.points.size(); ++i) {
         m_View->scene()->addItem(data.points[i]);
         for (int j = 0; j < data.conn[i].size(); ++j) {
             Road* road = 
                new Road(m_itemMenu,
                         data.points[i],
                         data.points[data.conn[i][j].first],
                         data.conn[i][j].second == 1 ?
                            Road::Main : Road::NotMain);
             data.points[i]->connect(data.points[data.conn[i][j].first], road);
             data.points[data.conn[i][j].first]->
                connected(data.points[i], road);
         }
     }
     for (int i = 0; i < data.trafficLights.size(); ++i) {
         m_View->scene()->addItem(data.trafficLights[i]);
         Road* road = 
            new Road(m_itemMenu,
                     data.trafficLights[i],
                     data.points[data.trafficlightConnections[i]],
                     Road::Connection);
         data.trafficLights[i]->
            connect(data.points[data.trafficlightConnections[i]], road);
         data.points[data.trafficlightConnections[i]]->
            connected(data.trafficLights[i], road);
     }
 }
 bool MainWindow::saveFile(const QString &fileName)
 {

    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly| QFile::Text)) {
        SaveFileData data;
        writeSaveData(data);
        QTextStream out(&file);
        bool errorFlag = false;

        errorFlag |= !saveCarGenerators(out, data.carGenerators);
        errorFlag |= !savePoints(out, data.points);
        errorFlag |= !saveConnections(out, data.points, data.conn);
        errorFlag |= !saveTrafficLights(out, data.trafficlights);


        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2")
                            .arg(QDir::toNativeSeparators(fileName),
                             file.errorString());
        }
        else if (errorFlag) {
            errorMessage = tr("Cannot write file %1:\n%2")
                            .arg(QDir::toNativeSeparators(fileName),
                             "saving information is incorrect");
        }
    }
    else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2")
                        .arg(QDir::toNativeSeparators(fileName),
                         file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();
    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, "Application", errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;

 }

 void MainWindow::writeSaveData(SaveFileData &data)
 {
     CarGenerator* gen;
     RoadPoint* pnt;
     Trafficlight* light;
     QList<QGraphicsItem*> items = m_Scene->items();

     for (unsigned int i = 0; i < items.size(); ++i) {
         switch (items[i]->type()) {
             case (int)ModelTypes::CarGenerator:
                 gen = dynamic_cast<CarGenerator*>(items[i]);
                 data.carGenerators.push_back(gen);
             break;
             case (int)ModelTypes::RoadPoint:
                 pnt = dynamic_cast<RoadPoint*>(items[i]);
                 pnt->setIndex(data.points.size());
                 data.points.push_back(pnt);
                 data.conn.push_back(pnt->getConnections());
             break;
             case (int)ModelTypes::Trafficlight:
                 light = dynamic_cast<Trafficlight*>(items[i]);
                 //TODO: errror
                 data.trafficlights.push_back(light);
             break;
             default: break;
         }
     }
 }

 bool MainWindow::saveCarGenerators(QTextStream &out,
                                    QVector<CarGenerator *> &carGenerators)
 {
     out << "#CarGenerators\n{\n";
     for (int i = 0; i < carGenerators.size(); ++i) {
         QList<RoadPoint*>conn =  carGenerators[i]->getConnections();
         if (conn.size() == 0)
             return false;
         QString str = QString("\t%1 %2 %3 %4\n").arg(conn[0]->getIndex())
                       .arg(carGenerators[i]->scenePos().x())
                       .arg(carGenerators[i]->scenePos().y())
                       .arg(carGenerators[i]->getRate());
         out << str;
     }
     out << "}\n";
     return true;
 }

 bool MainWindow::savePoints(QTextStream &out, QVector<RoadPoint *> &points)
 {
     out << "#Points\n{\n";
     for (int i = 0; i < points.size(); ++i) {
         QString str = QString("\t%1 %2 %3\n")
                        .arg(i).arg(points[i]->getPoint().x())
                        .arg(points[i]->getPoint().y());
         out << str;
     }
     out << "}\n";
     return true;
 }

 bool MainWindow::saveConnections(QTextStream &out,
                                  QVector<RoadPoint*> points,
                                  QVector<QList<RoadPoint*>> conn)
 {
     out << "#Connections\n{\n";
     for (int i = 0; i < conn.size(); ++i) {
         for (int j = 0; j < conn[i].size(); ++j) {
              Road::Type connectionType = points[i]->getRoadType(conn[i][j]);
             int fl_mainRoad = connectionType == Road::Main ? 1 : 0;
             QString str = QString("\t%1 %2 %3\n")
                            .arg(i).arg(conn[i][j]->getIndex()).arg(fl_mainRoad);
             out << str;
         }

     }
     out << "}\n";
     return true;
 }

 bool MainWindow::saveTrafficLights(QTextStream &out,
                                    QVector<Trafficlight *> &trafficlights)
 {
     out << "#TrafficLights\n{\n";
     //TODO:errror
     for (int i = 0; i < trafficlights.size(); ++i) {
         QList<RoadPoint*> conn = trafficlights[i]->getConnections();
         if (conn.size() == 0)
             return false;
         LightTimings time = trafficlights[i]->getTimings();
         QString str = QString("\t%1 %2 %3 %4 %5 %6\n")
                        .arg(conn[0]->getIndex())
                        .arg(trafficlights[i]->getPoint().x())
                        .arg(trafficlights[i]->getPoint().y())
                        .arg(time.green)
                        .arg(time.yellow)
                        .arg(time.red);
         out << str;
     }
     out << "}\n";
     return true;
 }
 void MainWindow::setCurrentFile(const QString &fileName)
 {
    m_CurFile = fileName;
    m_View->setUpdated(false);
    setWindowModified(false);
    QString shownName(fileName);
    if (shownName.isEmpty())
        shownName = "untitled.mdl";
    setWindowFilePath(shownName);
 }
 QString MainWindow::strippedName(const QString &fullfileName)
 {
    return QFileInfo(fullfileName).fileName();
 }

 void MainWindow::slotRun()
 {
     QProcess* model = new QProcess(this);
    QStringList l = QStringList(m_CurFile);
     model->setProgram("model");
     model->setArguments(l);
     model->start();
 }

 void MainWindow::slotAddRoad()
 {
     emit signalAction(WorkspaceScene::ActionType::AddRoad);
 }

 void MainWindow::slotAddRoadPoint()
 {
     emit signalAction(WorkspaceScene::ActionType::AddRoidPoint);
 }

 void MainWindow::slotAddCarGenerator()
 {
    emit signalAction(WorkspaceScene::ActionType::AddCarGenerator);
 }

 void MainWindow::slotMove()
 {
     emit signalAction(WorkspaceScene::ActionType::Move);
 }

 void MainWindow::slotAddDockWidget(QWidget *widget)
 {
     m_DockWidget->setWidget(widget);
     addDockWidget(Qt::RightDockWidgetArea, m_DockWidget);
 }

 void MainWindow::slotRemoveDockWidget(QWidget *widget)
 {
     removeDockWidget(m_DockWidget);
 }

 void MainWindow::slotAddTrafficlight()
 {
     emit signalAction(WorkspaceScene::ActionType::AddTrafficlight);
 }

 QMenu* MainWindow::createItemMenu()
 {
    QMenu* menu = new QMenu(tr("Context menu"), this);
    return menu;
 }

 void MainWindow::sceneScaleChanged(const QString &scale)
 {
     double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
     QTransform oldMatrix = m_View->transform();
     m_View->resetTransform();
     m_View->translate(oldMatrix.dx(), oldMatrix.dy());
     m_View->scale(newScale, newScale);
 }
