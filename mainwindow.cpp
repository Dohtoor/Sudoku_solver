#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QFormLayout>
#include "sudoku.h"

QLineEdit *table[9][9];
bool enteredTable[9][9] = {false};
sudoku sud;
bool flag = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegularExpression numbers("[1-9]");
    QValidator *validator = new QRegularExpressionValidator(numbers);
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            table[i][j] = new QLineEdit();
            table[i][j]->setMinimumSize(30, 30);
            table[i][j]->setMaximumSize(30, 30);
            table[i][j]->setAlignment(Qt::AlignCenter);
            table[i][j]->setMaxLength(1);
            table[i][j]->setValidator(validator);
            ui->gridLayout->addWidget(table[i][j], i, j);
        }
    }

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<8; j++)
        {
             setTabOrder(table[i][j], table[i][j+1]);
        }
        if (i != 8)
            setTabOrder(table[i][8], table[i+1][0]);
    }
    setTabOrder(table[8][8], ui->pushButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    if (flag)
        return;
    QFont font(table[0][0]->font());
    font.setBold(true);
    QString member;
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            table[i][j]->setReadOnly(true);
            if (table[i][j]->text() != "")
            {
                member = table[i][j]->text();
                sud.set(i, j, member.toInt());
                enteredTable[i][j]=true;
            }
            else
            {
                table[i][j]->setFont(font);
            }
        }

    sud.solve();

    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            member = QString::number(sud.get(i,j));
            table[i][j]->setText(member);
        }
    flag = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    QFont font(table[0][0]->font());
    font.setBold(false);
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            table[i][j]->setText("");
            table[i][j]->setReadOnly(false);
            table[i][j]->setFont(font);
            enteredTable[i][j] = false;
        }
    sud.reset();
    flag = false;
}

void MainWindow::on_pushButton_3_clicked()
{
    QFont font(table[0][0]->font());
    font.setBold(false);
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
        {
            if (!enteredTable[i][j])
                table[i][j]->setText("");
            table[i][j]->setReadOnly(false);
            table[i][j]->setFont(font);
            enteredTable[i][j] = false;
        }
    flag = false;
    sud.reset();
}

void MainWindow::on_pushButton_4_clicked()
{
    QCoreApplication::quit();
}
