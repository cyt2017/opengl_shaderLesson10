#ifndef MYSHADERSHADOW_H
#define MYSHADERSHADOW_H

#include "tool/programid.h"

class MyShaderShadow : public ProgramId
{
public:
    typedef int attribute;
    typedef int uniform;
public:
    uniform     _matMV;
    uniform     _matPRJ;
    uniform     _matShadow;
    uniform     _shadowMap;
    uniform     _color;
    attribute   _position;
    attribute   _normal;
public:
    MyShaderShadow();

    virtual bool    initialize();
    virtual void    begin();
    virtual void    end();
};

#endif // MYSHADERSHADOW_H
