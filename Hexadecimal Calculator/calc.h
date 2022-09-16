#ifndef CALC_H
#define CALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calc; }
QT_END_NAMESPACE

class Calc : public QMainWindow
{
    Q_OBJECT

public:
    Calc(QWidget *parent = nullptr);
    ~Calc();

private:
    Ui::Calc *ui;

    // Slots of buttons
private slots :
    void NumberPressed();
    void LetterPressed();
    void AddPressed();
    void SubtPressed();
    void EqualPressed();
    void ClrPressed();

};
#endif // CALC_H
