#include <QJsonObject>
#include "torus.h"
#include "../affine.h"

QRectF Torus::boundingRect() const {
    double xMin = numeric_limits<double>::max();
    double xMax = numeric_limits<double>::min();
    double yMin = numeric_limits<double>::max();
    double yMax = numeric_limits<double>::min();
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            double x = vs->operator()(row * hCount + column, 0);
            double y = vs->operator()(row * hCount + column, 1);
            if (x < xMin)
                xMin = x;
            if (x > xMax)
                xMax = x;
            if (y < yMin)
                yMin = y;
            if (y > yMax)
                yMax = y;
        }
    }
    return QRectF(QPointF(xMin, -yMin), QPointF(xMax, -yMax));
}

void Torus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Matrix v = applyTr();
    painter->setPen(Qt::black);
    for (int col = 1; col < hCount; col++) {
        for (int row = 1; row < vCount; row++) {
            QPolygonF face;
            face << QPointF(
                    v(row * hCount + col, 0),
                    -v(row * hCount + col, 1)
            ) << QPointF(
                    v((row - 1) * hCount + col, 0),
                    -v((row - 1) * hCount + col, 1)
            ) << QPointF(
                    v((row - 1) * hCount + col - 1, 0),
                    -v((row - 1) * hCount + col - 1, 1)
            ) << QPointF(
                    v(row * hCount + col - 1, 0),
                    -v(row * hCount + col - 1, 1)
            );
            painter->drawPolygon(face);
        }
    }
    //Замкнуть
    for (int row = 1; row < vCount; row++) {
        QPolygonF face;
        face << QPointF(
                v(row * hCount, 0),
                -v(row * hCount, 1)
        ) << QPointF(
                v((row - 1) * hCount, 0),
                -v((row - 1) * hCount, 1)
        ) << QPointF(
                v((row - 1) * hCount + hCount - 1, 0),
                -v((row - 1) * hCount + hCount - 1, 1)
        ) << QPointF(
                v(row * hCount + hCount - 1, 0),
                -v(row * hCount + hCount - 1, 1)
        );
        painter->drawPolygon(face);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Matrix Torus::applyTr() {
    Matrix v(*vs);
    v = geom::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = geom::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = geom::rotateX(v, transformations[RotateX]);
    v = geom::rotateY(v, transformations[RotateY]);
    v = geom::rotateZ(v, transformations[RotateZ]);
    return v;
}

QJsonObject Torus::toJson() const {
    QJsonObject json;
    json.insert("type", "TORUS");
    json.insert("R", R);
    json.insert("r", r);
    return json;
}

Torus::Torus(double R, double r, QObject *parent) : Figure(parent), R(R), r(r) {
    vs = new Matrix(vCount * hCount, 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<double> coords = getCoords(row, column);
            vs->operator()(row * hCount + column, 0) = coords[0];
            vs->operator()(row * hCount + column, 1) = coords[1];
            vs->operator()(row * hCount + column, 2) = coords[2];
        }
    }
}

Torus::~Torus() {
    delete vs;
}

std::vector<double> Torus::getCoords(ULONG row, ULONG column) {
    double phi = 2 * M_PI / hCount * row - M_PI;
    double xi = 2 * M_PI / vCount * column;
    std::vector<double> res(3);
    res[0] = (R + r * cos(phi)) * cos(xi);
    res[1] = (R + r * cos(phi)) * sin(xi);
    res[2] = r * sin(phi);
    return res;
}
