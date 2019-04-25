#include "GraphPort.h"
#include "ui_GraphPort.h"

GraphPort::GraphPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphPort)
{
    ui->setupUi(this);
    connect(ui->cbUseCurrentSize, SIGNAL(toggled(bool)), ui->sbWidth, SLOT(setDisabled(bool)));
    connect(ui->cbUseCurrentSize, SIGNAL(toggled(bool)), ui->sbHeight, SLOT(setDisabled(bool)));
    ui->plot->axisRect()->setMinimumSize(300, 180);
    ui->differenceRB->setChecked(true);
    ui->countRB->setChecked(false);
    ui->resourceRB->setChecked(false);
    // setupPlot();
    // register the plot document object (only needed once, no matter how many plots will be in the QTextDocument):
    QCPDocumentObject *plotObjectHandler = new QCPDocumentObject(this);
    ui->textEdit->document()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, plotObjectHandler);
}

GraphPort::~GraphPort()
{
    delete ui;
}

void GraphPort::setupPlot()
{

    QVector<double> x, y, x2, y2; // Initialize co-ords
    // Graph for Agent Count over each Step
    if(ui->countRB->isChecked())
    {
        ui->plot->removeGraph(0); // Remove existing graphs
        ui->plot->removeGraph(1); // ...
        ui->plot->addGraph();     // Add New Graph
        ui->plot->graph(0)->setPen(QPen(Qt::black));
        x.push_back(0); // Set X starting point to 0
        y.push_back(0); // Set Y starting point to 0
        for (int i=0; i< stepCount; ++i)
        {
            // Set the Data for the graph
          x.push_back(stepCount / stepCount + i);
          y.push_back(agentCount[i]);
        }
        ui->plot->graph(0)->setData(x, y); // Add Data to the Graph
        ui->plot->graph(0)->setName("Agent Count");
        ui->plot->xAxis->setRange(0, stepCount);
        ui->plot->yAxis->setRange(0, 1000);
        ui->plot->replot();
    }
    // Red and Blue Agent Population Compared in Graph over Steps
    if(ui->differenceRB->isChecked())
    {
        ui->plot->addGraph();
        ui->plot->graph(0)->setPen(QPen(Qt::red));
        ui->plot->addGraph();
        ui->plot->graph(1)->setPen(QPen(Qt::blue));
        x.push_back(0);
        y.push_back(0);
        x2.push_back(0);
        y2.push_back(0);
        for (int i=0; i< stepCount; ++i)
        {
            x.push_back(stepCount / stepCount + i);
            y.push_back(redCount[i]);
            x2.push_back(stepCount / stepCount + i);
            y2.push_back(blueCount[i]);
        }
        ui->plot->graph(0)->setData(x, y);
        ui->plot->graph(1)->setData(x2, y2);
        ui->plot->xAxis->setRange(0, stepCount);
        ui->plot->yAxis->setRange(0, 1000);
        ui->plot->replot();
    }
    // Graphs for Sugar and Spice Count (If Spice is Enabled) over each step
    if(ui->resourceRB->isChecked())
    {
        ui->plot->removeGraph(0);
        ui->plot->removeGraph(1);
        ui->plot->graph(0)->setPen(QPen(Qt::green));
        x.push_back(0);
        y.push_back(0);
        for (int i=0; i< stepCount; ++i)
        {
            x.push_back(stepCount / stepCount + i);
            y.push_back(sugarCount[i]);
        }
        ui->plot->addGraph();
        ui->plot->graph(0)->setData(x, y);
        ui->plot->xAxis->setRange(0, stepCount);
        ui->plot->yAxis->setRange(0, 1000);
        ui->plot->replot();
    }
    // create graph and assign data to it:
    // give the axes some labels:
    ui->plot->xAxis->setLabel("Steps");
    ui->plot->yAxis->setLabel("Count");
    // set axes ranges, so we see all data:

    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void GraphPort::on_actionInsert_Plot_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();

    // insert the current plot at the cursor position. QCPDocumentObject::generatePlotFormat creates a
    // vectorized snapshot of the passed plot (with the specified width and height) which gets inserted
    // into the text document.
    double width = ui->cbUseCurrentSize->isChecked() ? 0 : ui->sbWidth->value();
    double height = ui->cbUseCurrentSize->isChecked() ? 0 : ui->sbHeight->value();
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), QCPDocumentObject::generatePlotFormat(ui->plot, width, height));

    ui->textEdit->setTextCursor(cursor);
}

void GraphPort::on_actionSave_Document_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document...", qApp->applicationDirPath(), "*.pdf");
    if (!fileName.isEmpty())
    {
        QPrinter printer;
        printer.setFullPage(true);
        printer.setPaperSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->document()->print(&printer);
    }
}

void GraphPort::setData(QVector<int> ac, QVector<int> rc, QVector<int> bc, QVector<int> sc, int steps)
{
    agentCount = ac;
    // qDebug() << agentCount[0];
    redCount = rc;
    // qDebug() << redCount[0];
    blueCount = bc;
    // qDebug() << blueCount[0];
    sugarCount = sc;
   // qDebug() << sugarCount[0];
    if(steps > 0)
    {
        stepCount = steps;

    }
    else { stepCount = agentCount.size(); }
    // qDebug() << stepCount;
    // qDebug() << agentCount.size();
}

void GraphPort::on_countRB_clicked()
{
    setupPlot();
}

void GraphPort::on_differenceRB_clicked()
{
    setupPlot();
}

void GraphPort::on_resourceRB_clicked()
{
    setupPlot();
}
