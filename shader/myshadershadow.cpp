#include "myshadershadow.h"

MyShaderShadow::MyShaderShadow()
{
    _matMV      =   -1;
    _matPRJ     =   -1;
    _matShadow  =   -1;
    _shadowMap  =   -1;
    _color      =   -1;
    _position   =   -1;
    _normal     =   -1;
}

bool MyShaderShadow::initialize()
{
    const char* vs  =
    {
        "uniform    mat4   shadowMatrix;"
        "uniform    mat4    matMV;"
        "uniform    mat4    matPRJ;"
        "attribute  vec3    attrPos;"
        "attribute  vec3    attrNormal;"
        "varying    vec4    shadowMapUV;"
        "void main()"
        "{"
            "vec4 Position  =	matMV * vec4(attrPos,1.0);"
            "shadowMapUV    =	shadowMatrix * vec4(attrPos,1.0);"
            "gl_Position    =	matPRJ * Position;"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp        float; "
        "uniform    sampler2D	shadowMap;"
        "uniform    vec4	    color;"
        "varying	vec4		shadowMapUV;"
        "void main()"
        "{"
            "float	NdotLD		=	1.0;"
            "vec4    shMap       =   shadowMapUV;"
//            "shMap.z -= 0.005;"
            "if(shMap.w>0.0)"
            "{"
                "vec3	shadowProj	=	shMap.xyz / shMap.w;"
                "if(shadowProj.x >= 0.0 && shadowProj.x < 1.0 &&\
                    shadowProj.y >= 0.0 && shadowProj.y < 1.0 &&\
                    shadowProj.z >= 0.0 && shadowProj.z < 1.0)"
                "{"
                    "vec4 colorDepth = texture2D(shadowMap, shadowProj.xy);"
                    "if(colorDepth.r < shadowProj.z)"
                    "{"
                        "NdotLD = 0.0;"
                    "}"
                "}"
                "if(NdotLD > 0.0)"
                "{"
                    "gl_FragColor	= color;"
                "}"
                "else"
                "{"
                    "gl_FragColor	= color * 0.5;"
                "}"
            "}"
        "}"
    };
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"attrPos");
        _normal     =   glGetAttribLocation(_programId,"attrNormal");
        _matMV      =   glGetUniformLocation(_programId,"matMV");
        _matPRJ     =   glGetUniformLocation(_programId,"matPRJ");
        _matShadow  =   glGetUniformLocation(_programId,"shadowMatrix");
        _shadowMap  =   glGetUniformLocation(_programId,"shadowMap");
        _color      =   glGetUniformLocation(_programId,"color");
    }
    return  res;
}

void MyShaderShadow::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position );
    glEnableVertexAttribArray(_normal);
//    glEnableVertexAttribArray(_uv);
}

void MyShaderShadow::end()
{
    glDisableVertexAttribArray(_position );
    glDisableVertexAttribArray(_normal);
//    glDisableVertexAttribArray(_uv);
    glUseProgram(0);
}
