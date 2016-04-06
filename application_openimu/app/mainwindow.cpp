#include "mainwindow.h"
#include "iostream"
#include <QFileDialog>
#include <QPalette>
#include <qlabel.h>
#include "acquisition/SensorReader.h"
#include "customqmlscene.h"
#include "controllers/toolbarcontroller.h"
#include "models/caneva.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle(QString::fromUtf8("Open-IMU"));
    this->setMinimumSize(500,500);
    plotDisplay = false;

    mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);

    //Set Menu Bar v2
    toolbarController = new ToolbarController();
    toolbarController->setFixedHeight(20);
    mainLayout->setMenuBar(toolbarController->toolbar);
    //---Set Menu Bar v2

    filesWidget = new QWidget();
    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::gray);
    filesWidget->setAutoFillBackground(true);
    filesWidget->setPalette(Pal);

    //mainLayout->addWidget(filesWidget);

    CustomQmlScene* scene = new CustomQmlScene("layout1.qml", this);
    mainLayout->addWidget(scene);

    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget(mainWidget); 

    Caneva caneva("../../config/layout1.json", scene);

    caneva.test();
}

string MainWindow::getFileName(string s){
    char sep = '/';
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos) {
       return(s.substr(i+1, s.length() - i));
    }

    return("");
}

void MainWindow:: openFile(){
    if(!plotDisplay){
        QString folderName = QFileDialog::getExistingDirectory(this, tr("Open File"),"/path/to/file/");
        qDebug() << "List items = " << folderName;
        SensorReader *reader = new SensorReader();
        vector<string> x = reader->listFiles(folderName.toStdString());
        QVBoxLayout *filesLayout = new QVBoxLayout;
        foreach (string t , x){

            //qDebug() << "List items = " << getFileName(t).c_str();
            filesLayout->addWidget(new QLabel(getFileName(t).c_str(),filesWidget));
        }
        filesWidget->setLayout(filesLayout);

    }
}
void MainWindow:: computeSteps(){

  /* plotWidget = new Widget(this->parentWidget());
    plotWidget->setFolderPath(folderName.toStdString());
    plotWidget->setupPlot();
    mainLayout->addWidget(plotWidget);
    plotDisplay = true;*/
}
