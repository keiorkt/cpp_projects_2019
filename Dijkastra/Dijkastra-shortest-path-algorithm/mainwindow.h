#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "edgepalette.h"
#include "vertexpalette.h"
#include "graph.h"
#include "impl.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool drawVertexMode;

    bool drawEdgeMode;

    void backgroundInit();

    EdgePalette* edgePalette;

    VertexPalette* vertexPalette;

    Graph* graph;

    Impl* impl;

public slots:
    void onAddEdge(QPoint, QPoint, Vertex*, Vertex*);

    void onAddVertex(QPoint);

    void onDeleteVertex(Vertex*);

    void onDeleteEdge(Edge*);

private slots:
    void on_drawVertexButton_pressed();

    void on_drawEdgeButton_pressed();
};
#endif // MAINWINDOW_H
