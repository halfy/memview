#ifndef NOTEPAD_H

#include <QtGui>
#include <QGLWidget>
#include "Math.h"
#include "GLImage.h"
#include "StopWatch.h"
#include "MemoryState.h"

class MemViewWidget;
class MemViewScroll;

class Window : public QMainWindow {
    Q_OBJECT

public:
	     Window(int argc, char *argv[]);
    virtual ~Window();

private:
    QMenu		*myFileMenu;
    QAction		*myQuit;

    static const int	 theVisCount = 3;

    QMenu		*myVisMenu;
    QActionGroup	*myVisGroup;
    QAction		*myVis[theVisCount];

    MemViewWidget	*myMemView;
    MemViewScroll	*myScrollArea;
    QGridLayout		*myLayout;
};

// A scroll area to contain the memory view.  We'll pass off control over
// the vertical scrollbar to MemViewWidget.
class MemViewScroll : public QAbstractScrollArea {
public:
    MemViewScroll(QWidget *parent)
	: QAbstractScrollArea(parent) {}

    // Viewport events need to be passed directly to the viewport.
    bool    viewportEvent(QEvent *) { return false; }
};

// A widget to render the memory visualization.
class MemViewWidget : public QGLWidget {
    Q_OBJECT

public:
	     MemViewWidget(int argc, char *argv[],
			    QScrollBar *vscrollbar,
			    QScrollBar *hscrollbar);
    virtual ~MemViewWidget();

    void	paint(QPaintEvent *event)
		{ paintEvent(event); }
protected:
    void	paintGL();
    void	resizeEvent(QResizeEvent *event);

    void	mousePressEvent(QMouseEvent *event);
    void	mouseMoveEvent(QMouseEvent *event);
    void	mouseReleaseEvent(QMouseEvent *event);

private slots:
    void    linear();
    void    block();
    void    hilbert();
    void    tick();

private:
    GLImage	 myImage;
    QTimer	*myTimer;
    QScrollBar	*myVScrollBar;
    QScrollBar	*myHScrollBar;

    MemoryState::AnchorInfo  myAnchor;
    MemoryState		    *myState;

    StopWatch	 myStopWatch;
    QPoint	 myDragPos;
    QPoint	 myDragDir;
    double	 myVelocity[2];
    bool	 myDragging;
};

#endif
