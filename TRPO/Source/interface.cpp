#include "interface.h"
#include "Number.h"
#include "Editor.h"
#include "information.h"
#include "ui_interface.h"
#include <QDebug>

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{

    ui->setupUi(this);
    ui->lineEdit->setText("0");

    control.editor_.set_num(ui->lineEdit->text().toStdString());

    ui->spinBox->setValue(ui->horizontalSlider->value());

    QPushButton* pushButtons[16] = {ui->pushButton0, ui->pushButton1, ui->pushButton2,
                                    ui->pushButton3, ui->pushButton4, ui->pushButton5,
                                    ui->pushButton6, ui->pushButton7, ui->pushButton8,
                                    ui->pushButton9, ui->pushButton_A, ui->pushButton_B,
                                    ui->pushButton_C, ui->pushButton_D, ui->pushButton_E,
                                    ui->pushButton_F
                                   };

    for(auto button : pushButtons)
    {
        connect(button,SIGNAL(clicked()),this, SLOT(numbers()));
    }

    _prev = ui->spinBox->value()-1;
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &Interface::set_enabled_num);
    connect(ui->spinBox, &QSpinBox::valueChanged, this, &Interface::on_spinBox_valueChanged);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &Interface::text_changed);


    for (int i = 2; i < 16; i++)
        pushButtons[i]->setEnabled(false);

    QPushButton* operations[7] = {ui->pushButton_Sqr, ui->pushButton_reverse,
                                  ui->pushButton_plus, ui->pushButton_minus,
                                  ui->pushButton_mult, ui->pushButton_division,
                                  ui->pushButton_execute};
    for (unsigned i{0}; i < 7; i++)
            connect(operations[i], SIGNAL(clicked()), this, SLOT(on_pushButton_operation_clicked()));

    QPushButton* editor_commands[5] = {ui->pushButton_plusorminus,ui->pushButton_Backspace,
                                       ui->pushButton_C_2, ui->pushButton_CE, ui->pushButton_point};
    for (unsigned i{0}; i < 5; i++)
    {
        connect(editor_commands[i], SIGNAL(clicked()), this, SLOT(on_pushButton_editor_clicked()));
    }

    QPushButton* memory_commands[4] = {ui->pushButton_MC, ui->pushButton_MR, ui->pushButton_Mplus, ui->pushButton_MS};
    for (unsigned i{0}; i < 4; i++)
    {
        connect(memory_commands[i], SIGNAL(clicked()), this, SLOT(on_pushButton_memory_clicked()));
    }
}


Interface::~Interface()
{
    delete ui;
}


void Interface::numbers()
{
    QPushButton *button = (QPushButton*)sender();
    QString all_num;

    all_num = (ui->lineEdit->text()+button->text());
    if((all_num[0]=='0'&& all_num.length()>1)&&!(all_num.contains('.')))
        all_num.remove(0,1);

    ui->lineEdit->setText(all_num);
}


void Interface::set_enabled_num(int current)
{
    QPushButton* pushButtons[16] = {ui->pushButton0, ui->pushButton1, ui->pushButton2,
                                    ui->pushButton3, ui->pushButton4, ui->pushButton5,
                                    ui->pushButton6, ui->pushButton7, ui->pushButton8,
                                    ui->pushButton9, ui->pushButton_A, ui->pushButton_B,
                                    ui->pushButton_C, ui->pushButton_D, ui->pushButton_E,
                                    ui->pushButton_F};
    if (_prev - current != 0)
    {
        for (int i = 2; i < 16; i++)
        {
            if( current > i)
                pushButtons[i]->setEnabled(true);
            else
                pushButtons[i]->setEnabled(false);

        }
    }
}

void Interface::on_spinBox_valueChanged(int current)
{
    ui->horizontalSlider->setValue(ui->spinBox->value());
    if(!control.editor_.IsZero())
    {
        control.editor_.set_num(control.editor_.get_num(), _prev + 1, current, 5);
        ui->lineEdit->setText(QString::fromStdString(control.editor_.get_num()));
    }
    _prev = current - 1;
}

void Interface::on_horizontalSlider_valueChanged()
{
    ui->spinBox->setValue(ui->horizontalSlider->value());
}

void Interface::on_pushButton_editor_clicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (ui->lineEdit->text()!=""){
        std::string result = control.PerformEditorCommand(clickedButton->text().toStdString());
        ui->lineEdit->setText(QString::fromStdString(result));
    }
}

