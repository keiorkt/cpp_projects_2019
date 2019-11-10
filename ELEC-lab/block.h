#ifndef BLOCK_H
#define BLOCK_H

#include "impl.h"

#include <QLabel>
#include <string>

// Qt widget which supports drag-n-dropping

class Block : public QLabel
{
    Q_OBJECT

public:
    Block(const std::string &name, Impl *hostImpl, QWidget *parent = nullptr);

    QPoint getPositive();

    QPoint getNegative();

    QPoint getTerminal(int polar);

    void setPositive(const QPoint &start);

    void setNegative(const QPoint &end);

    //void updateDisplay(); // Interface of updating displayed text
    virtual void displayInfo() = 0; // Action for displaying voltage / current / resistance on a component

    std::string getName();

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

protected:
    void setImage(std::string path);

    void display(std::string text);

    bool needDisplay();

    virtual void rightClickAction(); // Action after right double click

private:
    std::string imagePath;

    std::string text;

    std::string name;

    Impl *hostImpl;

    QPoint start;

    QPoint end;
};

#endif // BLOCK_H
