#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <SimConnect.h>
#include <QTimer>
#include <string>
struct Struct1
{
    char    title[256];
    double  kohlsmann;
    double  altitude;
    double  latitude;
    double  longitude;
};

enum EVENT_ID{
    EVENT_SIM_START,
};

enum DATA_DEFINE_ID {
    DEFINITION_1,
};

enum DATA_REQUEST_ID {
    REQUEST_1,
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //void CALLBACK MyDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
signals:
    void simConnectOpenEvent(QString);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void checkNextDisp();
    void simConnectOpenReceived(QString);


private:

    Ui::MainWindow *ui;
    HANDLE phSimConnect;
    QTimer *simConnectDispTimer;
    QString displaytext;
    int response;

};

#endif // MAINWINDOW_H
