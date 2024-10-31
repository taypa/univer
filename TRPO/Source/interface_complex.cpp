#include "interface_complex.h"
#include "ui_interface_complex.h"

interface_complex::interface_complex(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_complex)
{
    ui->setupUi(this);
}

interface_complex::~interface_complex()
{
    delete ui;
}

void interface_complex::on_action_p_triggered()
{
    this->close();
    emit w_p();
}


void interface_complex::on_action_triggered()
{

}

