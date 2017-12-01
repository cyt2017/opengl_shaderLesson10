#include "qdatatorus.h"

QDataTorus::QDataTorus()
{

}

void QDataTorus::createTorus(QDataTorus::ArrayVertex &vertexs, QDataTorus::ArrayPri &pris, float radius, float tuberadius, int sides, int rings)
{
    float sideDelta = 2.0 * PI / sides;
    float ringDelta = 2.0 * PI / rings;
    float theta = 0;
    float cosTheta = 1.0;
    float sinTheta = 0.0;

    float phi, sinPhi, cosPhi;
    float dist;

    for (int i = 0; i < rings; i++)
    {
        float theta1    = theta + ringDelta;
        float cosTheta1 = cosf(theta1);
        float sinTheta1 = sinf(theta1);

        //GL.Begin(BeginMode.QuadStrip);
        phi = 0;

        Primative   pri =   {vertexs.size(),0,GL_TRIANGLES/*GL_QUAD_STRIP*/};

        for (int j = 0; j <= sides; j++)
        {
            phi = phi + sideDelta;
            cosPhi = cosf(phi);
            sinPhi = sinf(phi);
            dist = radius + (tuberadius * cosPhi);

            Vertex  vertex0;
            vertex0.nx   =   -cosTheta * cosPhi;
            vertex0.ny   =   -sinTheta * cosPhi;
            vertex0.nz   =   -sinPhi;
            vertex0.x   =   cosTheta * dist;
            vertex0.y   =   sinTheta * dist;
            vertex0.z   =   tuberadius * sinPhi;
            //GL.Normal3(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);
            //GL.Vertex3(cosTheta * dist, sinTheta * dist, tuberadius * sinPhi);
            vertexs.push_back(vertex0);

            Vertex  vertex1;
            vertex1.nx = -cosTheta1 * cosPhi;
            vertex1.ny = -sinTheta1 * cosPhi;
            vertex1.nz = -sinPhi;
            vertex1.x = cosTheta1 * dist;
            vertex1.y = sinTheta1 * dist;
            vertex1.z = tuberadius * sinPhi;

            //GL.Normal3(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);
            //GL.Vertex3(cosTheta1 * dist, sinTheta1 * dist, tuberadius * sinPhi);
            vertexs.push_back(vertex1);
        };
        pri.count   =   vertexs.size() - pri.start;
        pris.push_back(pri);
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }


}
