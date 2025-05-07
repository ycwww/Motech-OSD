#pragma once
#include <QString>
class file_operator
{
public:

	QString createFolder(const QString &folderPath);
	bool writeTextFile(const QString &filePath, const QString &content);
	bool writeInfo(const QString& fileName, const QString& szText, bool overWrite);
	bool readInfo(const QString& fileName, QList<QString>& readResult);

};

