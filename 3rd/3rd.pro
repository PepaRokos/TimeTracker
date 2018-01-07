TEMPLATE = subdirs

SUBDIRS += LimeReport \
	qdecimal

LimeReport.file=LimeReport/limereport.pro

!exists(LimeReport/limereport.pro)|!exists(qdecimal/qdecimal.pro) {
    message("Run \"git submodule init\".")
}