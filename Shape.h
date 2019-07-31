#ifndef H8_EX2_H
#define H8_EX2_H

#include <GL/freeglut.h>
#include <math.h>

class Vec {
private:
    float x, y;
public:
    Vec(float _x, float _y) {
        x = _x;
        y = _y;
    }

    float getX() { return x; }

    float getY() { return y; }

    void setX(float _x){
        x = _x;
    }

    void setY(float _y){
        y = _y;
    }

    Vec operator+(Vec v) {
        return (Vec(x + v.getX(), y + v.getY()));
    }

    Vec operator-(Vec v) {

        return (Vec(x - v.getX(), y - v.getY()));
    }

    Vec operator*(float k) {
        return (Vec(x * k, y * k));
    }

    Vec operator/(float k) {
        return (Vec(x / k, y / k));
    }
};

class Shape {
protected:
    Vec anchor;
    GLfloat color[3];   // pointer to a color array of RGB
    int drawType;       // GL_POLYGON, GL_LINE_LOOP
public:
    Shape() : anchor(0, 0), drawType(GL_POLYGON) {
        for (int i = 0; i < 3; i++)
            color[i] = 0.0f;
    }

    virtual void draw() = 0;

    virtual void zoom(float k) = 0;

    virtual void move(Vec dir) = 0;

    virtual void rotate(float angle)=0;

    Vec getAnchor();

    void setAnchor(Vec a);

    ~Shape(){};
};

class Circle : public Shape {
private:
    Vec p1;
    float r;
public:
    Circle(Vec _p1, float _r, GLfloat *_color, int _drawType) : p1(0, 0), r(0.0f) {
        r = _r;
        p1 = _p1;
        for (int i = 0; i < 3; i++)
            color[i] = _color[i];
        drawType = _drawType;
        setAnchor(_p1); //lijin added
    };

    void draw() override;

    void zoom(float k) override;

    void move(Vec dir) override;

    void rotate(float angle) override;

};

class Triangle : public Shape {
private:
    Vec p1;
    Vec p2;
    Vec p3;
public:
    Triangle(Vec _p1, Vec _p2, Vec _p3, GLfloat *_color, int _drawType) : p1(0, 0), p2(0, 1), p3(0.4, 0.2) {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;
        setAnchor((_p1 + _p2 + _p3) / 3);
        for (int i = 0; i < 3; i++)
            color[i] = _color[i];
        drawType = _drawType;
    }

    void draw() override;

    void zoom(float k) override;

    void move(Vec dir) override;

    void rotate(float angle) override;

};

class Quadrangle : public Shape {
private:
    Vec p1;
    Vec p2;
    Vec p3;
    Vec p4;
public:
    Quadrangle(Vec _p1, Vec _p2, Vec _p3, Vec _p4, GLfloat *_color, int _drawType) : p1(0.5, 0.75), p2(0.5, -0.75),
                                                                                     p3(-0.5, -0.75), p4(-0.5, 0.75) {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;
        p4 = _p4;
        setAnchor((_p1 + _p2 + _p3 + _p4) / 4);
        for (int i = 0; i < 3; i++)
            color[i] = _color[i];
        drawType = _drawType;
    }

    void draw() override;

    void zoom(float k) override;

    void move(Vec dir) override;

    void rotate(float angle) override;

};


class Car {
private:
    Shape *comp[4];

    Vec anchor;

    void moveleft();

    void moveright();

public:
    void move();

    void draw();

    void rotate(float angle);

    Car(float x = 0.0, float y = 0.0);

    ~Car();
};


#endif //PARKING_LOTS_SHAPE_H
