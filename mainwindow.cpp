#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <fstream>

list<Neurona> lista;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    //INSERTAR AL INICIO
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(id == 0 or voltaje == 0 or id == NULL or voltaje == NULL){
        QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
    }else{
        Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
        lista.push_front(*nuevo);
        ui->id_spinBox->clear();
        ui->voltaje_doubleSpinBox->clear();
        ui->Pos_x_spinBox_2->clear();
        ui->Pos_y_spinBox_2->clear();
        ui->red_spinBox_4->clear();
        ui->green_spinBox_5->clear();
        ui->spinBox_6->clear();
    }
}

void MainWindow::on_pushButton_2_clicked(){
    //INSERTAR AL FINAL
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    id=ui->id_spinBox->value();
    voltaje=ui->voltaje_doubleSpinBox->value();
    posicion_x=ui->Pos_x_spinBox_2->value();
    posicion_y=ui->Pos_y_spinBox_2->value();
    red=ui->red_spinBox_4->value();
    green=ui->green_spinBox_5->value();
    blue=ui->spinBox_6->value();
    if(id == 0 or voltaje == 0 or id == NULL or voltaje == NULL){
        QMessageBox::warning(this,"Mensaje","Tiene que existir un voltaje y un id.");
    }else{
        Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
        lista.push_back(*nuevo);
        ui->id_spinBox->clear();
        ui->voltaje_doubleSpinBox->clear();
        ui->Pos_x_spinBox_2->clear();
        ui->Pos_y_spinBox_2->clear();
        ui->red_spinBox_4->clear();
        ui->green_spinBox_5->clear();
        ui->spinBox_6->clear();
    }
}

void MainWindow::on_pushButton_3_clicked(){
    //MOSTRAR
    if(!lista.empty()){
        ui->plainTextEdit->clear();
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            ui->plainTextEdit->insertPlainText("ID: "+QString::number(aux->getId())+"\n");
            ui->plainTextEdit->insertPlainText("VOLTAJE: "+QString::number(aux->getVoltaje())+"\n");
            ui->plainTextEdit->insertPlainText("POS_X: "+QString::number(aux->getPosX())+"\n");
            ui->plainTextEdit->insertPlainText("POS_Y: "+QString::number(aux->getPosY())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n");
            ui->plainTextEdit->insertPlainText("GREEN: "+QString::number(aux->getGreen())+"\n");
            ui->plainTextEdit->insertPlainText("RED: "+QString::number(aux->getRed())+"\n\n");
            aux++;
        }
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_4_clicked(){
    //RESPALDO
    string delimitador = "|";
    if(!lista.empty()){
        QString filename = QFileDialog::getSaveFileName(this, "Save file","respaldo.txt");
        ofstream archivo(filename.toStdString(),ios::out);
        list<Neurona>::iterator aux = lista.begin();
        while(aux!=lista.end()){
            archivo<<aux->getId()<<delimitador;
            archivo<<aux->getVoltaje()<<delimitador;
            archivo<<aux->getPosX()<<delimitador;
            archivo<<aux->getPosY()<<delimitador;
            archivo<<aux->getRed()<<delimitador;
            archivo<<aux->getGreen()<<delimitador;
            archivo<<aux->getBlue()<<delimitador;
            aux++;
        }
        QMessageBox::information(this,"Guardado","Guardado exitosamente...");
    }else{
        ui->plainTextEdit->clear();
        ui->plainTextEdit->insertPlainText("La lista esta vacia...");
    }
}


void MainWindow::on_pushButton_5_clicked(){
    int id, posicion_x,posicion_y,red,green,blue;
    double voltaje;
    string registro;
    QString filename = QFileDialog::getOpenFileName(this, "Open file","C://");
    ifstream archivo(filename.toStdString(),ios::in);
    if(!archivo.fail()){
        while(!archivo.eof()){
            getline(archivo,registro,'|');
            id=atoi(registro.c_str());
            if(id != NULL){
                getline(archivo,registro,'|');
                voltaje=strtof(registro.c_str(), nullptr);
                getline(archivo,registro,'|');
                posicion_x=atoi(registro.c_str());
                getline(archivo,registro,'|');
                posicion_y=atoi(registro.c_str());
                getline(archivo,registro,'|');
                red=atoi(registro.c_str());
                getline(archivo,registro,'|');
                green=atoi(registro.c_str());
                getline(archivo,registro,'|');
                blue=atoi(registro.c_str());
                Neurona *nuevo = new Neurona(id,voltaje,posicion_x,posicion_y,red,green,blue);
                lista.push_back(*nuevo);
            }
        }
        QMessageBox::information(this,"Recuperado","Se recuperaron los archivos correctamente...");
    }else{
        QMessageBox::critical(this,"Error","El archivo no se abrio correctamente...");
    }
}
