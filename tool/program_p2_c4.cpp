#include "program_p2_c4.h"

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
    _position       =   -1;
    _normal         =   -1;
    _colorLight     =   -1;
    _colorOffset    =   -1;
    _MVP            =   -1;
    _lightDir       =   -1;
    _matMV          =   -1;
    _fogR           =   -1;
    _fogDensity     =   -1;
    _fogColor       =   -1;
}

bool PROGRAM_P2_C4::initialize()
{
    //!思路：1、已知法线和光线，得到光强；
    //! 2、光强和光漫射(_lightDiffuse<_colorOffset>)得到光颜色；
    //! 3、已知顶点和观察矩阵，得到摄像机中的顶点坐标；
    //! 4、所得顶点坐标求距离，便可以和给定的可视半径进行比较，
    //!   并乘上雾的浓度，就是坐标所在的雾浓度
    //! 5、对计算出来的雾浓度进行归一化，使用函数（" fog = clamp(fog, 0.0, 1.0);"），
    //!   参数1：需要归一化的数据；2、3：归一化的范围
    //! 6、根据函数（"gl_FragColor = mix(_outColor,_fogColor,fog);"）选择光的颜色
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "uniform    vec3    _lightDir;"
        "uniform    vec3    _colorLight;"
        "uniform    vec3    _colorOffset;"
        "attribute  vec3    _position;"
        "attribute  vec3    _normal;"
        "varying    vec4    _outColor;"
        "varying    vec3    _outPos;"
        "void main()"
        "{"
        "   float NDotL =   max(dot(_normal, _lightDir), 0.0);"
        "   _outColor   =   vec4(_colorLight*NDotL + _colorOffset,1.0);"
        "   _outPos     =   _position;"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };
#if 0
    //!方法一：
    const char* ps  =
    {
        "precision  lowp    float; "
        "uniform    mat4    _matMV;"
        "uniform    float   _fogR;"
        "uniform    float   _fogDensity;"
        "uniform    vec4    _fogColor;"
        "varying    vec4    _outColor;"
        "varying    vec3    _outPos;"
        "void main()"
        "{"
        "   vec3 viewPos=   (_matMV*vec4(_outPos,1.0)).xyz;"
        "   float len   =   length(viewPos);"
        "   float fog   =   (_fogR - len)*_fogDensity;"
        "   fog         =   clamp(fog, 0.0, 1.0);"
        "   gl_FragColor    =   mix(_outColor,_fogColor,1.0-fog);"
        "}"
    };
#else
    //! 方法二：把" float fog   =   (_fogR - len)*_fogDensity;"
    //! 替换成 "   float fog   =   len/_fogR;"可减少运算
    //! 值得注意的是：
    //! 上面的"gl_FragColor = mix(_outColor,_fogColor,1.0-fog);"中第三个参数是（1.0-fog）;
    //! 如果直接用（fog），出现的结果就和Lesson09中的效果一样了
    //! 但是下面的片元shader是直接使用（fog）
    const char* ps  =
    {
        "precision  lowp    float; "
        "uniform    mat4    _matMV;"
        "uniform    float   _fogR;"
        "uniform    float   _fogDensity;"
        "uniform    vec4    _fogColor;"
        "varying    vec4    _outColor;"
        "varying    vec3    _outPos;"
        "void main()"
        "{"
        "   vec3 viewPos=   (_matMV*vec4(_outPos,1.0)).xyz;"
        "   float len   =   length(viewPos);"
        "   float fog   =   len/_fogR;"
        "   fog         =   clamp(fog, 0.0, 1.0);"
        "   gl_FragColor    =   mix(_outColor,_fogColor,fog);"
        "}"
    };

#endif
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"_position");
        _normal     =   glGetAttribLocation(_programId,"_normal");
        _colorLight =   glGetUniformLocation(_programId,"_colorLight");
        _colorOffset=   glGetUniformLocation(_programId,"_colorOffset");
        _matMV      =   glGetUniformLocation(_programId,"_matMV");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _lightDir   =   glGetUniformLocation(_programId,"_lightDir");
        _fogR       =   glGetUniformLocation(_programId,"_fogR");
        _fogDensity =   glGetUniformLocation(_programId,"_fogDensity");
        _fogColor   =   glGetUniformLocation(_programId,"_fogColor");
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position);       
    glEnableVertexAttribArray(_normal);
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_normal);
    glUseProgram(0);
}
