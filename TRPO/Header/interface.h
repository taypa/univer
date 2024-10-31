#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <Editor.h>
#include <control.h>
//#include <Memory.h>
//#include <Number.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:
    void numbers();
    void set_enabled_num(int current);
    void on_spinBox_valueChanged(int current);
    void on_horizontalSlider_valueChanged();
    void on_pushButton_editor_clicked();
    void on_pushButton_operation_clicked();
    void on_pushButton_memory_clicked();
    void text_changed(QString str);
    void on_action_triggered();
    void on_action_2_triggered();

private:
    Ui::Interface *ui;
    int _prev;
    Control control;

protected:
    void keyPressEvent(QKeyEvent *e) override;


};
#endif // INTERFACE_H
