#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStorageInfo>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDomDocument>
#include <QDir>
#include <QFileDialog>
#include <QRegularExpression>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);

    QDir directory("/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo");
    QStringList files = directory.entryList(QDir::Files);
    ui->comboBox->addItems(files);

}

MainWindow::~MainWindow()
{
    delete ui;
}


#include <QProcess>
#include <QDebug>


void MainWindow::populateComboBox()  // Добавляем оставшиеся файлы в comboBox
{
    QString directoryPath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo";
        QDir dir(directoryPath);
        QStringList files = dir.entryList(QDir::Files);


        QRegularExpression regex(".*\\.zip$", QRegularExpression::CaseInsensitiveOption);

        files.erase(std::remove_if(files.begin(), files.end(), [&](const QString& fileName) {
            return regex.match(fileName).hasMatch();
        }), files.end());

        ui->comboBox->clear();
        ui->comboBox->addItems(files);
}




void MainWindow::on_pushButton_clicked() //FILE
{
    QString filePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/output.txt";


    QString userInput = ui->lineEdit->text();

    if (userInput.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите строку для записи в файл.");
        return;
    }

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << userInput << "\n";
        file.close();
        ui->textEdit->append("Файл успешно создан и записана строка: " + userInput);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл для записи.");
        return;
    }


    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContent = in.readAll();

        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл.");
        return;
    }
    populateComboBox();
}




void MainWindow::on_pushButton_3_clicked() //delete File
{

        QString filePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/output.txt";

        if (QFile::exists(filePath)) {
            if (QFile::remove(filePath)) {
                ui->textEdit->append("Файл успешно удалён");
                QMessageBox::information(this, "Успех", "Файл успешно удалён.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить файл.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Файл не существует.");
        }
        populateComboBox();
}



void MainWindow::on_pushButton_4_clicked() //json
{
    QString jsonFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.json";

        QJsonObject jsonObj;
        jsonObj["name"] = "John Doe";
        jsonObj["age"] = 30;
        jsonObj["email"] = "john.doe@example.com";

        QJsonDocument jsonDoc(jsonObj);

        QFile jsonFile(jsonFilePath);
        if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            jsonFile.write(jsonDoc.toJson());
            jsonFile.close();

            ui->textEdit->append("Файл JSON успешно создан и записаны данные:\n" + jsonDoc.toJson(QJsonDocument::Compact));
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать файл JSON для записи.");
            return;
        }

        if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray jsonData = jsonFile.readAll();
            jsonFile.close();

            ui->textEdit->append("\nСодержимое файла JSON:\n" + jsonData);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл JSON.");
            return;
        }
        populateComboBox();

}






void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    populateComboBox();
}


void MainWindow::on_action1_disk_triggered()
{
    ui->textEdit->clear();

    QProcess process;
    process.start("df", QStringList() << "-h");
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    ui->textEdit->append(output);
    populateComboBox();
}






void MainWindow::on_pushButton_5_clicked() //DELETE Json
{
    QString jsonFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.json";

        if (QFile::exists(jsonFilePath)) {
            if (QFile::remove(jsonFilePath)) {
                ui->textEdit->append("Файл JSON успешно удалён.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить файл JSON.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Файл JSON не существует.");
        }
    populateComboBox();
}


void MainWindow::on_pushButton_6_clicked() //XML
{
    QString xmlFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.xml";

        QString userInput = ui->lineEdit->text();

        if (userInput.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите данные для записи в XML файл.");
            return;
        }

        QDomDocument xmlDoc;
        QDomElement root = xmlDoc.createElement("root");
        xmlDoc.appendChild(root);

        QDomElement dataElement = xmlDoc.createElement("data");
        dataElement.appendChild(xmlDoc.createTextNode(userInput));
        root.appendChild(dataElement);

        QFile xmlFile(xmlFilePath);
        if (xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&xmlFile);
            out << xmlDoc.toString();
            xmlFile.close();

            ui->textEdit->append("Файл XML успешно создан и записаны данные:\n" + xmlDoc.toString());
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать файл XML для записи.");
            return;
        }

        if (xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString xmlContent = xmlFile.readAll();
            xmlFile.close();

            ui->textEdit->append("\nСодержимое файла XML:\n" + xmlContent);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл XML.");
            return;
        }
        populateComboBox();
}


void MainWindow::on_pushButton_7_clicked() //DELETE xml
{
    QString xmlFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.xml";

        if (QFile::exists(xmlFilePath)) {
            if (QFile::remove(xmlFilePath)) {
                ui->textEdit->append("Файл XML успешно удалён.");
            } else {
                QMessageBox::warning(this, "Ошибка", "Не удалось удалить файл XML.");
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Файл XML не существует.");
        }
        populateComboBox();
}


void MainWindow::on_pushButton_8_clicked() //zip
{
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip";
        QString selectedFile = ui->comboBox->currentText();
        QString filePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/" + selectedFile;

        if (!QFile::exists(filePath)) {
            QMessageBox::warning(this, "Ошибка", "Выбранный файл не существует.");
            return;
        }

        QProcess process;
        QStringList arguments;
        arguments << "-r" << zipFilePath << selectedFile;
        process.setWorkingDirectory("/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo");
        process.start("zip", arguments);
        process.waitForFinished();

        QString output = process.readAllStandardOutput();
        QString errorOutput = process.readAllStandardError();
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            ui->textEdit->append("Файл " + selectedFile + " успешно добавлен в архив " + zipFilePath);
            QFile::remove(filePath);
        } else {
            ui->textEdit->append("Ошибка при создании ZIP-архива:\n" + errorOutput);
        }
        populateComboBox();
}


void MainWindow::on_pushButton_10_clicked() //unzip
{
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip";
        QString extractPath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo";

        process->start("unzip", QStringList() << zipFilePath << "-d" << extractPath);

        connect(process, &QProcess::finished, this, [this, zipFilePath](int exitCode, QProcess::ExitStatus exitStatus) {
            QString output = process->readAllStandardOutput();
            QString errorOutput = process->readAllStandardError();

            if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                ui->textEdit->append("Содержимое архива разархивировано:\n" + output);
                QFile::remove(zipFilePath);
                ui->textEdit->append("Архив " + zipFilePath + " успешно удалён.");
                populateComboBox();
            } else {
                ui->textEdit->append("Ошибка при разархивировании:\n" + errorOutput);
            }
            process->deleteLater();
        });
        populateComboBox();
}


void MainWindow::on_pushButton_9_clicked()//deletezip
{
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip";

        if (QFile::remove(zipFilePath)) {
            ui->textEdit->append("Архив " + zipFilePath + " успешно удалён.");
        } else {
            ui->textEdit->append("Ошибка при удалении архива " + zipFilePath + ".");
        }
        populateComboBox();
}

