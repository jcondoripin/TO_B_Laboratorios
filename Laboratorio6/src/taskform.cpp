#include "taskform.h"
#include "ui_Task.h"

TaskForm::TaskForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::Task)
{
  ui->setupUi(this);
  connect(ui->pushButtonSend, &QPushButton::clicked, this, &TaskForm::onSendClicked);
}

TaskForm::~TaskForm()
{
  delete ui;
}

QString TaskForm::lineEditText() const
{
  return ui->lineEditTask->text();
}

void TaskForm::setLabelText(const QString &text)
{
  ui->labelTask->setText(text);
}

void TaskForm::onSendClicked()
{
  const QString text = ui->lineEditTask->text();
  ui->labelTask->setText(text);
  emit textSubmitted(text);
}
