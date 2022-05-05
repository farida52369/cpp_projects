#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_undo_clicked();
    void on_solveTheGame_clicked();
    void on_board_cellChanged(int row, int column);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
