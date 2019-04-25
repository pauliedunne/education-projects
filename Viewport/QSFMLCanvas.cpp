

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "QSFMLCanvas.h"

// Platform-specific headers
#ifdef Q_WS_X11
    #include <Qt/qx11info_x11.h>
    #include <X11/Xlib.h>
#endif


////////////////////////////////////////////////////////////
/// Construct the QSFMLCanvas
////////////////////////////////////////////////////////////
QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
QWidget       (Parent),
myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Setup the widget geometry
    move(Position);
    resize(Size);

    // Setup the timer
   // myTimer.setInterval(FrameTime);
}

////////////////////////////////////////////////////////////
/// Notification for the derived class that moment is good
/// for doing initializations
////////////////////////////////////////////////////////////
void QSFMLCanvas::OnInit()
{
    // Nothing to do by default...
}


////////////////////////////////////////////////////////////
/// Notification for the derived class that moment is good
/// for doing its update and drawing stuff
////////////////////////////////////////////////////////////
void QSFMLCanvas::OnUpdate()
{
    // Nothing to do by default...
}

////////////////////////////////////////////////////////////
/// Called when the widget is shown ;
/// we use it to initialize our SFML window
////////////////////////////////////////////////////////////
void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!myInitialized)
    {
        #ifdef Q_WS_X11
            XFlush(QX11Info::display());
        #endif
        // Create the SFML window with the widget handle
        sf::RenderWindow::create(sf::WindowHandle(winId()));

        // Let the derived class do its specific stuff
        OnInit();

        myInitialized = true;
    }
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
    return 0;
}

////////////////////////////////////////////////////////////
/// Called when the widget needs to be painted ;
/// we use it to display a new frame
////////////////////////////////////////////////////////////
void QSFMLCanvas::paintEvent(QPaintEvent*)
{
        // Display on screen
 //   RenderWindow::display();
    sf::Text text;
    text.setString("Hello");
    RenderWindow::draw(text);
}

