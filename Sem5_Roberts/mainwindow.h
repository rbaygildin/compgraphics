#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QListWidgetItem>
#include "figures/cube.h"
#include "figures/pyramid.h"
#include "figures/octahedron.h"
#include "figures/icosahedron.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Fig{CUBE, PYRAMID, OCT, ICOS};
    explicit MainWindow(QWidget *parent = 0);
    void createActions();
    void drawAxes();
    bool eventFilter(QObject *target, QEvent *event) override;
    void addCube(QPoint pos);
    void addPyramid(QPoint pos);
    void addOctahedron(QPoint pos);
    void addIcosahedron(QPoint pos);
    ~MainWindow() override;

private slots:
    void save();
    void open();
    void about();
    void contextMenuRequested(QPoint pos);
    void redraw();
    void rotateX();
    void rotateY();
    void rotateZ();
    void scaleX();
    void scaleY();
    void scaleZ();
    void moveX();
    void moveY();
    void moveZ();
    void clear();
    void restore();
    void selectFigure(QListWidgetItem* item);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    vector<IFigure*> figures;
    IFigure* selectedFigure;
    bool mousePressed = false;
    QPoint mousePressedPoint;
};

#endif // MAINWINDOW_H