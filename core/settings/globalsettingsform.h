#ifndef GLOBALSETTINGSFORM_H
#define GLOBALSETTINGSFORM_H

#include <QWidget>
#include "../formbinder.h"
#include "globalsettings.h"
#include "../autotablemodel.h"
#include "../data/numberseries.h"

namespace Ui {
class GlobalSettingsForm;
}

class GlobalSettingsForm : public FormBinder<GlobalSettings>
{
    Q_OBJECT

public:
    explicit GlobalSettingsForm(QWidget *parent = 0);
    ~GlobalSettingsForm();

private:
    Ui::GlobalSettingsForm *ui;
    AutoTableModel<NumberSeries> *m_seriesModel;
    QList<SeasonPtr> m_seasons;

    void loadSeasons();
    void loadNumSeries();

    // IForm interface
public slots:
    bool saveRecord() override;

    // IForm interface
public:
    void loadEntity() override;
private slots:
    void on_vatPayer_toggled(bool checked);
    void on_season_currentIndexChanged(int index);
    void on_btnEditName_clicked();
    void on_btnNew_clicked();
    void on_pushButton_clicked();
};

#endif // GLOBALSETTINGSFORM_H
