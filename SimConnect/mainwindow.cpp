#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    phSimConnect=NULL;
    simConnectDispTimer = new QTimer(this);
    connect(simConnectDispTimer, SIGNAL(timeout()), this, SLOT(checkNextDisp()));
    connect(this,SIGNAL(simConnectOpenEvent(QString)),this,SLOT(simConnectOpenReceived(QString)));
    simConnectDispTimer->start(200);
    displaytext="\n\n\n\n\n\n\n\n\n\n";
    response=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::checkNextDisp()
{
    HRESULT hr;//= SimConnect_CallDispatch(phSimConnect, MyDispatchProc, NULL);
    SIMCONNECT_RECV* pData;
    DWORD cbData;

    hr = SimConnect_GetNextDispatch(phSimConnect, &pData, &cbData);
    if (SUCCEEDED(hr))
    {
        switch(pData->dwID)
        {
        case SIMCONNECT_RECV_ID_OPEN:
        {
            // enter code to handle SimConnect version information received in a SIMCONNECT_RECV_OPEN structure.
            SIMCONNECT_RECV_OPEN *openData = (SIMCONNECT_RECV_OPEN*) pData;
            qDebug("SimConnect OPen");
            emit simConnectOpenEvent("Connected to Prepar3D");
            break;
        }
        case SIMCONNECT_RECV_ID_SIMOBJECT_DATA_BYTYPE:
        { SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA_BYTYPE*)pData;

            switch(pObjData->dwRequestID)
            {
            case REQUEST_1:
            {
                DWORD ObjectID = pObjData->dwObjectID;
                Struct1 *pS = (Struct1*)&pObjData->dwData;
                if (SUCCEEDED(StringCbLengthA(&pS->title[0], sizeof(pS->title), NULL))) // security check
                {
                    QString recMessag = QString("\nObjectID= %1 Title=%2 \n Lat=%3Lon= %4 Alt=%5").arg(ObjectID).arg(pS->title).arg(pS->latitude).arg(pS->longitude).arg(pS->altitude);
                    emit simConnectOpenEvent(recMessag);
                }
                break;
            }

            default:
                break;
            }
            break;
        }
        default:
            qDebug("Sicommnet Case defualt");
            qDebug()<<pData->dwID;
            break;
        }
    }
    else
    {
        // qDebug("Sicommnet does not dispatch message");

    }
}

void MainWindow::on_pushButton_clicked()
{
    HRESULT hr;
    if(SUCCEEDED(SimConnect_Open(&phSimConnect, "Managed Data Request", NULL,0, 0,0)))
    {
        qDebug("Connection done");
        // HRESULT hrevnt = SimConnect_SubscribeToSystemEvent(phSimConnect, EVENT_SIM_START, "SimStart");
        SimConnect_AddToDataDefinition(phSimConnect, DEFINITION_1, "Title", NULL, SIMCONNECT_DATATYPE_STRING256);
        hr = SimConnect_AddToDataDefinition(phSimConnect, DEFINITION_1, "Kohlsman setting hg", "inHg");
        hr = SimConnect_AddToDataDefinition(phSimConnect, DEFINITION_1, "Plane Altitude", "feet");
        hr = SimConnect_AddToDataDefinition(phSimConnect, DEFINITION_1, "Plane Latitude", "degrees");
        hr = SimConnect_AddToDataDefinition(phSimConnect, DEFINITION_1, "Plane Longitude", "degrees");

        // Request an event when the simulation starts
        hr = SimConnect_SubscribeToSystemEvent(phSimConnect, EVENT_SIM_START, "SimStart");

    }
    else
    {
        qDebug("Connection not done");
    }

}

void MainWindow::on_pushButton_2_clicked()
{

    SimConnect_RequestDataOnSimObjectType(phSimConnect,REQUEST_1,DEFINITION_1, 0, SIMCONNECT_SIMOBJECT_TYPE_USER);
    qDebug("Request Done");
}

void MainWindow::on_pushButton_3_clicked()
{
    SimConnect_Close(phSimConnect);
    phSimConnect = NULL;
    emit simConnectOpenEvent("Connection closed");


}
void MainWindow::simConnectOpenReceived(QString s )
{// remove first string from output

    displaytext = displaytext.replace(displaytext.indexOf("\n"),s.size(),s);

    // add the new string
    //displaytext=di += "\n" + response++ + ": " + s;

    // display it
    ui->label_2->setText(s);
}
