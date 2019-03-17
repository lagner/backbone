#pragma once
#include <QtQuick/QQuickItem>


namespace Backbone {


class PagePresenter;


// TODO: set background color
class Page
    : public QQuickItem
{
    Q_OBJECT

public:
    Page();
    ~Page();

    void classBegin() override;
    void componentComplete() override;
    void keyPressEvent(QKeyEvent * event) override;

    void setPagePresenter(PagePresenter * presenter);

private:
    PagePresenter * presenter_ = nullptr;
};


} // namespace Backbone
