#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edge.h"
#include "edgepalette.h"
#include "vertexpalette.h"
#include "vertex.h"
#include <QInputDialog>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph = new Graph();

    backgroundInit();

    // Set the background color of buttons
    ui->drawVertexButton->setStyleSheet("background-color:gray;");
    ui->drawEdgeButton->setStyleSheet("background-color:gray;");

    connect(edgePalette, SIGNAL(addEdge(QPoint,QPoint,Vertex*,Vertex*)),
            this, SLOT(onAddEdge(QPoint,QPoint,Vertex*,Vertex*)));

    connect(vertexPalette, SIGNAL(addVertex(QPoint)),
            this, SLOT(onAddVertex(QPoint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_drawVertexButton_pressed() {
    drawVertexMode = !drawVertexMode;
    vertexPalette->setVisible(drawVertexMode);

    if (drawVertexMode) {

        drawEdgeMode = false;
        edgePalette->setVisible(false);
        ui->drawEdgeButton->setStyleSheet("background-color:gray;");

        ui->drawVertexButton->setStyleSheet("background-color:black;");

    } else {

        ui->drawVertexButton->setStyleSheet("background-color:gray;");

    }
}

void MainWindow::on_drawEdgeButton_pressed() {
    drawEdgeMode = !drawEdgeMode;
    edgePalette->setVisible(drawEdgeMode);

    if (drawEdgeMode) {

        drawVertexMode = false;
        vertexPalette->setVisible(false);
        ui->drawVertexButton->setStyleSheet("background-color:gray;");

        ui->drawEdgeButton->setStyleSheet("background-color:black;");

    } else {

        ui->drawEdgeButton->setStyleSheet("background-color:gray;");

    }

}

void MainWindow::backgroundInit() {
    // Set the circuit background color to white
    ui->backgroundLabel->setStyleSheet("QLabel { background-color : white; }");

    // Add palette label
    vertexPalette = new VertexPalette(ui->backgroundLabel, ui->backgroundLabel->parentWidget());
    edgePalette = new EdgePalette(ui->backgroundLabel, graph, ui->backgroundLabel->parentWidget());
}

void MainWindow::onAddEdge(QPoint start, QPoint end, Vertex* startV, Vertex* endV) {
    bool ok;
    int weight = QInputDialog::getInt(this, tr("Input weight"), tr("weight"), 0, 1, 10000, 1, &ok);
    if (ok) {
        Edge *edge = new Edge(start, end, weight, startV, endV, "edge", ui->backgroundLabel);
        connect(edge, SIGNAL(onDelete(Edge*)), this, SLOT(onDeleteEdge(Edge*)));
        graph->addEdge(edge);
    }
}

void MainWindow::onDeleteEdge(Edge* e) {
    graph->removeEdge(e);
}

void MainWindow::onAddVertex(QPoint loc) {
    std::string name = "vertex";
    Vertex *vertex = new Vertex(loc, name, ui->backgroundLabel);
    connect(vertex, SIGNAL(onDelete(Vertex*)), this, SLOT(onDeleteVertex(Vertex*)));
    graph->addVertex(vertex);
}

void MainWindow::onDeleteVertex(Vertex* v) {
    graph->removeVertex(v);
}
