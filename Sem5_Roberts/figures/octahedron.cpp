//
// Created by Roman Yarnykh on 01.11.17.
//

#include <QJsonObject>
#include "octahedron.h"

Octahedron::Octahedron(double edge, QGraphicsScene *scene) : Figure(edge, scene) {
    this->originalV = vertex();
    this->f = faces();
    this->v = this->originalV;
    xC = 0;
    yC = 0;
    zC = 0;
    for(int i = 0; i < OCT_V; i++){
        xC += v(0, i);
        yC += v(1, i);
        zC += v(2, i);
    }
    xC /= OCT_V;
    yC /= OCT_V;
    zC /= OCT_V;
}

QGenericMatrix<OCT_V, 3, qreal> Octahedron::vertex() {
    QGenericMatrix<OCT_V, 3, qreal> v2;
    //v 1
    v2(X, OCT_V1) = -this->edge / 2.0;
    v2(Y, OCT_V1) = 0;
    v2(Z, OCT_V1) = -this->edge / 2.0;
    //v 2
    v2(X, OCT_V2) = this->edge / 2.0;
    v2(Y, OCT_V2) = 0;
    v2(Z, OCT_V2) = -this->edge / 2.0;
    //v 3
    v2(X, OCT_V3) = this->edge / 2.0;
    v2(Y, OCT_V3) = 0;
    v2(Z, OCT_V3) = this->edge / 2.0;
    //v 4
    v2(X, OCT_V4) = -this->edge / 2.0;
    v2(Y, OCT_V4) = 0;
    v2(Z, OCT_V4) = this->edge / 2.0;
    //v 5
    v2(X, OCT_V5) = 0;
    v2(Y, OCT_V5) = this->edge * sqrt(2) / 2;
    v2(Z, OCT_V5) = 0;
    //v 6
    v2(X, OCT_V6) = 0;
    v2(Y, OCT_V6) = -this->edge * sqrt(2) / 2;
    v2(Z, OCT_V6) = 0;

    return v2;
}

QGenericMatrix<OCT_F, OCT_P, int> Octahedron::faces() {
    QGenericMatrix<OCT_F, OCT_P, int> f2;
    //front top
    f2(OCT_P1, OCT_FRONT_TOP) = OCT_V1;
    f2(OCT_P2, OCT_FRONT_TOP) = OCT_V2;
    f2(OCT_P3, OCT_FRONT_TOP) = OCT_V5;
    //right top
    f2(OCT_P1, OCT_SIDE_RIGHT_TOP) = OCT_V2;
    f2(OCT_P2, OCT_SIDE_RIGHT_TOP) = OCT_V3;
    f2(OCT_P3, OCT_SIDE_RIGHT_TOP) = OCT_V5;
    //back top
    f2(OCT_P1, OCT_SIDE_BACK_TOP) = OCT_V3;
    f2(OCT_P2, OCT_SIDE_BACK_TOP) = OCT_V4;
    f2(OCT_P3, OCT_SIDE_BACK_TOP) = OCT_V5;
    //left top
    f2(OCT_P1, OCT_SIDE_LEFT_TOP) = OCT_V4;
    f2(OCT_P2, OCT_SIDE_LEFT_TOP) = OCT_V1;
    f2(OCT_P3, OCT_SIDE_LEFT_TOP) = OCT_V5;
    //front bottom
    f2(OCT_P1, OCT_FRONT_BOTTOM) = OCT_V1;
    f2(OCT_P2, OCT_FRONT_BOTTOM) = OCT_V2;
    f2(OCT_P3, OCT_FRONT_BOTTOM) = OCT_V6;
    //right bottom
    f2(OCT_P1, OCT_SIDE_RIGHT_BOTTOM) = OCT_V2;
    f2(OCT_P2, OCT_SIDE_RIGHT_BOTTOM) = OCT_V3;
    f2(OCT_P3, OCT_SIDE_RIGHT_BOTTOM) = OCT_V6;
    //back bottom
    f2(OCT_P1, OCT_SIDE_BACK_BOTTOM) = OCT_V3;
    f2(OCT_P2, OCT_SIDE_BACK_BOTTOM) = OCT_V4;
    f2(OCT_P3, OCT_SIDE_BACK_BOTTOM) = OCT_V6;
    //left bottom
    f2(OCT_P1, OCT_SIDE_LEFT_BOTTOM) = OCT_V4;
    f2(OCT_P2, OCT_SIDE_LEFT_BOTTOM) = OCT_V1;
    f2(OCT_P3, OCT_SIDE_LEFT_BOTTOM) = OCT_V6;
    return f2;
}

QRectF Octahedron::bound() {
    return QRectF(QPointF(originalV(0, OCT_V1), originalV(1, OCT_V5)), QPointF(originalV(0, OCT_V4), originalV(1, OCT_V6)));
}

QJsonObject Octahedron::toJson() {
    QJsonObject json = Figure::toJson();
    json.insert("type", "OCTAHEDRON");
    return json;
}
