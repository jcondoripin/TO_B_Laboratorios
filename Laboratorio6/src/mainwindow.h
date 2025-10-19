#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include "taskform.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onColorItemClicked(QListWidgetItem *item);
    void onTaskTextSubmitted(const QString &text);

private:
    // widgets (puedes también diseñar un .ui, aquí se hace en código para claridad)
    QWidget *central;
    QLayout *mainLayout;
    QListWidget *colorList;
    QLabel *displayLabel;
    TaskForm *taskForm;

    void setupUi(); // helper para construir la UI
    void populateColors();
};

#endif // MAINWINDOW_H
