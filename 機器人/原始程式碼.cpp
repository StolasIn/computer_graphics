#include <windows.h>
#include <bits/stdc++.h>
#include <GL/glut.h>

#define TORSO_HEIGHT 9.0
#define TORSO_RADIUS 5.0
#define UPPER_ARM_HEIGHT 2.8
#define LOWER_ARM_HEIGHT 2.8
#define LOWER_LEG_RADIUS 1.0
#define LOWER_LEG_HEIGHT 1.5
#define UPPER_LEG_HEIGHT 1.5
#define UPPER_LEG_RADIUS 1.0
#define UPPER_ARM_RADIUS 1.0
#define LOWER_ARM_RADIUS 1.0
#define HEAD_HEIGHT 4.5
#define HEAD_RADIUS 4.95

#define none 0
#define motion_1 1
#define motion_2 2
#define motion_3 3
#define motion_4 4
#define motion_5 5
#define dance1 6
#define dance2 7

using namespace std;

static GLint motion = 0;

static GLfloat theta[30] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                            0.0,0.0};
static GLfloat mot[]={0.0,0.0,0.0,0.0};
static GLint angle = 2;

GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul, *h1;


static GLint step[100]={4,4,4,4,4,4,20,20,10,
                        10,5,5,10,10,6,6,6,6,6,
                        4,4,4,4,4,4,4,4,10,10,-10,
                        -10,10,-10,4,4,4,4,-4,10};

static GLint init_step[100]={4,4,4,4,4,4,20,20,10,
                            10,5,5,10,10,6,6,6,6,6,
                            4,4,4,4,4,4,4,4,10,10,-10,
                            -10,10,-10,4,4,4,4,-4,10};

double basePos[] = { 0, -5, -5 };
double baseRotate[] = { 0, 0, 0 };
double fan_size = 5;

int walk_state = 0;
int dance_state = 0;
int bye_state = 0;
int cnt=0;

void reset(void);

void torso()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,50,50);
    glPopMatrix();
}

void head()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*HEAD_HEIGHT-2,0.0);

    //白色眼睛
    glColor3f(1,1,1);
    glTranslated(-2.0,2.0,3.5);
    gluSphere(h,0.5,100,100);
    glTranslated(2.0,-2.0,-3.5);
    glTranslated(2.0,2.0,3.5);
    gluSphere(h,0.5,100,100);
    glTranslated(-2.0,-2.0,-3.5);

    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //金色光環
    glColor3f(0.85,0.65,0.13);
    glTranslated(0,-0.5,5);
    gluCylinder(h1,1.5,1.5, 0.5,10,10);
    glTranslated(0,0.5,-5);

    //金色角
    glColor3f(1,0.84,0.0);
    glRotatef(-30.0, 0.0, 1.0, 1.0);
    glTranslated(-1.5,-2.5,2.5);
    gluCylinder(h1,0.5,0, 3.5,10,10);
    glTranslated(1.5,2.5,-2.5);
    glRotatef(60.0, 0.0, 1.0, 1.0);

    glTranslated(1.5,-2.5,2.5);
    gluCylinder(h1,0.5,0, 3.5,10,10);
    glTranslated(-1.5,2.5,-2.5);
    glRotatef(-30.0, 0.0, 1.0, 1.0);

    //頭
    glColor3f(0.484,0.985,0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h,1,100,100);
    glPopMatrix();
}

void left_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);

    //圓球關節
    gluSphere(h1,0.95,50,50);
    glPopMatrix();
}

void left_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glTranslated(0.0,0.0,2.8);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    glTranslatef(0.0, 0.0, 1);
    glRotatef(mot[0], 0.0, 0.0, 1.0);
    glColor3f(0.5,0.5,0.5);

    //電風扇
    gluDisk(h1,0,fan_size,3,10);
    glColor3f(0.484,0.985,0);
    glPopMatrix();
}

void right_upper_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(rua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);

    //圓球關節
    gluSphere(h1,0.95,50,50);
    glPopMatrix();
}

void right_lower_arm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(rla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glTranslated(0.0,0.0,2.8);

    //圓球關節
    gluSphere(h1,0.95,50,50);
    glPopMatrix();
}

void left_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void left_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glTranslated(0.0,0.0,1.5);

    //圓球關節
    gluSphere(h1,0.95,50,50);
    glPopMatrix();
}

void right_upper_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}

