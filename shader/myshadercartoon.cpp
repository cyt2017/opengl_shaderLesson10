#include "myshadercartoon.h"

MyShaderCartoon::MyShaderCartoon()
{
    _MVP        =   -1;
    _lightDir   =   -1;
    _color      =   -1;
    _position   =   -1;
    _normal     =   -1;
}

bool MyShaderCartoon::initialize()
{
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "attribute  vec3    _position;"
        "attribute  vec3    _normal;"
        "varying    vec3    _outNormal;"
        "void main()"
        "{"
            "_outNormal     =	_normal;"
            "gl_Position    =	_MVP * vec4(_position,1.0);"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp        float; "
        "uniform    vec3        _ligthDir;"
        "uniform    vec4	    _color;"
        "varying	vec3		_outNormal;"
        "void main()"
        "{"
        "   float NDotL    = max(dot(_outNormal,_ligthDir),0.0);"
        "   vec4 color;"
        "   if(NDotL>0.7)"
        "   {"
        "       color = vec4(1.0,1.0,1.0,1.0);"
        "   }"
        "   else if(NDotL>0.5)"
        "   {"
        "       color = vec4(0.7,0.7,0.7,1.0);"
        "   }"
        "   else if(NDotL>0.3)"
        "   {"
        "       color = vec4(0.5,0.5,0.5,1.0);"
        "   }"
        "   else"
        "   {"
        "       color = vec4(0.3,0.3,0.3,1.0);"
        "   }"
            "gl_FragColor	= color * _color;"
        "}"
    };
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"attrPos");
        _normal     =   glGetAttribLocation(_programId,"attrNormal");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _lightDir   =   glGetUniformLocation(_programId,"_lightDir");
        _color      =   glGetUniformLocation(_programId,"_color");
    }
    return  res;
}

void MyShaderCartoon::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position );
    glEnableVertexAttribArray(_normal);
}

void MyShaderCartoon::end()
{
    glDisableVertexAttribArray(_position );
    glDisableVertexAttribArray(_normal);
    glUseProgram(0);
}
