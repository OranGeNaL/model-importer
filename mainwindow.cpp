#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectModel_clicked()
{
    QFileDialog* fileSelector = new QFileDialog();
    const QStringList filters({"Model files (*.dae)",
                               "Any files (*)"
                              });
    fileSelector->setNameFilters(filters);

    //fileSelector->show();

    modelName = fileSelector->getOpenFileName();

    ui->filePath->setText(modelName);

    qDebug() << modelName;


    const aiScene* scene = nullptr;
    Assimp::Importer importer;
    scene = importer.ReadFile(modelName.toStdString().c_str(), NULL);
        if(scene == nullptr){
            qDebug() << "initializeGL::Reading file failed!\n";
            exit(EXIT_FAILURE);
        }

        //unsigned short currentMesh = 5;
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
            if(scene->mNumMeshes != 0 && scene->mMeshes[i]->HasNormals()){
                //----- tmp -----------------
                MyVertex tmpVertex;
                aiVector3D* verteces = scene->mMeshes[i]->mVertices;
                aiVector3D* normals = scene->mMeshes[i]->mNormals;
                aiVector3D* texture_coords = scene->mMeshes[i]->mTextureCoords[0];
                //---------------------------
                for(unsigned int currentVertex = 0; currentVertex < scene->mMeshes[i]->mNumVertices; ++currentVertex){
                    tmpVertex.x = verteces[currentVertex].x;
                    tmpVertex.y = verteces[currentVertex].y;
                    tmpVertex.z = verteces[currentVertex].z;

                    tmpVertex.nx = normals[currentVertex].x;
                    tmpVertex.ny = normals[currentVertex].y;
                    tmpVertex.nz = normals[currentVertex].z;

                    tmpVertex.s0 = texture_coords[currentVertex].x;
                    tmpVertex.t0 = texture_coords[currentVertex].y;

                    //tmpVertex.s0 = verteces[currentVertex].x;
                    //tmpVertex.t0 = verteces[currentVertex].y;

                    //qDebug() << verteces[currentVertex].x << verteces[currentVertex].y << verteces[currentVertex].z;


                    vertexes.append(tmpVertex);
                }
            }

            aiFace* faces = scene->mMeshes[i]->mFaces;
            for(unsigned int currentFace = 0; currentFace < scene->mMeshes[i]->mNumFaces; ++currentFace){
                for(unsigned short currentFacePoint = 0; currentFacePoint < faces[currentFace].mNumIndices; ++currentFacePoint){
                    indexes.append((GLuint)faces[currentFace].mIndices[currentFacePoint]);
                }
            }
        }
}

void MainWindow::on_importModel_clicked()
{

    WriteVertexIntoFile(vertexes, modelName + "-vertexes.txt");
    WriteIndexesIntoFile(indexes, modelName + "-indexes.txt");
}


void MainWindow::WriteVertexIntoFile(QVector<MyVertex> vert, QString fileN)
{
    QFile file(fileN);
    file.open(QIODevice::WriteOnly);

    for(int i = 0; i < vert.length(); i++)
    {
        file.write((QString::number(vert[i].x) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].y) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].z) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].nx) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].ny) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].nz) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].s0) + '\n').toStdString().c_str());
        file.write((QString::number(vert[i].t0) + '\n').toStdString().c_str());

    }

    file.close();
}

void MainWindow::WriteIndexesIntoFile(QVector<GLuint> ind, QString fileN)
{
    QFile file(fileN);
    file.open(QIODevice::WriteOnly);

    for(int i = 0; i < ind.length(); i++)
    {
        file.write((QString::number(ind[i]) + '\n').toStdString().c_str());
    }

    file.close();
}
