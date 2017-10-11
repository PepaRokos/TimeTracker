#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class EndDialog;
}

class EndDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndDialog(QWidget *parent = 0);
    ~EndDialog();
    QDateTime end();
    void setRefDateTime(const QDateTime &start);

private:
    Ui::EndDialog *ui;
    QDateTime m_refDateTime;

    // QDialog interface
public slots:
    virtual void accept() override;
};

#endif // ENDDIALOG_H