void right_lower_leg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);

    //圓球關節
    gluSphere(h1,0.95,50,50);

    //主幹
    gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT,10,10);
    glTranslated(0.0,0.0,1.5);

    //圓球關節
    gluSphere(h1,0.95,50,50);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //主顏色
    glColor3f(0.484,0.985,0);

    //調整物體位置
    glTranslatef(basePos[0], basePos[1], basePos[2]);

    //調整物體旋轉
    glRotatef(baseRotate[0], 1.0, 0.0, 0.0);
    glRotatef(baseRotate[1], 0.0, 1.0, 0.0);
    glRotatef(baseRotate[2], 0.0, 0.0, 1.0);

    //調整物體模擬上下跳動的感覺
    if(motion != none){
        if(motion != motion_2){
            glTranslatef(0,-theta[9]/60,0);
            glTranslatef(0,-theta[7]/60,0);
        }
        else{
            glTranslatef(0,theta[9]/80,0);
            glTranslatef(0,theta[7]/80,0);
        }
        glTranslatef(0,-theta[11]/48,0);
        glTranslatef(0,-theta[20]/40,0);
        glTranslatef(0,-theta[25]/60,0);
        glTranslatef(0,-theta[26]/60,0);
    }

    //調整軀幹
    glRotatef(theta[21], 0.0, 1.0, 0.0);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    /**/torso();

    //調整頭
    glPushMatrix();
    glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    glRotatef(theta[24], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    /**/head();
    glPopMatrix();

    //調整左手臂
    glPushMatrix();
    glRotatef(mot[1], 0.0, 1.0, 0.0);
    glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(120-mot[1], 1.0, 0.0, 0.0);
    glRotatef(theta[3], 1.0, 0.0, 0.0);
    glRotatef(theta[11], 0.0, 0.0, 1.0);
    if(motion == dance1 || motion == dance2){
        glRotatef(theta[14]+90, 1.0, 0.0, 0.0);
        glRotatef(theta[15]+90, 0.0, 0.0, 1.0);
    }
    /**/left_upper_arm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    glRotatef(theta[12], 0.0, 0.0, -1.0);
    glRotatef(theta[16], 0.0, 0.0, 1.0);
    glRotatef(theta[22], 0.0, 0.0, 1.0);
    /**/left_lower_arm();
    glPopMatrix();


    //調整右手臂
    glPushMatrix();
    glRotatef(mot[1], 0.0, 1.0, 0.0);
    glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(120-mot[1], 1.0, 0.0, 0.0);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    glRotatef(theta[11], 0.0, 0.0, -1.0);
    glRotatef(theta[29], 0.0, 0.0, 1.0);
    if(motion == dance1 || motion == dance2){
        glRotatef(theta[14]+90, -1.0, 0.0, 0.0);
        glRotatef(theta[15]+90, 0.0, 0.0, -1.0);
    }
    /**/right_upper_arm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    glRotatef(theta[12], 0.0, 0.0, 1.0);
    glRotatef(theta[16], 0.0, 0.0, 1.0);
    glRotatef(theta[23], 0.0, 0.0, -1.0);
    /**/right_lower_arm();
    glPopMatrix();


    //調整左腳
    glPushMatrix();
    glTranslatef(-(UPPER_LEG_RADIUS+1), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7]+180, 1.0, 0.0, 0.0);
    glRotatef(theta[11], 0.0, 0.0, 1.0);
    glRotatef(theta[17], 0.0, 0.0, 1.0);
    glRotatef(theta[25], 0.0, 0.0, 1.0);
    /**/left_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    glRotatef(theta[18], 0.0, 0.0, 1.0);
    glRotatef(theta[28], 0.0, 0.0, -1.0);
    /**/left_lower_leg();
    glPopMatrix();


    //調整右腳
    glPushMatrix();
    glTranslatef(UPPER_LEG_RADIUS+1, 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9]+180, 1.0, 0.0, 0.0);
    glRotatef(theta[11], 0.0, 0.0, -1.0);
    glRotatef(theta[17], 0.0, 0.0, 1.0);
    glRotatef(theta[26], 0.0, 0.0, -1.0);
    /**/right_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    glRotatef(theta[18], 0.0, 0.0, 1.0);
    glRotatef(theta[27], 0.0, 0.0, 1.0);
    right_lower_leg();
    /**/glPopMatrix();

    //繪製
    glFlush();
    glutSwapBuffers();
}



