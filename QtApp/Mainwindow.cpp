#include "Mainwindow.h"
#include <QtWidgets>
#include "Item.h"
#include <QVector>
#include <QList>
#include <QHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)/*, m_Workspace(new QPlainTextEdit(this))*/
{
    m_itemMenu = createItemMenu();

    m_Scene = new WorkspaceScene(m_itemMenu, QRectF(0.0f, 0.0f, 1080.0f, 720.0f), this);
    //m_Scene->addRect(QRectF(0.0f, 0.0f, 100.0f, 100.0f), QPen(QColor(Qt::yellow)), QBrush(Qt::yellow));
    m_View = new QGraphicsView(m_Scene, this);
    setCentralWidget(m_View);


    createActions();
    createStatusBar();
    readSettings();
//    connect(m_Workspace->document(), &QTextDocument::contentsChanged,
//            this, &MainWindow::slotDocumentWasModified);
    connect(this, &MainWindow::signalAction, m_Scene, &WorkspaceScene::slotSetAction);

//#ifndef QT_NO_SESSIONMANAGER
//    QGuiApplication::setFallbackSessionManagementEnabled(false);
//    connect(qApp, &QGuiApplication::commitDataRequest,
//            this, &MainWindow::commitData);
//#endif

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
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

    const QIcon cutIcon = QIcon::fromTheme("edit-cut");
    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip(tr("Cut current selection to the clipboard"));
    //connect(cutAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::cut);
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy");
    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip(tr("Copy current selection to the clipboard"));
    //connect(copyAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::copy);
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste");
    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip(tr("Paste current selection from the clipboard"));
    //connect(pasteAct, &QAction::triggered, m_Workspace, &QPlainTextEdit::paste);
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);

    QMenu *modelMenu = menuBar()->addMenu(tr("&Model"));
    //QAction *runAct = new QAction();
    //runAct->setShortcut

    QAction *runAct = modelMenu->addAction(tr("&Run"), this, &MainWindow::slotRun);
    runAct->setToolTip(tr("Run model application"));

    QToolBar *toolsToolBar = new QToolBar(tr("Toolbar"), this);
    addToolBar(Qt::LeftToolBarArea, toolsToolBar);
    QAction *addRoadAct = toolsToolBar->addAction(tr("Add Road"), this, &MainWindow::slotAddRoad);
    QAction *addCarGeneratorAct = toolsToolBar->addAction(tr("Add Car Generator"), this, &MainWindow::slotAddCarGenerator);
    QAction *moveAct = toolsToolBar->addAction(tr("Move hand"), this, &MainWindow::slotMove);

    menuBar()->addSeparator();

    //QToolBar *toolsToolBar = new QToolBar(tr("&Tools"));


    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::slotAbout);
    aboutAct->setToolTip(tr("Show the application's about box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setToolTip(tr("Show the Qt about box"));

    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
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
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}
bool MainWindow::slotSave()
{
    if (m_CurFile.isEmpty())
        return slotSaveAs();
    return saveFile(m_CurFile);
}
bool MainWindow::slotSaveAs()
{
//    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
//                                                    m_CurFile);
//    if (fileName.isEmpty())
//        return false;
 //   return saveFile(fileName);
    m_View->hide();
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    //dialog.exec();
    if (dialog.exec() != QFileDialog::Accepted) {
        return false;
    }
    return saveFile(dialog.getSaveFileName());
}
void MainWindow::slotAbout()
{
    QMessageBox::about(this, tr("About application"),
                       tr("Will be updated"));
}
void MainWindow::slotDocumentWasModified()
{
    //setWindowModified(m_Workspace->document()->isModified());
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
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }
    QTextStream in(&file);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    //m_Workspace->setPlainText(in.readAll());
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
//    if (!m_Workspace->document()->isModified())
//        return true;
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
     m_View->show();
    QString errorMessage;
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly| QFile::Text)) {
        QVector<CarGenerator*> carGenerators;
        QVector<QPointF> points;
        QVector<QList<RoadPoint*>> conn;
        QHash<RoadPoint*, int> hash;
        CarGenerator* gen;
        RoadPoint* pnt;
        QList<QGraphicsItem*> items = m_Scene->items();
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
                    points.push_back(pnt->getPoint());
                    conn.push_back(pnt->getConnections());
                break;
                default: break;
            }
        }
        QTextStream out(&file);
        out << "#CarGenerators\n{\n";
        for (int i = 0; i < carGenerators.size(); ++i) {
            QString str = QString("\t%1 %2 %3\n").arg(hash[carGenerators[i]->getConnection()])
                    .arg(carGenerators[i]->getConnection()->getPoint().x()).arg(carGenerators[i]->getConnection()->getPoint().y());
            out << str;
        }
        out << "}\n";
        out << "#Points\n{\n";
        for (int i = 0; i < points.size(); ++i) {
            QString str = QString("\t%1 %2 %3\n").arg(i).arg(points[i].x()).arg(points[i].y());
            out << str;
        }
        out << "}\n";
        out << "#Connections\n{\n";
        for (int i = 0; i < conn.size(); ++i) {
            for (int j = 0; j < conn[i].size(); ++j) {
                QString str = QString("\t%1 %2\n").arg(i).arg(hash[conn[i][j]]);
                out << str;
            }

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
    //m_Workspace->document()->setModified(false);
    setWindowModified(false);
    QString shownName(fileName);
    if (shownName.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
 }
 QString MainWindow::strippedName(const QString &fullfileName)
 {
    return QFileInfo(fullfileName).fileName();
 }

 void MainWindow::slotRun()
 {

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

 QMenu* MainWindow::createItemMenu()
 {
    QMenu* menu = new QMenu(tr("Context menu"), this);
    return menu;
 }
