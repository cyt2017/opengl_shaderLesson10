#ifndef QDATABOXOPENGL_H
#define QDATABOXOPENGL_H

#include <string.h>
#include "tool/CELLMath.hpp"

class QDataBoxOpengl
{
public:
    QDataBoxOpengl();
    ~QDataBoxOpengl();

    struct V3N3
    {
       float x,y,z;
       float nx,ny,nz;
    };
    struct V3N3UV2
    {
       float x,y,z;
       float nx,ny,nz;
       float u, v;
    };

    struct NORMALMAP
    {
       float x, y, z;
       float nx, ny, nz;
       float u, v;
       float tx,ty,tz;
       float bx,by,bz;
    };

    NORMALMAP _dataNor[36];

    void initV3N3(const CELL::float3 &halfSize);
    void initDataBox(const CELL::float3 &halfSize);

    void convertTBN(V3N3UV2* vertices,NORMALMAP* nmVerts);
};

#endif // QDATABOXOPENGL_H
