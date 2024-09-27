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


void MainWindow::populateComboBox() {
    QString directoryPath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo"; // Укажите ваш путь
        QDir dir(directoryPath);
        QStringList files = dir.entryList(QDir::Files);

        // Фильтруем файлы, исключая те, которые заканчиваются на .zip
        QRegularExpression regex(".*\\.zip$", QRegularExpression::CaseInsensitiveOption);

        files.erase(std::remove_if(files.begin(), files.end(), [&](const QString& fileName) {
            return regex.match(fileName).hasMatch(); // Удаляем файлы, которые соответствуют регулярному выражению
        }), files.end());

        ui->comboBox->clear(); // Очищаем comboBox
        ui->comboBox->addItems(files); // Добавляем оставшиеся файлы в comboBox
}




void MainWindow::on_pushButton_clicked()
{
    QString filePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/output.txt"; // Имя файла

    // Получаем строку, введённую пользователем
    QString userInput = ui->lineEdit->text();

    if (userInput.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите строку для записи в файл.");
        return;
    }

    // 1. Создание и запись в файл
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << userInput << "\n"; // Записываем строку
        file.close();
        ui->textEdit->append("Файл успешно создан и записана строка: " + userInput);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл для записи.");
        return;
    }


    // 2. Чтение файла и вывод в textEdit
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




void MainWindow::on_pushButton_3_clicked()
{
    // Указываем полный путь к файлу
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
    QString jsonFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.json"; // Путь к файлу JSON

        // Создаём JSON объект
        QJsonObject jsonObj;
        jsonObj["name"] = "John Doe"; // Пример данных
        jsonObj["age"] = 30;           // Пример данных
        jsonObj["email"] = "john.doe@example.com"; // Пример данных

        // Сериализация объекта в формат JSON
        QJsonDocument jsonDoc(jsonObj);

        // 1. Запись JSON в файл
        QFile jsonFile(jsonFilePath);
        if (jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            jsonFile.write(jsonDoc.toJson());
            jsonFile.close();

            // Выводим сообщение о успешной записи в textEdit
            ui->textEdit->append("Файл JSON успешно создан и записаны данные:\n" + jsonDoc.toJson(QJsonDocument::Compact));
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать файл JSON для записи.");
            return;
        }

        // 2. Чтение файла JSON и вывод в textEdit
        if (jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QByteArray jsonData = jsonFile.readAll();
            jsonFile.close();

            // Выводим содержимое JSON в textEdit
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






void MainWindow::on_pushButton_5_clicked()
{
    QString jsonFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.json"; // Путь к файлу JSON

        // Проверяем, существует ли файл
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
    QString xmlFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.xml"; // Путь к файлу XML

        // Получаем строку, введённую пользователем
        QString userInput = ui->lineEdit->text();

        if (userInput.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите данные для записи в XML файл.");
            return;
        }

        // Создаём XML документ
        QDomDocument xmlDoc;
        QDomElement root = xmlDoc.createElement("root"); // Корневой элемент
        xmlDoc.appendChild(root);

        // Создаем новый элемент и добавляем данные
        QDomElement dataElement = xmlDoc.createElement("data");
        dataElement.appendChild(xmlDoc.createTextNode(userInput)); // Добавляем данные из lineEdit
        root.appendChild(dataElement);

        // 1. Запись XML в файл
        QFile xmlFile(xmlFilePath);
        if (xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&xmlFile);
            out << xmlDoc.toString(); // Записываем XML
            xmlFile.close();

            // Выводим сообщение о успешной записи в textEdit
            ui->textEdit->append("Файл XML успешно создан и записаны данные:\n" + xmlDoc.toString());
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать файл XML для записи.");
            return;
        }

        // 2. Чтение файла XML и вывод в textEdit
        if (xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString xmlContent = xmlFile.readAll();
            xmlFile.close();

            // Выводим содержимое XML в textEdit
            ui->textEdit->append("\nСодержимое файла XML:\n" + xmlContent);
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось прочитать файл XML.");
            return;
        }
        populateComboBox();
}


void MainWindow::on_pushButton_7_clicked()
{
    QString xmlFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/data.xml"; // Путь к файлу XML

        // Проверяем, существует ли файл
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
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip"; // Путь к ZIP-архиву
        QString selectedFile = ui->comboBox->currentText(); // Получаем выбранный файл
        QString filePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/" + selectedFile; // Полный путь к файлу

        // Проверяем, существует ли файл
        if (!QFile::exists(filePath)) {
            QMessageBox::warning(this, "Ошибка", "Выбранный файл не существует.");
            return;
        }

        // Создаем ZIP-архив с помощью QProcess
        QProcess process;
        QStringList arguments;
        arguments << "-r" << zipFilePath << selectedFile; // Добавляем файл в архив
        process.setWorkingDirectory("/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo"); // Установка рабочей директории
        process.start("zip", arguments);
        process.waitForFinished();

        // Выводим результат
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
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip"; // Путь к ZIP-архиву
        QString extractPath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo"; // Путь для разархивирования

        // Разархивируем файл
        process->start("unzip", QStringList() << zipFilePath << "-d" << extractPath); // Указываем путь для извлечения

        // Подключаем сигнал finished для обработки завершения процесса
        connect(process, &QProcess::finished, this, [this, zipFilePath](int exitCode, QProcess::ExitStatus exitStatus) {
            QString output = process->readAllStandardOutput();
            QString errorOutput = process->readAllStandardError();

            if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                ui->textEdit->append("Содержимое архива разархивировано:\n" + output);
                // Удаляем архив после успешного разархивирования
                QFile::remove(zipFilePath);
                ui->textEdit->append("Архив " + zipFilePath + " успешно удалён.");
                populateComboBox();
            } else {
                ui->textEdit->append("Ошибка при разархивировании:\n" + errorOutput);
            }
            process->deleteLater(); // Удаляем QProcess после завершения
        });
        populateComboBox();
}


void MainWindow::on_pushButton_9_clicked()//deletezip
{
    QString zipFilePath = "/Users/slayyyter/Desktop/Папки С Учебой/7sem/rzrbbezpo/archive.zip"; // Путь к ZIP-архиву

        // Удаляем ZIP-архив
        if (QFile::remove(zipFilePath)) {
            ui->textEdit->append("Архив " + zipFilePath + " успешно удалён.");
        } else {
            ui->textEdit->append("Ошибка при удалении архива " + zipFilePath + ".");
        }
        populateComboBox();
}

