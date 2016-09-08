#include "about.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new QLabel(ui->scrollArea);
    ui->scrollArea->setWidget(label);
    undoStack = new QUndoStack(this);
    createActions();
    createStatusBar();
    repaint();
    instrument = 1;
    color.setRgb(0,0,0);
    isStPolgn=false;
    isDblClick=false;
    amOfClBezie=0;
    widthOfPen=2;


    img.load(":/template.jpg");
    label->setPixmap(img);
    setCurrentFile(QString());

    //configure buttons
    ui->pushButton->setIcon(QIcon(":/pen.jpg"));
    ui->pushButton->setIconSize(QSize(30,30));

    ui->pushButton_3->setIcon(QIcon(":/lastic.jpg"));
    ui->pushButton_3->setIconSize(QSize(30,30));

    ui->pushButton_4->setIcon(QIcon(":/line.jpg"));
    ui->pushButton_4->setIconSize(QSize(30,30));

    ui->pushButton_5->setIcon(QIcon(":/circle.jpg"));
    ui->pushButton_5->setIconSize(QSize(30,30));

    ui->pushButton_6->setIcon(QIcon(":/rectangle.jpg"));
    ui->pushButton_6->setIconSize(QSize(30,30));

    ui->pushButton_7->setIcon(QIcon(":/polygon.jpg"));
    ui->pushButton_7->setIconSize(QSize(30,30));

    ui->pushButton_8->setIcon(QIcon(":/bezie.jpg"));
    ui->pushButton_8->setIconSize(QSize(30,30));


    //colors of buttons
    ui->pushButton_9->setStyleSheet("background-color: rgb(255,0,0)");

    ui->pushButton_10->setStyleSheet("background-color: rgb(255,128,64)");

    ui->pushButton_11->setStyleSheet("background-color: rgb(255,255,0)");

    ui->pushButton_12->setStyleSheet("background-color: rgb(0,128,0)");

    ui->pushButton_13->setStyleSheet("background-color: rgb(0,255,255)");

    ui->pushButton_14->setStyleSheet("background-color: rgb(0,0,255)");

    ui->pushButton_15->setStyleSheet("background-color: rgb(128,0,255)");

    ui->pushButton_16->setStyleSheet("background-color: rgb(0,0,0)");
}

void MainWindow::paintEvent(QPaintEvent *)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    if (instrument == 1)
    {
        if (isPressed)
        {
            painter.begin(&img);
            painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
            painter.drawLine(current, next);
            painter.end();
        }
        current=next;
        label->setPixmap(img);
    }

    if (instrument == 2)
    {
        painter.setRenderHint(QPainter::Antialiasing, false);
        if (isPressed)
        {
            painter.begin(&img);
            painter.setPen(QPen (Qt::white, widthOfPen+6, Qt::SolidLine));
            painter.drawLine(current, next);
            painter.end();
        }
        current=next;
        label->setPixmap(img);
    }

    if (instrument == 3)
    {
        imgTmp=img;
        if (isPressed)
        {
            painter.begin(&imgTmp);
            painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
            if (current != next)
                painter.drawLine(current, next);
            painter.end();
            label->setPixmap(imgTmp);
        }
    }
    if (instrument == 4)
    {
        imgTmp=img;
        if (isPressed)
        {
            painter.begin(&imgTmp);
            painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
            painter.drawEllipse(QPointF(current),next.x()-current.x(),next.y()-current.y());
            painter.end();
            label->setPixmap(imgTmp);
        }
    }
    if (instrument == 5)
    {
        imgTmp=img;
        if (isPressed)
        {
            painter.begin(&imgTmp);
            painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
            painter.drawRect(current.x(),current.y(),next.x()-current.x(),next.y()-current.y());
            painter.end();
            label->setPixmap(imgTmp);
        }
    }
    if (instrument == 6)
    {
        imgTmp=img;
        if (isPressed)
        {
            painter.begin(&imgTmp);
            painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
            if (current != next)
                painter.drawLine(current, next);
            painter.end();
            label->setPixmap(imgTmp);
        }
    }
    if (instrument == 7)
    {
        if (isPressed)
        {
            if (amOfClBezie==0)
            {
                imgTmp=img;
                painter.begin(&imgTmp);
                painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
                if (current != next)
                    painter.drawLine(current, next);
                painter.end();
            }
            if (amOfClBezie==1)
            {
                imgTmp=img;
                QPainterPath path;
                path.moveTo(current);
                path.quadTo(c1,endPoint);
                painter.begin(&imgTmp);
                painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
                painter.drawPath(path);
                painter.end();
            }
            if (amOfClBezie==2)
            {
                imgTmp=img;
                QPainterPath path;
                path.moveTo(current);
                path.cubicTo(c1,c2,endPoint);
                painter.begin(&imgTmp);
                painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
                painter.drawPath(path);
                painter.end();
            }
            label->setPixmap(imgTmp);
        }
    }
}



