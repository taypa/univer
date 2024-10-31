#include "interface_fraction.h"
#include "ui_interface_fraction.h"

interface_fraction::interface_fraction(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::interface_fraction)
{
    ui->setupUi(this);
}

interface_fraction::~interface_fraction()
{
    delete ui;
}

void interface_fraction::on_action_triggered()
{
    this->close();
    emit w_p();
}


void interface_fraction::on_action_2_triggered()
{

}

