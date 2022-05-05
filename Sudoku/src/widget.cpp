#include "widget.h"
#include "ui_widget.h"

// classes created
#include "GenerateSudoku.h"

// Board Dimensions
#define N 9

int board[N][N]; //  Main board
int temp_board[N][N]; // If user needed solution


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // ComboBox Values __ To Start New Game
    // According to chosen Level
    QStringList levels = {"Easy", "Meduim", "Hard"};
    foreach (QString s, levels) {
        ui->comboBox->addItem(s);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    ui->board->clear();

    // Initialize The array in the begining of every New Game
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    // Generate The Sudoku Board
    GenerateSudoku::generateSudoku(board, index);

    // Initialize The Table Widget with empty "" -> board[i][j] = 0
    // with The value -> board[i][j] != 0
    for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                    if (board[i][j] != 0){
                        QTableWidgetItem* item = ui->board->item(i, j);
                        if(!item) {
                            item = new QTableWidgetItem();
                            ui->board->setItem(i, j, item);
                        }
                        item->setText(QString::number(board[i][j]));
                        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                    }
                    temp_board[i][j] = board[i][j];
            }
      }
}

void Widget::on_undo_clicked()
{
    QTableWidgetItem* item = ui->board->currentItem();
    if(!item) {
        item = new QTableWidgetItem();
        ui->board->setCurrentItem(item);
    }
    item->setText("");
    // ui->board->setCurrentItem("");
}

void Widget::on_solveTheGame_clicked()
{
    GenerateSudoku::solve(temp_board);
    for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                QTableWidgetItem* item = ui->board->item(i, j);
                if(!item) {
                    item = new QTableWidgetItem();
                    ui->board->setItem(i, j, item);
                }
                item->setText(QString::number(temp_board[i][j]));
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
      }
}

void Widget::on_board_cellChanged(int row, int column)
{
        QTableWidgetItem* item = ui->board->item(row, column);
        if (!((item->text().toInt() > 0 && item->text().toInt() < 10) || item->text() == ""))  {
            if(!item) {
                item = new QTableWidgetItem();
                ui->board->setItem(row, column, item);
            }
            item->setText("");
            ui->label->setText("Warning: add only numbers from [1:9]");
        }
}
