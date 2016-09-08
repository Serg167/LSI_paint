#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QPixmap img;
    QPixmap imgTmp;
    QString str;
    bool isPressed;
    bool isStPolgn;
    bool isDblClick;
    QPointF current;
    QPointF next;
    QPointF currentTmp;
    QPointF c1;
    QPointF c2;
    QPointF endPoint;
    QLabel* label;
    QUndoStack *undoStack;
    int instrument;
    QColor color;
    QPainter painter;
    int amOfClBezie;
    int widthOfPen;
    QString curFile;

protected:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *);

public:

    explicit MainWindow(QWidget *parent = 0);
    void showSplash(QSplashScreen* );
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    void createActions();
    void createStatusBar();
    void loadFile(const QString &fileName);
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

public slots:
    void newFile();
    void open();
    bool save();
    void pen();
    void lastic();
    void line();
    void drawLine();
    void ellipse();
    void drawEllipse();
    void rectangle();
    void drawRectangle();
    void polygon();
    void drawPolygon();
    void bezie();
    void drawBezie();
    void colorRed();
    void colorOrange();
    void colorYellow();
    void colorGreen();
    void colorLightBlue();
    void colorDarkBlue();
    void colorViolette();
    void scale(int);

};


#endif // MAINWINDOW_H
