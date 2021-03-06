//
// Created by Max Heartfield on 15.03.18.
//

#include "DistractionFilter.h"

DistractionFilter::DistractionFilter() {
    addShaderFromSourceCode(QOpenGLShader::Vertex, readFile(VERTEX_PATH));
    addShaderFromSourceCode(QOpenGLShader::Fragment, readFile(FRAG_PATH));
    bindAttributeLocation("vertex", 0);
    bindAttributeLocation("texCoord", 1);
    link();
}
