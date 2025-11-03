#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define WIDTH 640
#define HEIGHT 480

static int dragging = 0;
static int start_x = 0, start_y = 0;
static int now_x = 0, now_y = 0;

static void display(void) {
    //背景を塗りつぶす
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //投影変換を指定するモードへ入る
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); //投影変換の変換行列を単位行列で初期化
    //各軸-1.0～1.0で囲まれる立方体の範囲にあるモノを垂直方向へ並行投影
    glOrtho(-WIDTH / 2, WIDTH / 2,
	    -HEIGHT / 2, HEIGHT / 2,
	    1.0, -1.0); //Z軸は……
    //垂直方向へ平行投影なので，
    //何もしないとカメラは(0.0, 0.0, 無限遠)から原点(0.0, 0.0, 0.0)を見ている状態になる
    //画面の中心が(0.0, 0.0, 0.0)となる．
    
    
    glMatrixMode(GL_MODELVIEW); //視野変換・モデリング変換モードへ
    glLoadIdentity(); //視野変換・モデリング変換の変換行列を単位行列で初期化
    //------ここから下でモデル・オブジェクトの描画をする-----------------
    
    //これから描く線の色を指定する(RGBA)
    glColor4f(1.0, 1.0, 1.0, 0.0);
    
    // 本体
    glBegin(GL_QUADS);
    glVertex3d(   0, -180, 0); //X座標，Y座標，Z座標: Z座標は0
    glVertex3d(   0,  180, 0);
    glVertex3d( 180,  180, 0);
    glVertex3d( 180, -180, 0);
    glEnd();
    
    glColor4f(1.0, 0.0, 0.0, 0.0);
    
    // 鼻
    int dx = 0, dy = 0;
    if (dragging) {
	dx = now_x - start_x;
	dy = -(now_y - start_y);
    }
    glBegin(GL_QUADS);
    glVertex3d(-180 + dx,   0 + dy, 0);
    glVertex3d(-180 + dx, 180 + dy, 0);
    glVertex3d(   0,      180,      0);
    glVertex3d(   0,        0,      0);
    glEnd();
    
    //-----------モデルの描画ここまで-------------------
    
    glutSwapBuffers();
}

static void resize(int windowWidth, int windowHeight) {
    glViewport(0, 0, windowWidth, windowHeight); //ウインドウ全体に表示
}

static void timer(int _){
    glutPostRedisplay();
    //この関数自身を100ms後に呼び出す指定
    glutTimerFunc(17, timer, 0);
}

static void mouse(int button, int state, int x, int y)
{
    if (button == 0) {
	if (state == 0) {
	    dragging = 1;
	    start_x = now_x = x;
	    start_y = now_y = y;
	} else {
	    dragging = 0;
	}
    }
}

static void motion(int x, int y)
{
    if (dragging) {
	now_x = x;
	now_y = y;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(WIDTH, HEIGHT); 
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    //GLUT_DEPTHを指定することで，Z軸が使える様になる．
    glutCreateWindow("2DGraphicsWithOrthoProjection_2");
    
    glutDisplayFunc(display);
    glutReshapeFunc(resize); //関数resizeをコールバックに設定
    
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    //黒で塗りつぶす指定をする
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    //移動させていくためのtimer関数を100ms後に呼び出す指定
    //一度呼んだら指定は消えるので，timer関数内の最後で再呼び出ししなければならない
    glutTimerFunc(17, timer, 0);
    
    //メインループ開始
    glutMainLoop();
    return 0;
}
