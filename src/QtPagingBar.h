#pragma once

#include <QToolButton>
#include <QLabel>

namespace Ui {
    class QtPagingBar;
}

class QtPagingBar : public QWidget
{
    Q_OBJECT

public:
    explicit QtPagingBar(QWidget *parent = nullptr);
    virtual ~QtPagingBar() override;

    void jump(int page, int ofpage, int total);

Q_SIGNALS:
    void clicked(int page);

private Q_SLOTS:
    void onClicked();

private:
    Ui::QtPagingBar *ui;

    QToolButton* newButton(int page, bool current=false);
    QLabel*      newEllipsis();

    void showTotals(int total);
};

