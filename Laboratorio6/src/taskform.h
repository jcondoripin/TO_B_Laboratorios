#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>

namespace Ui
{
  class Task;
}

class TaskForm : public QWidget
{
  Q_OBJECT
public:
  explicit TaskForm(QWidget *parent = nullptr);
  ~TaskForm();

  QString lineEditText() const;
  void setLabelText(const QString &text);

signals:
  void textSubmitted(const QString &text);

private slots:
  void onSendClicked();

private:
  Ui::Task *ui;
};

#endif
