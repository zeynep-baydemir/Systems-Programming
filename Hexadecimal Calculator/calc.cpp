#include "calc.h"
#include "ui_calc.h"

int value = 0;
bool addition = false; //Control for + is pressed
bool subtraction = false; //Control for - is pressed
bool equal=false;   //Control for = is pressed
bool numCont=false; //Control for number is pressed

Calc::Calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calc)
{
    ui->setupUi(this);

    // Displays 0 on the screen when calculator is opened
    ui -> Screen -> setText(QString::number(value));

    QPushButton *numbers[10];
    QPushButton *letters[6];


    // Connects number bottons signals
    for(int i = 0; i<10; i++){
        QString name = "Button"+ QString::number(i);
        numbers[i] = Calc::findChild<QPushButton*>(name);
        connect(numbers[i], SIGNAL(released()),this, SLOT(NumberPressed()));
    }

    // Connects letter buttons signals
    for(int i = 0; i<6;i++){
        int j=i+65;
        QChar ch = j;
        QString name="";
        name+=ch;
        letters[i] = Calc::findChild<QPushButton*>(name);
        connect(letters[i], SIGNAL(released()),this, SLOT(LetterPressed()));
    }

    // Connects +,-,= and Clr buttons signals
    connect(ui->Add, SIGNAL(released()),this,SLOT(AddPressed()));
    connect(ui->Subt, SIGNAL(released()),this,SLOT(SubtPressed()));
    connect(ui->Equal, SIGNAL(released()),this,SLOT(EqualPressed()));
    connect(ui->Clr, SIGNAL(released()),this,SLOT(ClrPressed()));

}

Calc::~Calc()
{
    delete ui;
}

    // When number button is pressed
void Calc::NumberPressed(){
    QPushButton *but = (QPushButton*)sender();
    QString buttonval = but ->text();
    QString screenval = ui -> Screen->text();

    // if number isn't pressed before and + or - or = is pressed or 0 is displayed on the screen
    if(numCont==false && (addition||subtraction||equal||(QString ::compare(screenval,"0",Qt::CaseInsensitive)==0))){
       ui -> Screen -> setText(buttonval);
    }
    // if number is bigger than 1 digit
    else{
        QString numval = screenval+buttonval;
        ui -> Screen -> setText(numval);
    }
    numCont = true;
}
    // When letter button is pressed
void Calc::LetterPressed(){
    QPushButton *button = (QPushButton*)sender();
    QString buttonval = button ->text();
    QString screenval = ui -> Screen->text();

    // if number isn't pressed before and + or - or = is pressed or 0 is displayed on the screen
    if(numCont==false && (addition||subtraction||equal||(QString ::compare(screenval,"0",Qt::CaseInsensitive)==0))){
       ui -> Screen -> setText(buttonval);
    }
    // if number is bigger than 1 digit
    else{
        QString numval = screenval+buttonval;
        ui -> Screen -> setText(numval);
    }
    numCont = true;
}
    // When + button is pressed
void Calc::AddPressed(){
    QString screenval = ui->Screen->text();
    bool ok;

    // Cast value on the screen to int
    int decscreen = screenval.toInt(&ok,16);

    // if + button is pressed and number is pressed before
    if (addition && numCont){
        value = value+decscreen;
        // if value is negative, number is displayed on the screen with negative sign
        if(value<0){
            int newval = -value;
            QString hextotal = QString::number(newval,16).toUpper();
            QString eksi = "-";
            hextotal = eksi+hextotal;
            ui->Screen->setText(hextotal);
        }
        else{
            QString hextotal = QString::number(value,16).toUpper();
            ui->Screen->setText(hextotal);
        }
    }

    // if - button is pressed and number is pressed before
    else if(subtraction&&numCont){
        value =  value-decscreen;
        // if value is negative, number is displayed on the screen with negative sign
        if(value<0){
            int newval = -value;
            QString hextotal = QString::number(newval,16).toUpper();
            QString eksi = "-";
            hextotal = eksi+hextotal;
            ui->Screen->setText(hextotal);
        }
        else{
            QString hextotal = QString::number(value,16).toUpper();
            ui->Screen->setText(hextotal);
        }
        subtraction=false;
    }
    else{
        value = decscreen;
        subtraction = false;
    }
    subtraction = false;
    addition=true;
    numCont = false;
}

 // When - button is pressed
void Calc::SubtPressed(){
    QString screenval = ui->Screen->text();
    bool ok;
    int decscreen;
    // Cast value on the screen to int
    decscreen = screenval.toInt(&ok,16);
    // if + button is pressed and number is pressed before
    if (addition && numCont){
        value = value+decscreen;
        // if value is negative, number is displayed on the screen with negative sign
        if(value<0){
            int newval = -value;
            QString hextotal = QString::number(newval,16).toUpper();
            QString eksi = "-";
            hextotal = eksi+hextotal;
            ui->Screen->setText(hextotal);
        }
        else{
            QString hextotal = QString::number(value,16).toUpper();
            ui->Screen->setText(hextotal);
        }
        addition = false;
    }
    // if - button is pressed and number is pressed before
    else if(subtraction && numCont){
        value =  value-decscreen;
        // if value is negative, number is displayed on the screen with negative sign
        if(value<0){
            int newval = -value;
            QString hextotal = QString::number(newval,16).toUpper();
            QString eksi = "-";
            hextotal = eksi+hextotal;
            ui->Screen->setText(hextotal);
        }
        else{
            QString hextotal = QString::number(value,16).toUpper();
            ui->Screen->setText(hextotal);
        }

    }

    else{
        value = decscreen;
    }
    addition = false;
    subtraction=true;
    numCont = false;
}

    // When = button is pressed
void Calc::EqualPressed(){
    int total = 0;
    QString screenval = ui -> Screen->text();
    bool ok;
    // Cast value on the screen to int
    int decscreen = screenval.toInt(&ok,16);
      // if + button is pressed and number is pressed before
    if (addition && numCont){
        total = decscreen + value;
        QString hextotal = QString::number(total,16).toUpper();
        ui->Screen->setText(hextotal);
    }
    // if - button is pressed and number is pressed before
    else if(subtraction && numCont){
        total =  value-decscreen;
        // if total is negative, number is displayed on the screen with negative sign
        if(total<0){
            total = -total;
            QString hextotal = QString::number(total,16).toUpper();
            QString eksi = "-";
            hextotal = eksi+hextotal;
            ui->Screen->setText(hextotal);
        }
        else{
            QString hextotal = QString::number(total,16).toUpper();
            ui->Screen->setText(hextotal);
        }

    }
    else {
        ui->Screen->setText(screenval);
    }
    equal = true;
    addition=false;
    subtraction = false;
    numCont = false;
}
 // When clr is pressed, clear everything
void Calc::ClrPressed(){
    addition = false;
    subtraction = false;
    numCont = false;
    equal = false;
    ui->Screen->setText("0");
    value=0;

}


