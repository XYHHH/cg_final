#include "OBJ.h"
using namespace std;
int eye_x = 0;
int eye_y = 0;
int eye_z = 5;
int currentW, currentH;
OBJ *monkey,*ant;
void keyboard(unsigned char key, int x, int y)
    {
        switch (key)
        {

        case 'a':
            eye_x -= 1;
            break;
        case 'd':
            eye_x += 1;
            break;
        case 'w':
            eye_y += 1;
            break;
        case 's':
            eye_y -= 1;
            break;
        default:
            break;
        }
        glLoadIdentity();
        gluPerspective(60, (GLfloat)currentW / (GLfloat)currentH, 1.0, 20); //创建透视投影矩阵(fovy,aspect,zNear,zFar);
        glMatrixMode(GL_MODELVIEW);
        gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);
        glutPostRedisplay();
    }

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);
    //glLoadIdentity();
    //monkey->render(1,0,0,0,0,-1);
    ant->render(-1,-2,0,0,0,1);
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //设置机口
    cout << "reshape!" << w << " " << h << endl;
    glLoadIdentity();
    currentH = h;
    currentW = w;
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 20); //创建透视投影矩阵(fovy,aspect,zNear,zFar);
    glMatrixMode(GL_MODELVIEW);

    gluLookAt(eye_x, eye_y, eye_z, 0, 0, 0, 0, 1, 0);
}


void init(void)
{
    glClearColor(1, 1, 1, 0);
    glShadeModel(GL_FLAT); //选择平面明暗模式或光滑明暗模式
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);


    monkey = new OBJ("gun.obj",0,0,1);
    ant = new OBJ("Ant-Man.obj",0,0,1);
    monkey->setScale(0.5);
    ant->setScale(1);
    // 光源

    GLfloat ambientLight[ ] = { 0.3f, 0.3f , 0.3f, 1.0f};
    GLfloat diffuseLight[ ] = { 0.7f, 0.7f, 0.7f, 1.0f};
    //设置并启用光照0
    glLightfv(GL_LIGHT0 , GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0 , GL_DIFFUSE, diffuseLight);
    //启动光源0：
    glEnable(GL_LIGHT0);
    //光的位置：
    GLfloat lightPos [ ] = { -5.0f, 5.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION, lightPos);
}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv); //固定格式
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
    glutInitWindowSize(400, 400);    //显示框的大小
    glutInitWindowPosition(400, 400); //确定显示框左上角的位置
    glutCreateWindow("OBJ");
    init();
    //monkey();
    //output_file();
    cout << " !" << endl;
    if (""==NULL) cout<<"asd"<<endl;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop(); //进人GLUT事件处理循环
    return 0;
}