void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    isPressed = true;
    if (instrument != 7) amOfClBezie=0;
    if (instrument == 6)
    {
        if (isDblClick) isStPolgn=true;
        if (isStPolgn)
            current = ev->pos()-ui->scrollArea->geometry().topLeft()+
                    QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                           ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
        next = current;
        isDblClick=false;
    }
    else
    {
        if (instrument == 7)
        {
            if (amOfClBezie==3) amOfClBezie=0;
            if (amOfClBezie == 0)
                current = ev->pos()-ui->scrollArea->geometry().topLeft()+
                        QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                               ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
            next = current;
            if (amOfClBezie==1)
                c1 = ev->pos()-ui->scrollArea->geometry().topLeft()+
                        QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                               ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
            if (amOfClBezie==2)
                c2 = ev->pos()-ui->scrollArea->geometry().topLeft()+
                        QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                               ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
        }
        else
        {
            current = ev->pos()-ui->scrollArea->geometry().topLeft()+
                    QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                           ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
            next = current;
        }
    }
    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    next = ev->pos()-ui->scrollArea->geometry().topLeft()+
            QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                   ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
    if (amOfClBezie==1)
        c1=next;
    if (amOfClBezie==2)
        c2=next;
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    isPressed = false;
    next = ev->pos()-ui->scrollArea->geometry().topLeft()+
            QPoint(ui->scrollArea->horizontalScrollBar()->value(),
                   ui->scrollArea->verticalScrollBar()->value())-QPoint(1,55);
    if (instrument == 3)
    {
        drawLine();
    }
    if (instrument == 4)
    {
        drawEllipse();
    }
    if (instrument == 5)
    {
        drawRectangle();
    }
    if (instrument == 6)
    {
        drawPolygon();
    }
    if (instrument == 7)
    {
        if (amOfClBezie==0)
            endPoint=next;
        drawBezie();
        amOfClBezie++;
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    if (instrument == 6)
    {
        painter.begin(&img);
        painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
        painter.drawLine(current, currentTmp);
        painter.end();
        label->setPixmap(img);
    }
    isDblClick=true;
    repaint();
}

void MainWindow::pen()
{
    label->setCursor(QCursor(Qt::ArrowCursor));
    instrument=1;
}

void MainWindow::lastic()
{
    label->setCursor(QCursor(QBitmap(":/eraser.bmp")));
    instrument=2;
}

