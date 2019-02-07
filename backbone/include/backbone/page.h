#pragma once
#include <QtQuick/QQuickItem>


namespace Backbone {


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

private:
};


} // namespace Backbone
