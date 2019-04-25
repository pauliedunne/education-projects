#ifndef GRAPHPORT_H
#define GRAPHPORT_H

#include <QDialog>
#include <QTextDocument>
#include <QFileDialog>
#include "qcpdocumentobject.h"
#include <QVector>
#include <QDebug>
#include <QTest>
#include "qcustomplot.h"


namespace Ui {
class GraphPort;
}

class GraphPort : public QDialog
{
    Q_OBJECT

public:
    explicit GraphPort(QWidget *parent = 0);
    ~GraphPort();

    void setupPlot();
    void setData(QVector<int> ac, QVector<int> rc, QVector<int> bc, QVector<int> sc, int steps);

private slots:
    void on_actionInsert_Plot_triggered();
    void on_actionSave_Document_triggered();

    void on_countRB_clicked();

    void on_differenceRB_clicked();

    void on_resourceRB_clicked();

private:
    Ui::GraphPort *ui;
    QVector<int> agentCount;
    QVector<int> redCount;
    QVector<int> blueCount;
    QVector<int> sugarCount;
    int stepCount;
};

#endif // GRAPHPORT_H
