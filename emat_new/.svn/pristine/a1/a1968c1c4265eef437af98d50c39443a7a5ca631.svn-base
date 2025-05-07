#include "file_operator.h"
#include <QDir>
#include <QDebug>
#include <QDate>
#include <QMessageBox>

// 创建文件夹函数
QString file_operator::createFolder(const QString &folderPath) 
{
	QDir dir(folderPath);
	if (!dir.exists()) 
	{
		if (!dir.mkpath(".")) 
		{
			qDebug() << "Failed to create directory:" << folderPath;
			return QString();
		}
	}

	QString dateFolderName = QDate::currentDate().toString("yyyy-MM-dd");
	QString dateFolderPath = folderPath + QDir::separator() + dateFolderName;
	QDir dateDir(dateFolderPath);
	if (!dateDir.exists()) 
	{
		if (!dateDir.mkpath("."))
		{
			qDebug() << "Failed to create date directory:" << dateFolderPath;
			return QString();
		}
	}

	return dateFolderPath;
}

bool file_operator::writeTextFile(const QString &filePath, const QString &content) 
{
	QFile file(filePath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Failed to open file for writing:" << filePath;
		return false;
	}

	QTextStream out(&file);
	out << content;
	file.close();

	qDebug() << "Content written to file:" << filePath;
	return true;
}
bool file_operator::writeInfo(const QString& fileName, const QString& szText, bool overWrite)
{
	if (0 == fileName.length())
		return false;

	QFile writeFile(fileName);
	if (overWrite)
	{
		if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
		{
			QMessageBox::warning(NULL, "warning", "Cannot Open the file:" + fileName, QMessageBox::Yes);
			return false;
		}
		QTextStream out(&writeFile);
		out << szText;
		writeFile.close();

	}
	else
	{
		if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
		{
			QMessageBox::warning(NULL, "warning", "Cannot Open the file:" + fileName, QMessageBox::Yes);
			return false;
		}
		QTextStream out(&writeFile);
		out << szText;
		writeFile.close();
	}
	return true;
}

 bool file_operator::readInfo(const QString& fileName, QList<QString>& readResult)
{
	QFile readFile(fileName);
	if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(NULL, "warning", "cannot open file", QMessageBox::Yes);
		return false;
	}
	while (!readFile.atEnd())
	{
		QByteArray line = readFile.readLine();
		QString str(line);
		if ((str != QString::null) && (str != " ") && (str != "\n"))
		{
			readResult.push_back(str);
		}
	}
	return true;
}






