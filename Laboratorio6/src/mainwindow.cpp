#include "mainwindow.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      central(new QWidget(this)),
      mainLayout(new QVBoxLayout),
      colorList(new QListWidget),
      displayLabel(new QLabel("Selecciona un color")),
      taskForm(new TaskForm)
{
    setupUi();
    populateColors();

    connect(colorList, &QListWidget::itemClicked, this, &MainWindow::onColorItemClicked);

    connect(taskForm, &TaskForm::textSubmitted, this, &MainWindow::onTaskTextSubmitted);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    setCentralWidget(central);
    central->setLayout(mainLayout);

    displayLabel->setAlignment(Qt::AlignCenter);
    displayLabel->setMinimumHeight(40);
    displayLabel->setFrameStyle(QFrame::Box | QFrame::Plain);

    mainLayout->addWidget(colorList);
    mainLayout->addWidget(displayLabel);
    mainLayout->addWidget(taskForm);
}

void MainWindow::populateColors()
{
    QStringList colors = {"Red", "Green", "Blue", "Yellow", "Magenta", "Cyan", "Black", "White", "Orange", "Purple"};
    for (const QString &c : colors)
    {
        QListWidgetItem *it = new QListWidgetItem(c);
        QColor qc(c);
        if (qc.isValid())
        {
            it->setBackground(qc);
        }
        colorList->addItem(it);
    }
}

void MainWindow::onColorItemClicked(QListWidgetItem *item)
{
    if (!item)
        return;
    const QString colorName = item->text();

    displayLabel->setText(colorName);

    QColor qc(colorName);
    QPalette pal = displayLabel->palette();
    if (qc.isValid())
    {
        pal.setColor(QPalette::Window, qc);
        displayLabel->setAutoFillBackground(true);
        displayLabel->setPalette(pal);

        QColor textColor = (qc.lightness() < 128) ? Qt::white : Qt::black;
        pal.setColor(QPalette::WindowText, textColor);
        displayLabel->setPalette(pal);
    }

    taskForm->setLabelText(QString("Última selección: %1").arg(colorName));
}

void MainWindow::onTaskTextSubmitted(const QString &text)
{
    displayLabel->setText(QString("Desde TaskForm: %1").arg(text));

    QList<QListWidgetItem *> matches = colorList->findItems(text, Qt::MatchFixedString | Qt::MatchCaseSensitive);
    if (!matches.isEmpty())
    {
        colorList->setCurrentItem(matches.first());
        onColorItemClicked(matches.first());
    }
}
