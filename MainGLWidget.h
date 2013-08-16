#ifndef MAINGLWIDGET_H
#define MAINGLWIDGET_H

#include <QTimer>
#include <QtOpenGL>
#include <QGLWidget>
#include <QDateTime>
#include <QGLShader>
#include <QDebug>
#include "EyeTracker.h"

class MainGLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit MainGLWidget(QWidget *parent = 0);
    virtual ~MainGLWidget();
    
signals:
    
public slots:
    void onFatigueTimerTimeOut();
    void onBlinkDectected();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);

private:
    // ---- member ---- //
    const int   FATIGUE_LIMIT = 5000;  // 5s

    bool        toFlash = false;
    bool        toBlur  = false;
    QImage      img;
    QTimer     *pFatigueTimer;
    QDateTime   timestamp;

    QGLFramebufferObject *fboScene;
    QGLFramebufferObject *fboVBlur;
    QGLFramebufferObject *fboHBlur;

    QGLShaderProgram *shaderProgram;
    QGLShader *vertShader;
    QGLShader *fragShader;

    // blink detection
    EyeTracker *pTracker;
    QThread    *pTrackerThread;
    int         blinkCounter = 0;

    // opengl
    GLuint *texture = new GLuint[2];

    // ---- function ---- //
    void setupFatigueTimer();
    void setupEyeTracker();
    void setupGLTextures();
    void setupShader(const QString &vshader, const QString &fshader);

    void start();
    void stop();

    void renderWithTexture(GLuint tex);

    void outputLog(const QString &msg);
};

#endif // MAINGLWIDGET_H
