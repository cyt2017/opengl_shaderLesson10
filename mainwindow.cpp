#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<QString> fileName;
    QString name[6];
    name[0] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_PX.png";
    name[1] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_PY.png";
    name[2] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_PZ.png";
    name[3] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_NX.png";
    name[4] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_NY.png";
    name[5] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_4/build/cube/cube_NZ.png";

    for(int i=0;i<sizeof(name)/sizeof(name[0]);++i)
    {
        fileName.push_back(name[i]);
    }

    ui->widget->init_QGW(fileName);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    timer->start(20);

    ui->widget->parent = this;
    this->installEventFilter(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeOut()
{
    ui->widget->drawImage();
}

