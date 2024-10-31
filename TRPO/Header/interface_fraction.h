#ifndef INTERFACE_FRACTION_H
#define INTERFACE_FRACTION_H

#include <QMainWindow>

namespace Ui {
class interface_fraction;
}

class interface_fraction : public QMainWindow
{
    Q_OBJECT

public:
    explicit interface_fraction(QWidget *parent = nullptr);
    ~interface_fraction();

signals:
    void w_p();
    void w_c();

private slots:
    void on_action_triggered();
    void on_action_2_triggered();

private:
    Ui::interface_fraction *ui;
};

#endif // INTERFACE_FRACTION_H
