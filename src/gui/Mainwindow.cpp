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
#include "TrafficlightWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)/*, m_Workspace(new QPlainTextEdit(this))*/
{


    m_itemMenu = createItemMenu();
    m_Scene = new WorkspaceScene(m_itemMenu, QGuiApplication::screens()[0]->geometry(), this);
    //m_Scene->addRect(QRectF(0.0f, 0.0f, 100.0f, 100.0f), QPen(QColor(Qt::yellow)), QBrush(Qt::yellow));
    m_View = new Workspace(m_Scene, this);
    setCentralWidget(m_View);

    m_DockWidget = new QDockWidget(tr("Traffilclight widget"));
    createActions();
    createStatusBar();
    readSettings();
    connect(m_View, &Workspace::signalModified, this, &MainWindow::slotWorkspaceIsModified);
    connect(this, &MainWindow::signalAction, m_Scene, &WorkspaceScene::slotSetAction);
    connect(m_Scene, &WorkspaceScene::signalAddDockWidget, this, &MainWindow::slotAddDockWidget);

//#ifndef QT_NO_SESSIONMANAGER
//    QGuiApplication::setFallbackSessionManagementEnabled(false);
//    connect(qApp, &QGuiApplication::commitDataRequest,
//            this, &MainWindow::commitData);
//#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
    m_Scene->update();
    m_View->update();
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new");
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::slotNewFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

    const QIcon openIcon = QIcon::fromTheme("document-open");
    QAction *openAct = new QAction(openIcon, tr("&Open"), this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::slotOpen);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save");
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip(tr("Save a file"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::slotSave);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAct = new QAction(saveAsIcon, tr("&Save As"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setToolTip(tr("Save a file as"));
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::slotSaveAs);
    fileMenu->addAction(saveAsAct);
    fileToolBar->addAction(saveAsAct);

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("&Exit"), this, &QWidget::close);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setToolTip(tr("Exit the program"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

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
    //QAction *runAct = new QAction();
    //runAct->setShortcut

    QAction *runAct = modelMenu->addAction(tr("&Run"), this, &MainWindow::slotRun);
    runAct->setToolTip(tr("Run model application"));

    QToolBar *toolsToolBar = new QToolBar(tr("Toolbar"), this);
    addToolBar(Qt::LeftToolBarArea, toolsToolBar);

    const QIcon addRoadIcon("res/textures/road.png");
    QAction *addRoadAct = new QAction(addRoadIcon, tr("Add road"), toolsToolBar);
    connect(addRoadAct, &QAction::triggered, this, &MainWindow::slotAddRoad);
    toolsToolBar->addAction(addRoadAct);

    const QIcon addCarGeneratorIcon("res/textures/carIcon.png");
    QAction *addCarGeneratorAct = new QAction(addCarGeneratorIcon, tr("Add car generator"), toolsToolBar);
    connect(addCarGeneratorAct, &QAction::triggered, this, &MainWindow::slotAddCarGenerator);
    toolsToolBar->addAction(addCarGeneratorAct);

    const QIcon handIcon("res/textures/hand.png");
    QAction *moveAct = new QAction(handIcon, tr("Move hand"), toolsToolBar);
    connect(moveAct, &QAction::triggered, this, &MainWindow::slotMove);
    toolsToolBar->addAction(moveAct);

    const QIcon lightIcon("res/textures/traffic-light-icon.png");
    QAction *trafficlightAct = new QAction(lightIcon, tr("Add trafficlight"), toolsToolBar);
    connect(trafficlightAct, &QAction::triggered, this, &MainWindow::slotAddTrafficlight);
    toolsToolBar->addAction(trafficlightAct);

    menuBar()->addSeparator();

    //QToolBar *toolsToolBar = new QToolBar(tr("&Tools"));


    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::slotAbout);
    aboutAct->setToolTip(tr("Show the application's about box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setToolTip(tr("Show the Qt about box"));

//    cutAct->setEnabled(false);
//    copyAct->setEnabled(false);
    //connect(m_Workspace, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    //connect(m_Workspace, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);



    const QIcon deleteIcon = QIcon::fromTheme("edit-delete");
    QAction* deleteAction = new QAction(deleteIcon, tr("&Delete"), m_itemMenu);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setToolTip(tr("Delete selected items"));
    connect(deleteAction, &QAction::triggered, m_Scene, &WorkspaceScene::slotDelete);
    m_itemMenu->addAction(deleteAction);

    QAction* connectAction = new QAction(tr("&Connect"), m_itemMenu);
    connectAction->setToolTip(tr("Connect items"));
    connect(connectAction, &QAction::triggered, m_Scene, &WorkspaceScene::slotConnect);
    m_itemMenu->addAction(connectAction);

    QAction* disconnectAct = new QAction(tr("&Disconnect"), m_itemMenu);
    connectAction->setToolTip(tr("Disconnect items"));
    connect(disconnectAct, &QAction::triggered, m_Scene, &WorkspaceScene::slotDisconnect);
    m_itemMenu->addAction(disconnectAct);

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
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath(), tr("MDL (*.mdl)"));
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::currentPath(), tr("MDL (*.mdl)"));
    m_View->show();
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}
void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About application"),
                       tr("Will be updated"));
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
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QList<QGraphicsItem*> items = m_Scene->items();
    for (auto item : items) {
        item->setSelected(true);
    }
    m_Scene->slotDelete();

    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QString line;
    QVector<CarGenerator*> carGenerators;
    QVector<int> carGeneratorsConnections;
    QVector<int> trafficlightConnections;
    QVector<RoadPoint*> points;
    QVector<QVector<QPair<int, int>>> conn;
    QVector<Trafficlight*> trafficLights;
    while (!in.atEnd()) {
        line = in.readLine();
        if (line == "#CarGenerators") {
            while (line != "{")
                line = in.readLine();
            int connectionID;
            float posX, posY;
            line = in.readLine();
            while (line != "}") {
                sscanf(line.toStdString().c_str(), "%d%f%f", &connectionID, &posX, &posY);
                carGenerators.push_back(new CarGenerator(m_itemMenu, QPointF(posX, posY)));
                carGeneratorsConnections.push_back(connectionID);
                line = in.readLine();
            }
        }
        else if (line == "#Points") {
            while (line != "{")
                line = in.readLine();
            int pointID;;
            float posX, posY;
            line = in.readLine();
            while (line != "}") {
                sscanf(line.toStdString().c_str(), "%d%f%f", &pointID, &posX, &posY);
                RoadPoint* point = new RoadPoint(m_itemMenu, QPointF(posX, posY));
                if (pointID >= points.size()) {
                    points.resize(pointID + 1);
                }
                points[pointID] = point;
                line = in.readLine();
            }
        }
        else if (line == "#Connections") {
            while (line != "{")
                line = in.readLine();
            int from, to, roadType;
            line = in.readLine();
            while (line != "}") {
                sscanf(line.toStdString().c_str(), "%d%d%d", &from, &to, &roadType);
                if (from >= conn.size()) {
                    conn.resize(from + 1);
                }
                conn[from].push_back({to, roadType});
                line = in.readLine();

            }
        }
        else if (line == "#TrafficLights") {
            while (line != "{")
                line = in.readLine();
            int green, yellow, red, id;
            float x, y;
            line = in.readLine();
            while (line != "}") {
                sscanf(line.toStdString().c_str(), "%d%f%f%d%d%d", &id, &x, &y, &green, &yellow, &red);
                trafficLights.push_back(new Trafficlight(m_itemMenu, QPointF(x, y), {green, yellow, red}));
                trafficlightConnections.push_back(id);
                line = in.readLine();

            }
        }
        else if (line == "")
            continue;
        else {
            QMessageBox::warning(this, tr("Application"),
                                 tr("Cannot read file %1:\nfile is broken.")
                                 .arg(QDir::toNativeSeparators(fileName)));
            QGuiApplication::restoreOverrideCursor();
            return;
        }
    }
    conn.resize(points.size());
    for (int i = 0; i < carGenerators.size(); ++i) {
        m_View->scene()->addItem(carGenerators[i]);
        Road* road = new Road(m_itemMenu, carGenerators[i], points[carGeneratorsConnections[i]], Road::Connection);
        carGenerators[i]->connect(points[carGeneratorsConnections[i]], road);
        points[carGeneratorsConnections[i]]->connected(carGenerators[i], road);
    }
    for (int i = 0; i < points.size(); ++i) {
        m_View->scene()->addItem(points[i]);
        for (int j = 0; j < conn[i].size(); ++j) {
            Road* road = new Road(m_itemMenu, points[i], points[conn[i][j].first], conn[i][j].second == 1 ? Road::Main : Road::NotMain);
            points[i]->connect(points[conn[i][j].first], road);
            points[conn[i][j].first]->connected(points[i], road);
        }
    }
    for (int i = 0; i < trafficLights.size(); ++i) {
        m_View->scene()->addItem(trafficLights[i]);
        Road* road = new Road(m_itemMenu, trafficLights[i], points[trafficlightConnections[i]], Road::Connection);
        trafficLights[i]->connect(points[trafficlightConnections[i]], road);
        points[trafficlightConnections[i]]->connected(trafficLights[i], road);
    }
    QGuiApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
 }

 void MainWindow::createStatusBar()
 {
    statusBar()->showMessage(tr("Ready!"));
 }
 void MainWindow::readSettings()
 {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
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
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
 }
 bool MainWindow::maybeSave()
 {
     if (!m_View->isUpdated())
        return true;
    const QMessageBox::StandardButton ret =
            QMessageBox::warning(this, tr("Application"), tr("Do you want save your changes?"),
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
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
 bool MainWindow::saveFile(const QString &fileName)
 {

    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly| QFile::Text)) {
        QVector<CarGenerator*> carGenerators;
        QVector<RoadPoint*> points;
        QVector<QList<RoadPoint*>> conn;
        QHash<RoadPoint*, int> hash;
        CarGenerator* gen;
        RoadPoint* pnt;
        Trafficlight* light;
        QList<QGraphicsItem*> items = m_Scene->items();
        QVector<Trafficlight*> trafficlights;
        //std::sort(items.begin(), items.end(), [](const QGraphicsItem* &a, const QGraphicsItem* &b) { return a->type() <= b->type();} );
        for (unsigned int i = 0; i < items.size(); ++i) {
            switch (items[i]->type()) {
                case (int)ModelTypes::CarGenerator:
                    gen = dynamic_cast<CarGenerator*>(items[i]);
                    carGenerators.push_back(gen);
                break;
                case (int)ModelTypes::RoadPoint:
                    pnt = dynamic_cast<RoadPoint*>(items[i]);
                    hash.insert(pnt, points.size());
                    points.push_back(pnt);
                    conn.push_back(pnt->getConnections());
                break;
                case (int)ModelTypes::Trafficlight:
                    light = dynamic_cast<Trafficlight*>(items[i]);
                    //TODO: errror
                    trafficlights.push_back(light);
                break;
                default: break;
            }
        }
        QTextStream out(&file);
        out << "#CarGenerators\n{\n";
        for (int i = 0; i < carGenerators.size(); ++i) {
            QList<RoadPoint*>conn =  carGenerators[i]->getConnections();
            //TODO: error
            QString str = QString("\t%1 %2 %3\n").arg(hash[conn[0]])
                    .arg(carGenerators[i]->scenePos().x()).arg(carGenerators[i]->scenePos().y());
            out << str;
        }
        out << "}\n";
        out << "#Points\n{\n";
        for (int i = 0; i < points.size(); ++i) {
            QString str = QString("\t%1 %2 %3\n").arg(i).arg(points[i]->getPoint().x()).arg(points[i]->getPoint().y());
            out << str;
        }
        out << "}\n";
        out << "#Connections\n{\n";
        for (int i = 0; i < conn.size(); ++i) {
            for (int j = 0; j < conn[i].size(); ++j) {
                 Road::Type connectionType = points[i]->getRoadType(conn[i][j]);
                int fl_mainRoad = connectionType == Road::Main ? 1 : 0;
                QString str = QString("\t%1 %2 %3\n").arg(i).arg(hash[conn[i][j]]).arg(fl_mainRoad);
                out << str;
            }

        }
        out << "}\n";
        out << "#TrafficLights\n{\n";
        //TODO:errror
        for (int i = 0; i < trafficlights.size(); ++i) {
            LightTimings time = trafficlights[i]->getTimings();
            QString str = QString("\t%1 %2 %3 %4 %5 %6\n").arg(hash[trafficlights[i]->getConnections()[0]]).arg(trafficlights[i]->getPoint().x()).arg(trafficlights[i]->getPoint().y())
                                                        .arg(time.green).arg(time.yellow).arg(time.red);
            out << str;
        }
        out << "}\n";
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2")
                            .arg(QDir::toNativeSeparators(fileName), file.errorString());

        }
    }
    else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
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
     model->setProgram("/home/dmitry/Courseproject-Modelling-road-traffic/main");
     model->setArguments(l);
     model->start();
 }

 void MainWindow::slotAddRoad()
 {
    emit signalAction(WorkspaceScene::ActionType::AddRoad);
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
