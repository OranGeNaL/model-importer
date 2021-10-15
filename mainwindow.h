#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <OpenGL.h>
#include <QDebug>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

//#include "../QSerializer/src/qserializer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



typedef struct MyVertex
  {
    float x, y, z;
    float nx, ny, nz;
    float s0, t0;
  } TMyVertex;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<MyVertex> vertexes;
    QVector<GLuint> indexes;

private slots:
    void on_selectModel_clicked();

    void on_importModel_clicked();

private:
    Ui::MainWindow *ui;
    QString modelName;
    void WriteVertexIntoFile(QVector<MyVertex>, QString);
    void WriteIndexesIntoFile(QVector<GLuint>, QString);
};
#endif // MAINWINDOW_H
