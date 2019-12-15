#ifndef VERTEXPALETTE_H
#define VERTEXPALETTE_H

#include <QLabel>
#include <QPoint>
#include <QPushButton>

class VertexPalette : public QLabel {
    Q_OBJECT

public:
    VertexPalette(QLabel *templateLabel,
            QWidget *parent = nullptr);

signals:
    void addVertex(QPoint);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    bool isPainting;

    QPoint startPoint;

    QPoint currentPoint;
};


#endif // VERTEXPALETTE_H