void mouse(int btn, int state, int x, int y)
{
    //調整特定軀幹的角度
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] += 5.0;
        if( theta[angle] > 360.0 )
            theta[angle] -= 360.0;
    }
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] -= 5.0;
        if( theta[angle] < 360.0 )
            theta[angle] += 360.0;
    }
    display();
}

//主選單
void menu(int id)
{
    if(id ==1 )
    {
        motion = none;
        reset();
    }
    else if(id == 2){
        exit(0);
    }
}

//控制選單
void control_menu(int id){
    angle = id;
}


//動作選單
void motion_menu(int id){
    reset();
    motion = id;
}

//讀取鍵盤輸入改變身體角度
void keyboardInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        baseRotate[0] += 5.0;
        if (baseRotate[0] > 360.0){
            baseRotate[0] -= 360.0;
        }
        display();
        break;
    case 's':
        baseRotate[0] -= 5.0;
        if (baseRotate[0] < 0){
            baseRotate[0] += 360.0;
        }
        display();
        break;
    case 'd':
        baseRotate[1] += 5.0;
        if (baseRotate[1] > 360.0){
            baseRotate[1] -= 360.0;
        }
        display();
        break;
    case 'a':
        baseRotate[1] -= 5.0;
        if (baseRotate[1] < 0){
            baseRotate[1] += 360.0;
        }
        display();
        break;
    default:
        break;
    }
}

//用鍵盤的方向鍵控制身體的位置
void SpKeyboardInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        basePos[0] += 0.5;
        display();
        break;
    case GLUT_KEY_LEFT:
        basePos[0] -= 0.5;
        display();
        break;
    case GLUT_KEY_UP:
        basePos[1] += 0.5;
        display();
        break;
    case GLUT_KEY_DOWN:
        basePos[1] -= 0.5;
        display();
        break;
    default:
        break;
    }
}

