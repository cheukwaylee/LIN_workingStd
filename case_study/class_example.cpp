#include <iostream>
using namespace std;

//线
class Line // abstract base class
{
public:
    Line(float len);            // construct function
    virtual float area() = 0;   // pure virtual function, NOT implement provided
    virtual float volume() = 0; //

protected:
    float m_len;
};

Line::Line(float len)
{
    m_len = len;
}

Line::Line(float len) : m_len(len)
{
    // other implement
}

//矩形
class Rec : public Line
{
public:
    Rec(float len, float width);
    float area();

protected:
    float m_width;
};

Rec::Rec(float len, float width) : Line(len), m_width(width)
{ // other implement
}
float Rec::area() { return m_len * m_width; }

// 创建对象 调用的函数：构造

//长方体
class Cuboid : public Rec
{
public:
    Cuboid(float len, float width, float height);
    float area();
    float volume();

protected:
    float m_height;
};
Cuboid::Cuboid(float len, float width, float height)
    : Rec(len, width), m_height(height) {}

float Cuboid::area() { return 2 * (m_len * m_width + m_len * m_height + m_width * m_height); }
float Cuboid::volume() { return m_len * m_width * m_height; }

//正方体
class Cube : public Cuboid
{
public:
    Cube(float len);
    float area();
    float volume();
};
Cube::Cube(float len) : Cuboid(len, len, len) {}

float Cube::area() { return 6 * m_len * m_len; }
float Cube::volume() { return m_len * m_len * m_len; }

int main()
{
    Line *p = new Cuboid(10, 20, 30);
    cout << "The area of Cuboid is " << p->area() << endl;
    cout << "The volume of Cuboid is " << p->volume() << endl;

    p = new Cube(15);
    cout << "The area of Cube is " << p->area() << endl;
    cout << "The volume of Cube is " << p->volume() << endl;
    return 0;
}

// 变量类型 变量名 = 初始化的值
int a = 8;
int *pa = &a;
int &ra = a;
int c = *pa; // *(pa) *&a a

/*
type of a?   int
type of pa?  int* pointer to int
type of ra?  int&
*/

/*
一元运算符
    * 提领
    & 取址（互逆）

变量类型
int*  pointer to int
int&  int

*/