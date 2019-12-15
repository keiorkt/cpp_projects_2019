#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
#include <string>

class Block : public QLabel {
    Q_OBJECT

public:
    Block(const std::string &name, QWidget *parent = nullptr);

    std::string getName();

    QPoint getPositive();

    QPoint getNegative();

    QPoint getTerminal(int polar);

    void setPositive(const QPoint &start);

    void setNegative(const QPoint &end);

protected slots:
    bool eventFilter(QObject *, QEvent *event) override;

    void paintEvent(QPaintEvent *) override;

protected:
    virtual void rightClickAction();

private:
    std::string text;

    std::string name;

    QPoint start;

    QPoint end;
};

#endif // BLOCK_H
