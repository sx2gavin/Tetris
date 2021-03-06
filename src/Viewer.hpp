#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QtGlobal>
#include <vector>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#else 
#include <QGLBuffer>
#endif

class Game;

class Viewer : public QGLWidget {
    
    Q_OBJECT

	enum drawMode {WIRE_FRAME, FACE, MULTICOLOURED};

public:
    Viewer(const QGLFormat& format, QWidget *parent = 0);
    virtual ~Viewer();
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
	void newGame();
	void resetGame();
	void wireframeMode();
	void faceMode();
	void multicolouredMode();
	void slowSpeed();
	void mediumSpeed();
	void fastSpeed();


    // If you want to render a new frame, call do not call paintGL(),
    // instead, call update() to ensure that the view gets a paint 
    // event.
  
protected:

    // Events we implement

    // Called when GL is first initialized
    virtual void initializeGL();
    // Called when our window needs to be redrawn
    virtual void paintGL();
    // Called when the window is resized (formerly on_configure_event)
    virtual void resizeGL(int width, int height);
    // Called when a mouse button is pressed
    virtual void mousePressEvent ( QMouseEvent * event );
    // Called when a mouse button is released
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    // Called when the mouse moves
    virtual void mouseMoveEvent ( QMouseEvent * event );
	// Called when a key is pressed
	virtual void keyPressEvent ( QKeyEvent * event );
	// Called when a key is released
	virtual void keyReleaseEvent ( QKeyEvent * event ); 

private slots:
	void updateGame();

private:

    QMatrix4x4 getCameraMatrix();
    void translateWorld(float x, float y, float z);
    void rotateWorld(float x, float y, float z);
    void scaleWorld(float x, float y, float z);	
	void defineCubeGeometry();
	void defineUWellGeometry();
	void addWell(QMatrix4x4 modelMatrix, QVector4D color);
	void addBlock(int x, int y, QVector4D color);
	void drawCurrentGameState();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QOpenGLBuffer mVertexBufferObject;
    QOpenGLVertexArrayObject mVertexArrayObject;
#else 
    QGLBuffer mVertexBufferObject;
#endif

    int mVertexLocation;
    int mMvpMatrixLocation;
	int mColorLocation;

	Game *game;

    QMatrix4x4 mPerspMatrix;
	std::vector<QMatrix4x4> mWellModelMatrices;
	std::vector<QVector4D> mWellColors;
	std::vector<QMatrix4x4> mBlockModelMatrices;
	std::vector<QVector4D> mBlockColors;
    QMatrix4x4 mTransformMatrix;
    
    QTimer* mTimer;
	int counter;
	int speed;
    QGLShaderProgram mProgram;
	
	// for scale and rotate.
	Qt::MouseButton pressedMouseButton;
	int prePos;
	bool shiftPressed;
	QVector3D persistenceAxis;
	int persistenceSpeed;

	drawMode mode;

};

#endif
