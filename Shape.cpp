#include "Shape.h"

Car::Car(float x, float y):anchor(Vec(x,y)){
//    Vec position(x,y);
//    anchor = position;
    Vec p1(0.5, -0.2);
    Vec p2(0.5, 0);
    Vec p3(-0.5, 0);
    Vec p4(-0.5, -0.2);
    Vec p5(0.3, 0);
    Vec p6(0.2, 0.2);
    Vec p7(-0.4, 0.2);
    Vec p8(-0.5, 0);
    Vec p9(-0.25, -0.2);
    Vec p10(0.25, -0.2);
    float color1[3]={0.5,0.5,0};
    float color2[3]={0,0.5,0.5};

    comp[0] = new Quadrangle(p1, p2, p3, p4,color2,GL_LINE_LOOP);
    comp[1] = new Quadrangle(p5, p6, p7, p8,color1,GL_LINE_LOOP);
//    comp[2] = new Circle(p9, 0.07,color1,GL_POLYGON);
//    comp[3] = new Circle(p10, 0.07,color2,GL_POLYGON);
}

Car::~Car() {
//    int i;
//    for (i = 0; i < 4; i++) {
//        delete comp[i];
//    }
}

void Car::moveleft() {
    Vec leftmove(0.1, 0);
    for (int i = 0; i < 4; i++) {
        comp[i]->move(leftmove);
    }
}

void Car::moveright() {
    Vec rightmove(-0.1, 0);
    for (int i = 0; i < 4; i++) {
        comp[i]->move(rightmove);
    }
}

void Car::move() {
    static int i = 1;
    if (i == 1) {
        Car::moveleft();
    }
    if (i == -1)
        Car::moveright();
    i = -i;
}


void Car::draw() {
    for (int i = 0; i < 4; i++) {
        comp[i]->draw();
    }
}

void Car::rotate(float angle) {
    for (int i = 0; i < 4; i++) {
        comp[i]->setAnchor(anchor);
        comp[i]->rotate(angle);
}}

void Circle::draw() {
    const int n = 20;
    const GLfloat R = r;
    const GLfloat Pi = 3.1415926536f;
    {
        glColor3fv(color);
        glBegin(drawType);
        for (int i = 0; i < n; ++i)
            glVertex2f(R * cos(2 * Pi / n * i) + p1.getX(), R * sin(2 * Pi / n * i) + p1.getY());
        glEnd();
        glFlush();
    }
}


Vec Shape::getAnchor() {
    return anchor;
}

void Shape::setAnchor(Vec _anchor) {
    anchor = _anchor;
}

void Circle::zoom(float k) {
    r = r * k;
}

void Circle::move(Vec dir) {
    p1 = p1 + dir;
}

void Circle::rotate(float angle) {
    p1.setX((p1.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p1.setY(-(p1.getY() - anchor.getY()) * sin(angle) + anchor.getY());
}

void Triangle::draw() {
    GLfloat
            PointA[2] = {p1.getX(), p1.getY()},
            PointB[2] = {p2.getX(), p2.getY()},
            PointC[2] = {p3.getX(), p3.getY()};
    glColor3fv(color);
    glBegin(drawType);
    glVertex2fv(PointA);
    glVertex2fv(PointB);
    glVertex2fv(PointC);
    glEnd();
    glFlush();
}

void Triangle::zoom(float k) {
    p1 = anchor + (p1 - anchor) * k;
    p2 = anchor + (p2 - anchor) * k;
    p3 = anchor + (p3 - anchor) * k;
}

void Triangle::move(Vec dir) {
    p1 = p1 + dir;
    p2 = p2 + dir;
    p3 = p3 + dir;
    setAnchor(anchor + dir);
}

void Triangle::rotate(float angle) {
    p1.setX((p1.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p1.setY(-(p1.getY() - anchor.getY()) * sin(angle) + anchor.getY());
    p2.setX((p2.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p2.setY(-(p2.getY() - anchor.getY()) * sin(angle) + anchor.getY());
    p3.setX((p3.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p3.setY(-(p3.getY() - anchor.getY()) * sin(angle) + anchor.getY());
}

void Quadrangle::draw() {
    GLfloat
            PointA[2] = {p1.getX(), p1.getY()},
            PointB[2] = {p2.getX(), p2.getY()},
            PointC[2] = {p3.getX(), p3.getY()},
            PointD[2] = {p4.getX(), p4.getY()};
    glColor3fv(color);
    glBegin(drawType);
    glVertex2fv(PointA);
    glVertex2fv(PointB);
    glVertex2fv(PointC);
    glVertex2fv(PointD);
    glEnd();
    glFlush();
}

void Quadrangle::zoom(float k) {
    p1 = anchor + (p1 - anchor) * k;
    p2 = anchor + (p2 - anchor) * k;
    p3 = anchor + (p3 - anchor) * k;
    p4 = anchor + (p4 - anchor) * k;
}

void Quadrangle::move(Vec dir) {
    p1 = p1 + dir;
    p2 = p2 + dir;
    p3 = p3 + dir;
    p4 = p4 + dir;
    anchor = anchor + dir;
}

void Quadrangle::rotate(float angle) {
    p1.setX((p1.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p1.setY(-(p1.getY() - anchor.getY()) * sin(angle) + anchor.getY());
    p2.setX((p2.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p2.setY(-(p2.getY() - anchor.getY()) * sin(angle) + anchor.getY());
    p3.setX((p3.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p3.setY(-(p3.getY() - anchor.getY()) * sin(angle) + anchor.getY());
    p4.setX((p4.getX() - anchor.getX()) * cos(angle) + anchor.getX());
    p4.setY(-(p4.getY() - anchor.getY()) * sin(angle) + anchor.getY());
}

