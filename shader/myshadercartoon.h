#ifndef MYSHADERCARTOON_H
#define MYSHADERCARTOON_H

#include "tool/programid.h"
class MyShaderCartoon : public ProgramId
{
public:
    typedef int attribute;
    typedef int uniform;
public:
    uniform     _MVP;
    uniform     _lightDir;
    uniform     _color;
    attribute   _position;
    attribute   _normal;
public:
    MyShaderCartoon();   

    virtual bool    initialize();
    virtual void    begin();
    virtual void    end();
};

#endif // MYSHADERCARTOON_H
