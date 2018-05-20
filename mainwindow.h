#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QByteArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief managementFinished
     * @param reply
     *
     * Called when replied after request
     */
    void managementFinished(QNetworkReply *reply);

    /**
     * @brief proceeding
     *
     * Proceeding appropriate request to selected url
     */
    void proceed();

private:
    /**
     * @brief initializeHttpTester
     *
     * Creating httpTester window content
     */
    void initializeHttpTester();

private:
    Ui::MainWindow *ui;

private: // httpTester content
    QWidget* mainWidget;

    QLineEdit* urlEdit;
    QLineEdit* dataEdit;
    QTextBrowser* responseViewer;
    QPushButton* proceedButton;

    QRadioButton* getRequest;
    QRadioButton* postRequest;
    QRadioButton* putRequest;

private: // Networking
    QNetworkAccessManager* manager;
    QNetworkRequest request;
};

#endif // MAINWINDOW_H
