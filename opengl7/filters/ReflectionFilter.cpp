//
// Created by Max Heartfield on 15.03.18.
//

#include "ReflectionFilter.h"

ReflectionFilter::ReflectionFilter() {
    addShaderFromSourceCode(QOpenGLShader::Vertex, readFile(VERT_PATH));
    addShaderFromSourceCode(QOpenGLShader::Fragment, readFile(FRAG_PATH));
    bindAttributeLocation("vertex", 0);
    bindAttributeLocation("texCoord", 1);
    link();
}
