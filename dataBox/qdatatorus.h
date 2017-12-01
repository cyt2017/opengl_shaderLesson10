#ifndef QDATATORUS_H
#define QDATATORUS_H

#include <QString>
#include <GLES2/gl2.h>
#include "tool/CELLMath.hpp"

class QDataTorus
{
public:
    QDataTorus();
    struct  Vertex
     {
         float   x, y, z;
         float   nx, ny, nz;
         float   u, v;
     };

     struct  Primative
     {
         int     start;
         int     count;
         int     pri;
     };
     typedef std::vector<Vertex> ArrayVertex;
     typedef std::vector<Primative> ArrayPri;

     ArrayVertex     _torus;
     ArrayPri        _pris;

     /// <summary>
     /// 绘制圆环体
     /// </summary>
     /// <param name="radius">圆环体半径</param>
     /// <param name="Tuberadius">圆环体段半径</param>
     /// <param name="Sides">圆环体段的侧面数</param>
     /// <param name="Rings">圆环体段数</param>
    void createTorus(ArrayVertex& vertexs,ArrayPri& pris,float radius = 50, float tuberadius = 10, int sides = 20, int rings = 30);
};

#endif // QDATATORUS_H
