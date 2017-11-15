#ifndef TORUS_H
#define TORUS_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QDebug>
#include <QVector3D>
#include "figure.h"
#include <cfloat>

using namespace std;

class Torus : public Figure {
public functions:

    Torus(double R = 250, double r = 50, QObject *parent = nullptr);

    ~Torus();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QJsonObject toJson() const override;

private functions:
    std::vector<double> getCoords(ULONG row, ULONG c);
    Matrix applyTr();

private fields:
    static const ULONG vCount = 60;
    static const ULONG hCount = 60;
    double R, r;
    Matrix *vs;
};

#endif // TORUS_H
