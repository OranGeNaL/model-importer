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
    const QStringList filters({"Model files (*.colada)",
                               "Any files (*)"
                              });
    fileSelector->setNameFilters(filters);

    fileSelector->show();
}


void MainWindow::on_importModel_clicked()
{

}

