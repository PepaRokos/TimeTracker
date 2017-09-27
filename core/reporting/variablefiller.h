#ifndef VARIABLEFILLER_H
#define VARIABLEFILLER_H

#include "report.h"
#include "../settings/globalsettings.h"
#include "../core_global.h"

#define COMPANY "COMPANY"
#define STREET "STREET"
#define HOUSE_NUMBER "HOUSE_NUMBER"
#define CITY "CITY"
#define ZIP_CODE "ZIP_CODE"
#define IC "IC"
#define DIC "DIC"
#define LOGO_PATH "LOGO_PATH"
#define RECORD_ID "RECORD_ID"
#define WEB "WEB"
#define EMAIL "EMAIL"
#define PHONE "PHONE"

class CORESHARED_EXPORT VariableFiller
{
public:
    VariableFiller();
    virtual ~VariableFiller();

    virtual void fill(ReportPtr report, int recordId = 0);
    void fillList(QList<ReportPtr> reports, int recordId = 0);
    void loadSettings();

private:
    GlobalSettingsPtr m_settings;
};

#endif // VARIABLEFILLER_H