void myReshape(int w, int h)
    {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
                10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
                10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess = { 100.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    //設兩個光源
    GLfloat light_position1[] = { 10.0, 20.0, 15.0, 0.0 };
    GLfloat light_position2[] = { -10.0, 20.0, 15.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);

    //new 2次曲面的物件
    h=gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    lua=gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    lla=gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    rua=gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    rla=gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    lul=gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lll=gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    rul=gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    rll=gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    h1=gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
}

//初始化所有參數
void reset(){
    baseRotate[0]=0;
    baseRotate[1]=0;
    baseRotate[2]=0;
    basePos[0] = 0;
    basePos[1] = -5;
    basePos[2] = -5;
    dance_state = 0;
    bye_state = 0;
    walk_state = 0;
    for(int i=0;i<3;i++){
        mot[i]=0;
    }
    fan_size = 5;
    for(int i=0;i<=29;i++){
        theta[i]=0;
    }
    for(int i=0;i<=40;i++){
        step[i]=init_step[i];
    }
}

//比較兩個浮點數是否相等
bool que(double a,double b){
    return fabs(a-b)<=1e-6;
}

//round theta變數變成step的倍數
GLfloat rou(GLfloat the,int ste){
    if((GLint)the%ste!=0){
        return (GLint)((GLint)the/ste)*ste;
    }
    else{
        return the;
    }
}

//如果theta超過範圍就改變step的正負號
GLfloat sign(GLfloat the,int ste,int left,int right){
    if (que(the,left) || que(the,right)){
        return -ste;
    }
    else{
        return ste;
    }
}

//如果theta在範圍內就加step
GLfloat plu(GLfloat the,int ste,int left,int right){
    if (the <= left && the >= right){
        the += ste;
    }
    return the;
}

//用指標改變變數內容
void change(GLfloat* the,int* ste,int left,int right){
    *the = rou(*the,*ste);
    *the = plu(*the,*ste,left,right);
    *ste = sign(*the,*ste,left,right);
}

//隨時間與動作改變參數
void TimerFunction(int value){
    if(motion != value){
        reset();
    }
    //電風扇
    else if(value == motion_1){
        mot[1] = 30;
        fan_size = 10;
        mot[0] += 20;
        if(mot[0]>=360) mot[0] = 0;
    }
    //蘿蔔蹲
    else if(value == motion_2){
        change(&theta[3],&step[0],60,0);
        change(&theta[5],&step[1],60,0);
        change(&theta[7],&step[2],4,-56);
        change(&theta[8],&step[3],60,0);
        change(&theta[9],&step[4],4,-56);
        change(&theta[10],&step[5],60,0);
    }
    //走路
    else if(value == motion_3){
        if(walk_state){
            change(&theta[3],&step[6],80,0);
            change(&theta[9],&step[9],40,0);
            change(&theta[10],&step[11],20,0);
            change(&theta[4],&step[12],10,-30);
            if(que(theta[9],0)){
                walk_state = 0;
            }
        }
        else{
            change(&theta[5],&step[7],80,0);
            change(&theta[7],&step[8],40,0);
            change(&theta[8],&step[10],20,0);
            change(&theta[6],&step[13],10,-30);
            if(que(theta[7],0)){
                walk_state = 1;
            }
        }
    }
    //開合跳
    else if(value == motion_4){
        theta[3] = -120;
        theta[5] = -120;
        change(&theta[11],&step[14],24,-24);
        change(&theta[12],&step[15],24,0);
        change(&theta[13],&step[16],24,0);
        change(&theta[10],&step[17],24,0);
        change(&theta[8],&step[18],24,0);
    }
    //說再見
    else if(value == motion_5){
        if(bye_state == 0){
            change(&theta[5],&step[37],4,-100);
            cnt = 0;
            if(theta[5] == -100){
                bye_state = 1;
            }
        }
        else if(bye_state == 1){
            change(&theta[29],&step[38],40,-40);
            if(theta[29]==40){
                cnt++;
            }
            if(cnt==3){
                bye_state = 2;
            }
        }
        else if(bye_state == 2){
            basePos[1]+=0.5;
            basePos[0]-=0.2;
            baseRotate[2]+=5;
            baseRotate[3]+=5;
        }
    }
    //跳舞1
    else if(value == dance1){
        change(&theta[14],&step[19],20,-20);
        change(&theta[15],&step[20],20,-20);
        change(&theta[16],&step[21],20,-20);
        change(&theta[17],&step[22],20,-20);
        change(&theta[18],&step[23],20,-20);
        change(&theta[19],&step[24],20,-20);
        change(&theta[20],&step[25],20,-20);
        change(&theta[21],&step[26],20,-20);
    }
    //跳舞2
    else if(value == dance2){
        if(dance_state==0){
            change(&theta[22],&step[27],90,-10);
            change(&theta[23],&step[28],90,-10);
            change(&theta[24],&step[31],90,-10);
            change(&theta[25],&step[33],36,0);
            change(&theta[27],&step[35],36,0);
            if(theta[22]==-10){
                dance_state=1;
            }
        }
        else if(dance_state==1){
            change(&theta[22],&step[29],10,-90);
            change(&theta[23],&step[30],10,-90);
            change(&theta[24],&step[32],10,-90);
            change(&theta[26],&step[34],36,0);
            change(&theta[28],&step[36],36,0);
            if(theta[22]==10){
                dance_state=0;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(50, TimerFunction, motion);
}
int main(int argc, char **argv)
{
    int middle_menu,con_menu,mot_menu;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("robot");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    //控制
    con_menu = glutCreateMenu(control_menu);
    glutAddMenuEntry("torso", 0);
    glutAddMenuEntry("head1", 1);
    glutAddMenuEntry("head2", 2);
    glutAddMenuEntry("right_upper_arm", 3);
    glutAddMenuEntry("right_lower_arm", 4);
    glutAddMenuEntry("left_upper_arm", 5);
    glutAddMenuEntry("left_lower_arm", 6);
    glutAddMenuEntry("right_upper_leg", 7);
    glutAddMenuEntry("right_lower_leg", 8);
    glutAddMenuEntry("left_upper_leg", 9);
    glutAddMenuEntry("left_lower_leg", 10);

    //動作選單
    mot_menu = glutCreateMenu(motion_menu);
    glutAddMenuEntry("fan", 1);
    glutAddMenuEntry("squat", 2);
    glutAddMenuEntry("walk", 3);
    glutAddMenuEntry("jump", 4);
    glutAddMenuEntry("bye bye", 5);
    glutAddMenuEntry("dance1", 6);
    glutAddMenuEntry("dance2", 7);

    //主選單
    middle_menu = glutCreateMenu(menu);
    glutAddSubMenu("control", con_menu);
    glutAddSubMenu("motion", mot_menu);
    glutAddMenuEntry("reset", 1);
    glutAddMenuEntry("quit", 2);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);


    //鍵盤輸入
    glutKeyboardFunc(keyboardInput);
    glutSpecialFunc(SpKeyboardInput);

    //動作
    glutTimerFunc(50,TimerFunction,motion);
    glutMainLoop();
}
