#include <QDebug>

#include <QByteArray>
#include <QFileInfo>

#include "module/epubexportEpubfile.h"

#include "module/epubexportZip.h"

EpubExportEpubfile::EpubExportEpubfile()
{
}

EpubExportEpubfile::~EpubExportEpubfile()
{
}

void EpubExportEpubfile::create()
{
    file = new EpubExportZip();
    file->createArchive(filename);
    // add mimetype to the current epub file
    // The mimetype file must be a text document in ASCII that contains the string application/epub+zip.
    // It must also be uncompressed, unencrypted, and the first file in the ZIP archive.
	addUncompressed("mimetype", QString("application/epub+zip"));
}

void EpubExportEpubfile::close()
{
delete file;
}

void EpubExportEpubfile::addFile(const QString& filename, const QString& path)
{
    QFileInfo fileinfo(filename);
    file->addFile(path, fileinfo.path(), getDefaultCompressionLevel(true));
}

void EpubExportEpubfile::addFileUncompressed(const QString& filename, const QString& path)
{
    QFileInfo fileinfo(filename);
    file->addFile(path, fileinfo.path(), getDefaultCompressionLevel(false));
}

void EpubExportEpubfile::add(QString filename, QString content)
{
    file->addString(filename, content, getDefaultCompressionLevel(true));
}

void EpubExportEpubfile::addUncompressed(QString filename, QString content)
{
    file->addString(filename, content, getDefaultCompressionLevel(false));
}

void EpubExportEpubfile::addUncompressed(QString filename, QByteArray content)
{
    file->addByteArray(filename, content, getDefaultCompressionLevel(false));
}

QDebug operator<<(QDebug dbg, const EpubExportEpubfile &epub)
{
    dbg.nospace() << "(" << "Debug not implemented" << ")";
    return dbg.space();
}
