#include "QtPagingBar.h"
#include "ui_QtPagingBar.h"

QtPagingBar::QtPagingBar(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::QtPagingBar)
{
    ui->setupUi(this);
}

QtPagingBar::~QtPagingBar()
{
    delete ui;
}

void QtPagingBar::jump(int page, int ofpage, int total)
{
    foreach(QObject* obj, children())
    {
        if ( obj != ui->pagingBarLayout )
        {
            delete obj;
        }
    }

    showTotals(total);

    if ( total >0 )
    {
        // 纠正每页数量，不得小于 1
        if ( ofpage < 1 ) { ofpage = 1; }
        int allpage = (total + ofpage -1) /ofpage; // 总页数
        // 纠正当前页，不得小于 1 或大于总页数
        if ( page < 1 ) { page = 1; }
        if ( page > allpage ) { page = allpage; }

        if ( page <= 4 )
        {
            for( int i=1; i<=page; i++ )
            {
                ui->pagingBarLayout->addWidget(newButton(i, i==page));
            }
        }else
        {
            ui->pagingBarLayout->addWidget(newButton(1));
            ui->pagingBarLayout->addWidget(newEllipsis());
            ui->pagingBarLayout->addWidget(newButton(page-2));
            ui->pagingBarLayout->addWidget(newButton(page-1));
            ui->pagingBarLayout->addWidget(newButton(page, true));
        }
        if ( page < allpage )
        {
            ui->pagingBarLayout->addWidget(newButton(page+1));
        }
        if ( page+1 < allpage )
        {
            ui->pagingBarLayout->addWidget(newButton(page+2));
        }
        if ( page+2 < allpage )
        {
            ui->pagingBarLayout->addWidget(newEllipsis());
            ui->pagingBarLayout->addWidget(newButton(allpage));
        }
        QLabel* label = new QLabel(this);
        label->clear();
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        ui->pagingBarLayout->addWidget(label);
    }
}

void QtPagingBar::onClicked()
{
    Q_EMIT clicked(sender()->property("page").toInt());
}

QToolButton* QtPagingBar::newButton(int page, bool current)
{
    QToolButton* tb = new QToolButton(this);
    tb->setFont(font());
    if ( current )
    {
        tb->setEnabled(false);
        tb->setStyleSheet("QToolButton{border:1px solid #5555ff; background:#5555ff; color:white;}");
    }else
    {
        tb->setStyleSheet("QToolButton{border:1px solid #555555; background:white; color:#555555;}");
    }
    tb->setCursor(Qt::PointingHandCursor);
    tb->setText(QString::number(page));
    tb->setProperty("page", page);
    connect(tb, &QToolButton::clicked, this, &QtPagingBar::onClicked);
    return tb;
}

QLabel* QtPagingBar::newEllipsis()
{
    QLabel* label = new QLabel(this);
    label->setFont(font());
    label->setText(QStringLiteral("…"));
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    return label;
}

void QtPagingBar::showTotals(int total)
{
    QLabel* label = new QLabel(this);
    label->setFont(font());
    label->setText(QStringLiteral("共 ")+QString::number(total)+QStringLiteral(" 条 "));
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    ui->pagingBarLayout->addWidget(label);
}