void Interface::on_pushButton_operation_clicked()
{
    std::string result = "0";

    std::string operation = qobject_cast<QPushButton*>(sender())->text().toStdString();

    Number first(ui->lineEdit->text().toStdString(), ui->horizontalSlider->value(), 5);

    ui->lineEdit->setText(QString::fromStdString(result));

    if(operation == "1/x" || operation == "Sqr")
    {
        control.proc_.SetRight(first);
        result = control.PerformFunc(operation);
    }
    else if(operation == "=")
    {
        control.proc_.SetRight(first);
        control.PerformOperation();
        control.editor_.set_num(control.proc_.GetLeft().get_num());
        control.proc_.SetRight(Number());
        control.proc_.SetLeft(Number());
        result = control.editor_.get_num();
    }
    else
    {
        if(control.proc_.GetLeft().get_num() == "0")
        {
            control.proc_.SetLeft(first);
            control.proc_.SetOperation(operation[0]);
            control.editor_.Clear();
            result = control.editor_.get_num();
        }
        else
        {
            control.proc_.SetRight(first);
            control.PerformOperation();
            control.editor_.Clear();
            control.proc_.SetRight(Number());
            control.proc_.SetOperation(operation[0]);
            result = control.editor_.get_num();
        }
    }
    ui->lineEdit->setText(QString::fromStdString(result));
}

void Interface::on_pushButton_memory_clicked()
{
    std::string operation = qobject_cast<QPushButton*>(sender())->text().toStdString();
    Number result(ui->lineEdit->text().toStdString(), ui->horizontalSlider->value(), 5);

    Number num = control.PerformMemory(operation, result);

    ui->lineEdit->setText(QString::fromStdString(num.get_num()));
    ui->horizontalSlider->setValue(num.get_p());
}

void Interface::text_changed(QString str)
{
    control.editor_.set_num(str.toStdString());
}


void Interface::on_action_triggered()
{
    Information p;
    p.setWindowTitle("Информация о приложении");
    p.show();
    p.exec();
}


void Interface::on_action_2_triggered()
{
    QMessageBox::information(this, "Students","Группа: ПМИ-02 \nРабсалова Юмжана \nСобещиков Ярослав");
}

void Interface::keyPressEvent(QKeyEvent *e)
{
    QString text = ui->lineEdit->text();
    if (!text.isEmpty())
    {
        if (e->key() == Qt::Key_Backspace)
        {
            std::string result = control.PerformEditorCommand(ui->pushButton_Backspace->text().toStdString());
            ui->lineEdit->setText(QString::fromStdString(result));
        }
        else if (e->key() == Qt::Key_Return)
        {
            std::string result = "0";
            Number first(ui->lineEdit->text().toStdString(), ui->horizontalSlider->value(), 5);

            control.proc_.SetRight(first);
            control.PerformOperation();
            control.editor_.set_num(control.proc_.GetLeft().get_num());
            control.proc_.SetRight(Number());
            control.proc_.SetLeft(Number());
            result = control.editor_.get_num();

            ui->lineEdit->setText(QString::fromStdString(result));
        }
        else if (e->key() == Qt::Key_Delete)
        {
            std::string result = control.PerformEditorCommand(ui->pushButton_CE->text().toStdString());
            ui->lineEdit->setText(QString::fromStdString(result));
        }
        else if (e->key() == Qt::Key_Period)
        {
            std::string result = control.PerformEditorCommand(ui->pushButton_point->text().toStdString());
            ui->lineEdit->setText(QString::fromStdString(result));
        }

        QPushButton* pushButtons[16] = {ui->pushButton0, ui->pushButton1, ui->pushButton2,
                                        ui->pushButton3, ui->pushButton4, ui->pushButton5,
                                        ui->pushButton6, ui->pushButton7, ui->pushButton8,
                                        ui->pushButton9, ui->pushButton_A, ui->pushButton_B,
                                        ui->pushButton_C, ui->pushButton_D, ui->pushButton_E,
                                        ui->pushButton_F
                                       };

        auto p1 = ui->spinBox->value();

        for (QPushButton *button : pushButtons)
        {
            if (button->text() == e->text())
            {
                auto button_name = Convertor_P_10::Convert(button->text().toStdString(),16,5);
                if (button_name < p1)
                {
                    QString all_num;
                    all_num = (ui->lineEdit->text()+button->text());
                    if((all_num[0]=='0'&& all_num.length()>1)&&!(all_num.contains('.')))
                        all_num.remove(0,1);

                    ui->lineEdit->setText(all_num);
                }
            }
        }
    }
}
