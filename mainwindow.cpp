#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::managementFinished);

    initializeHttpTester();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::managementFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        responseViewer->setText(reply->errorString());
        return;
    }

    responseViewer->setText(reply->readAll());
}

void MainWindow::proceed()
{
    QUrl url(urlEdit->text());

    if(!url.isValid())
    {
        responseViewer->setText("Invalid URL` " + urlEdit->text());
    }

    request.setUrl(url);

    if(getRequest->isChecked())
    {
        manager->get(request);
    }
    else if(postRequest->isChecked())
    {
        manager->post(request, QByteArray(dataEdit->text().toStdString().c_str()));
    }
    else
    {
        manager->put(request, QByteArray(dataEdit->text().toStdString().c_str()));
    }
}

void MainWindow::initializeHttpTester()
{
    mainWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    urlEdit = new QLineEdit();
    dataEdit = new QLineEdit();
    responseViewer = new QTextBrowser();

    QWidget* variantsWidget = new QWidget();
    QHBoxLayout* variantsLayout = new QHBoxLayout();

    getRequest = new QRadioButton("GET");
    postRequest = new QRadioButton("POST");
    putRequest = new QRadioButton("PUT");

    getRequest->setChecked(true);

    variantsLayout->addWidget(getRequest);
    variantsLayout->addWidget(postRequest);
    variantsLayout->addWidget(putRequest);

    variantsWidget->setLayout(variantsLayout);

    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    proceedButton = new QPushButton("Proceed");

    connect(proceedButton, &QPushButton::pressed,
            this, &MainWindow::proceed);

    buttonLayout->addWidget(proceedButton);
    buttonLayout->insertSpacing(0, 250);

    buttonWidget->setLayout(buttonLayout);

    mainLayout->addWidget(urlEdit);
    mainLayout->addWidget(dataEdit);
    mainLayout->addWidget(responseViewer);
    mainLayout->addWidget(variantsWidget);
    mainLayout->addWidget(buttonWidget);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    resize(400, 500);
}
