#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <vector>
#include "figures/torus.h"
#include "figures/polygons/polygon.h"
#include "figures/polygons/cube.h"
#include "figures/polygons/regularpyramid.h"
#include "figures/polygons/octahedron.h"
#include "figures/polygons/icosahedron.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

private slots:
    void save();
    void open();
    void about();
    void showGraphicsViewMenu(QPoint pos);
    void addCube(QPoint pos);
    void addRegularPyramid(QPoint pos);
    void addOctahedron(QPoint pos);
    void addIcosahedron(QPoint pos);
    void addPyramid(QPoint pos);
    void clear();
    void redraw();
    void restore();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<Polygon *> figures;
};

#endif // MAINWINDOW_H