void MainWindow::line()
{
    instrument=3;
    label->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::drawLine()
{
    painter.begin(&img);
    painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
    if (current != next)
        painter.drawLine(current, next);
    painter.end();
    label->setPixmap(img);
    repaint();
}

void MainWindow::ellipse()
{
    instrument=4;
    label->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::drawEllipse()
{
    painter.begin(&img);
    painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
    painter.drawEllipse(QPointF(current),next.x()-current.x(),next.y()-current.y());
    painter.end();
    label->setPixmap(img);
    repaint();
}

void MainWindow::rectangle()
{
    instrument=5;
    label->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::drawRectangle()
{
    painter.begin(&img);
    painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
    painter.drawRect(current.x(),current.y(),next.x()-current.x(),next.y()-current.y());
    painter.end();
    label->setPixmap(img);
    repaint();
}

void MainWindow::polygon()
{
    instrument=6;
    isStPolgn=true;
    label->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::drawPolygon()
{
    if (isStPolgn)
        currentTmp=current;
    painter.begin(&img);
    painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
    if (current != next)
        painter.drawLine(current, next);
    painter.end();
    label->setPixmap(img);
    current=next;
    isStPolgn=false;
    repaint();
}

void MainWindow::bezie()
{
    instrument=7;
    label->setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::drawBezie()
{
    if (amOfClBezie==0)
    {
        QPixmap imgTmp2(img);
        painter.begin(&imgTmp2);
        painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
        if (current != next)
            painter.drawLine(current, next);
        painter.end();
        label->setPixmap(imgTmp2);
    }
    if (amOfClBezie==1)
    {
        QPixmap imgTmp2(img);
        QPainterPath path;
        path.moveTo(current);
        path.quadTo(c1,endPoint);
        painter.begin(&imgTmp2);
        painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
        painter.drawPath(path);
        painter.end();
        label->setPixmap(imgTmp);
    }
    if (amOfClBezie==2)
    {
        QPainterPath path;
        path.moveTo(current);
        path.cubicTo(c1,c2,endPoint);
        painter.begin(&img);
        painter.setPen(QPen (color, widthOfPen, Qt::SolidLine) ) ;
        painter.drawPath(path);
        painter.end();
    }
    repaint();
}

void MainWindow::colorRed()
{
    color.setRgb(255,0,0);
    ui->pushButton_16->setStyleSheet("background-color: rgb(255,0,0)");
    repaint();
}

void MainWindow::colorOrange()
{
    color.setRgb(255,128,64);
    ui->pushButton_16->setStyleSheet("background-color: rgb(255,128,64)");
}

void MainWindow::colorYellow()
{
    color.setRgb(255,255,0);
    ui->pushButton_16->setStyleSheet("background-color: rgb(255,255,0)");
}

void MainWindow::colorGreen()
{
    color.setRgb(0,128,0);
    ui->pushButton_16->setStyleSheet("background-color: rgb(0,128,0)");
}

void MainWindow::colorLightBlue()
{
    color.setRgb(0,255,255);
    ui->pushButton_16->setStyleSheet("background-color: rgb(0,255,255)");
}

void MainWindow::colorDarkBlue()
{
    color.setRgb(0,0,255);
    ui->pushButton_16->setStyleSheet("background-color: rgb(0,0,255)");
}

void MainWindow::colorViolette()
{
    color.setRgb(128,0,255);
    ui->pushButton_16->setStyleSheet("background-color: rgb(128,0,255)");
}

void MainWindow::scale(int s)
{
    switch (s) {
    case 0:
        widthOfPen=2;
        break;
    case 100:
        widthOfPen=3;
        break;
    case 200:
        widthOfPen=4;
        break;
    case 300:
        widthOfPen=5;
        break;
    case 400:
        widthOfPen=6;
        break;
    case 500:
        widthOfPen=7;
        break;
    }
}


//+
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

//+
void MainWindow::newFile()
{
    if (maybeSave()) {
        img.load(":/template.jpg");
        label->setPixmap(img);
        setCurrentFile(QString());
    }
}

//+
void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open file"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


//+
bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this,tr("Save file"),tr("Image files (*.jpg)"));
        return saveFile(fileName);
    } else {
        return saveFile(curFile);
    }
}

//+
bool MainWindow::maybeSave()
{
    QMessageBox* pmBox = new QMessageBox(QMessageBox::Warning, tr("Save?"), tr("Save changes?"),
                                         QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    int n = pmBox->exec();
    if (n == QMessageBox::Yes)
        return save();
    if (n == QMessageBox::Cancel)
        return false;
    return true;
}

//+
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Load file error"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return;
    }
    img.load(fileName);
    label->setPixmap(img);
    setCurrentFile(fileName);
}

//+
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Save file error"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
    }
    img.save(file.fileName(),"jpg");
    setCurrentFile(fileName);
    return true;
}

//+
void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "LSI_untitled.jpg";
    setWindowFilePath(shownName);
}



