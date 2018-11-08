#include "globalsettingsform.h"
#include "ui_globalsettingsform.h"

#include <QMessageBox>
#include <QFileDialog>

#include "seasonnamedialog.h"
#include "globalsettings.h"
#include "../settingsservice.h"
#include "../seasonservice.h"
#include "../numberseriesservice.h"
#include "core-odb.hxx"

GlobalSettingsForm::GlobalSettingsForm(QWidget *parent) :
    FormBinder<GlobalSettings>(parent),
    ui(new Ui::GlobalSettingsForm)
{
    ui->setupUi(this);

    registerBinding(ui->firmName);
    registerBinding(ui->street);
    registerBinding(ui->houseNumber);
    registerBinding(ui->zipCode);
    registerBinding(ui->city);
    registerBinding(ui->ic);
    registerBinding(ui->vatPayer);
    registerBinding(ui->dic);
    registerBinding(ui->vatHigh);
    registerBinding(ui->vatFirstLower);
    registerBinding(ui->vatSecondLower);
    registerBinding(ui->web);
    registerBinding(ui->email);
    registerBinding(ui->phone);
    registerBinding(ui->singleUser);

    m_seriesModel = new AutoTableModel<NumberSeries>(this);
    m_seriesModel->setEditableCols(QList<int>() << 0);
    ui->tableNumSer->setModel(m_seriesModel);
}

GlobalSettingsForm::~GlobalSettingsForm()
{
    delete ui;
}

void GlobalSettingsForm::loadSeasons()
{
    ui->season->clear();
    SeasonService srv;
    m_seasons = srv.all();

    foreach (SeasonPtr season, m_seasons) {
        ui->season->addItem(season->name());

        if (season->active())
        {
            ui->season->setCurrentIndex(ui->season->count() - 1);
        }
    }
}

void GlobalSettingsForm::loadNumSeries()
{
    NumberSeriesService srvNumSer;
    SeasonService srvSeason;

    if (ui->season->currentIndex() >= 0)
    {
        SeasonPtr currentSeason = m_seasons[ui->season->currentIndex()];
        m_seriesModel->setData(srvNumSer.allForSeason(currentSeason));
    }
}

bool GlobalSettingsForm::saveRecord()
{
    SeasonService srvSeason;
    NumberSeriesService srvNumSer;

    SeasonPtr selSeason = m_seasons[ui->season->currentIndex()];
    if (selSeason->id() != Context::instance().currentSeason()->id())
    {
        if (QMessageBox::question(this, tr("Switch season"), tr("Realy switch active season?")) == QMessageBox::Yes)
        {
            srvSeason.activate(selSeason);
            Context::instance().setCurrentSeason(selSeason);
        }
        else
        {
            return false;
        }
    }

    foreach (SeasonPtr season, m_seasons) {
        srvSeason.update(season);
    }

    foreach (NumberSeriesPtr numSer, m_seriesModel->list()) {
        srvNumSer.update(numSer);
    }

    bindToData();
    SettingsService srv("CORE");
    srv.saveSettings(entity());

    return true;
}

void GlobalSettingsForm::loadEntity()
{
    SettingsService srv("CORE");
    QSharedPointer<GlobalSettings> settings = srv.loadSettings<GlobalSettings>();
    setEntity(settings);
    ui->grpVat->setEnabled(settings->vatPayer());

    if (!settings->logoPath().isEmpty())
    {
        ui->lblLogo->setPixmap(QPixmap(settings->logoPath()));
    }

    loadSeasons();
    loadNumSeries();
}

void GlobalSettingsForm::on_vatPayer_toggled(bool checked)
{
    ui->grpVat->setEnabled(checked);
}

void GlobalSettingsForm::on_season_currentIndexChanged(int)
{
    loadNumSeries();
}

void GlobalSettingsForm::on_btnEditName_clicked()
{
    SeasonPtr selSeason = m_seasons[ui->season->currentIndex()];
    SeasonNameDialog *dialog = new SeasonNameDialog(selSeason, this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();

    connect(dialog, &QDialog::accepted, [this](){
        this->loadSeasons();
    });
}

void GlobalSettingsForm::on_btnNew_clicked()
{
    if (QMessageBox::question(this, tr("New season"), tr("Realy create new season and switch to it?")) == QMessageBox::Yes)
    {
        SeasonPtr newSeason = SeasonPtr(new Season);
        SeasonNameDialog *dialog = new SeasonNameDialog(newSeason, this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->show();

        connect(dialog, &QDialog::accepted, [this, newSeason](){
           SeasonService srv;
           newSeason->setValidFrom(QDate::currentDate());
           srv.save(newSeason);
           srv.activate(newSeason);
           Context::instance().setCurrentSeason(newSeason);
           Context::instance().checkNumberSeries();

           this->loadSeasons();
           this->loadNumSeries();
        });
    }
}

void GlobalSettingsForm::on_pushButton_clicked()
{
    QString logoPath = QFileDialog::getOpenFileName(this, tr("Select logo"), "", tr("Images (*.png *.xpm *.jpg)"));
    if (!logoPath.isEmpty())
    {
        entity()->setLogoPath(logoPath);
        ui->lblLogo->setPixmap(QPixmap(logoPath));
    }
}
