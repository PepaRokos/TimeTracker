#include "variablefiller.h"
#include "../settingsservice.h"

VariableFiller::VariableFiller()
{
}

VariableFiller::~VariableFiller()
{
}

void VariableFiller::fill(ReportPtr report, int recordId)
{
    if (m_settings.isNull())
    {
        loadSettings();
    }

    QMap<QString, QString> vars;
    vars[COMPANY] = m_settings->firmName();
    vars[STREET] = m_settings->street();
    vars[HOUSE_NUMBER] = m_settings->houseNumber();
    vars[CITY] = m_settings->city();
    vars[ZIP_CODE] = m_settings->zipCode();
    vars[IC] = QString::number(m_settings->ic());
    vars[DIC] = m_settings->dic();
    vars[LOGO_PATH] = m_settings->logoPath();
    vars[WEB] = m_settings->web();
    vars[EMAIL] = m_settings->email();
    vars[PHONE] = m_settings->phone();

    if (recordId > 0)
    {
        vars[RECORD_ID] = QString::number(recordId);
    }
    else
    {
        vars[RECORD_ID] = "";
    }

    report->setVariables(vars);
}

void VariableFiller::fillList(QList<ReportPtr> reports, int recordId)
{
    foreach (ReportPtr report, reports) {
        fill(report, recordId);
    }
}

void VariableFiller::loadSettings()
{
    SettingsService srv("CORE");
    m_settings = srv.loadSettings<GlobalSettings>();
}
