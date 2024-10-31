#ifndef INTERFACE_COMPLEX_H
#define INTERFACE_COMPLEX_H

#include <QMainWindow>

namespace Ui {
class interface_complex;
}

class interface_complex : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_complex(QWidget *parent = nullptr);
    ~interface_complex();

signals:
    void w_p();
    void w_f();

private slots:
    void on_action_p_triggered();
    void on_action_triggered();

private:
    Ui::interface_complex *ui;
};

#endif // INTERFACE_COMPLEX_H