void MainWindow::createActions()
{
    ui->fileToolBar->setToolTip(tr("File toolbar"));
    ui->fileToolBar->setMovable(false);
    ui->editToolBar->setToolTip(tr("Edit toolbar"));
    ui->editToolBar->setMovable(false);


    //New file action
    QAction *newAct = new QAction(QIcon(":/new.png"), tr("&New"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("New file"));
    newAct->setToolTip(tr("New File"));
    connect(newAct, SIGNAL(triggered(bool)),SLOT(newFile()));
    ui->menuFile->addAction(newAct);
    ui->fileToolBar->addAction(newAct);

    //Open file action
    QAction *openAct = new QAction(QIcon(":/open.png"), tr("&Open..."),this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open file"));
    openAct->setToolTip(tr("Open file"));
    connect(openAct, SIGNAL(triggered(bool)), SLOT(open()));
    ui->menuFile->addAction(openAct);
    ui->fileToolBar->addAction(openAct);

    //Save file action
    QAction *saveAct = new QAction(QIcon(":/save.png"), tr("&Save"),this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save file"));
    saveAct->setToolTip(tr("Save file"));
    connect(saveAct, SIGNAL(triggered(bool)), SLOT(save()));
    ui->menuFile->addAction(saveAct);
    ui->fileToolBar->addAction(saveAct);

    //add separator
    ui->menuFile->addSeparator();

    //Exit action only in File menu
    QAction *exitAct = new QAction(tr("E&xit"),this);
    exitAct->setStatusTip(tr("Exit"));
    exitAct->setShortcut(Qt::CTRL+Qt::Key_Q);
    connect(exitAct, SIGNAL(triggered(bool)),SLOT(close()));
    ui->menuFile->addAction(exitAct);


    /*//Undo action
    QAction *undoAct = undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setIcon(QIcon(":/undo.png"));
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo"));
    undoAct->setToolTip(tr("Undo"));
    undoAct->setEnabled(true);
    connect(undoAct, SIGNAL(triggered(bool)), undoStack, SLOT(undo()));
    ui->menuEdit->addAction(undoAct);
    ui->editToolBar->addAction(undoAct);




    //Redo action
    QAction *redoAct = undoStack->createRedoAction(this, tr("&Redo"));
    redoAct->setIcon(QIcon(":/redo.png"));
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo"));
    redoAct->setToolTip(tr("Redo"));
    redoAct->setEnabled(true);
    connect(redoAct, SIGNAL(triggered(bool)), undoStack, SLOT(redo()));
    ui->menuEdit->addAction(redoAct);
    ui->editToolBar->addAction(redoAct);




    //add separator
    ui->menuEdit->addSeparator();


    //Cut action
    QAction *cutAct = new QAction(QIcon(":/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut(copy to clipboard)"));
    cutAct->setToolTip(tr("Cut(copy to clipboard)"));
    connect(cutAct, SIGNAL(triggered(bool)), SLOT(cut()));
    ui->menuEdit->addAction(cutAct);
    ui->editToolBar->addAction(cutAct);
    cutAct->setEnabled(false);



    //Copy to clipboard action
    QAction *copyAct = new QAction(QIcon(":/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy to the clipboard"));
    copyAct->setToolTip(tr("Copy to the clipboard"));
    connect(copyAct, SIGNAL(triggered(bool)), SLOT(copy()));
    ui->menuEdit->addAction(copyAct);
    ui->editToolBar->addAction(copyAct);
    copyAct->setEnabled(false);


    //Paste from clipboard action
    QAction *pasteAct = new QAction(QIcon(":/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste from the clipboard"));
    pasteAct->setToolTip(tr("Paste from the clipboard"));
    connect(pasteAct, SIGNAL(triggered(bool)),  SLOT(paste()));
    ui->menuEdit->addAction(pasteAct);
    ui->editToolBar->addAction(pasteAct);*/

    //"About" action
    ui->menuBar->addAction(tr("About"),new about,SLOT(show()));
}

void MainWindow::createStatusBar()
{
    ui->statusBar->showMessage(tr("Ready"));
    ui->statusBar->setToolTip(tr("Status bar"));

}

void MainWindow::showSplash(QSplashScreen* psplash)
{
    QTime time;
    time.start();
    for (int i = 0; i < 100; ) {
        if (time.elapsed() > 10) {
            time.start();
            ++i;
        }
        psplash->showMessage("Loading LSI_Paint: "
                             + QString::number(i) + "%",
                             Qt::AlignHCenter | Qt::AlignBottom,
                             Qt::black
                             );
        qApp->processEvents();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

