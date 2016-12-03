// Dungeon Simulator 2016.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const unsigned char* lostMessage = "You`ve died";
GLfloat mouseX = 0, mouseY = 0;
float mouseSensitivity = 0.01f;

bool keystate[255];
bool buttonState[3];

GLuint andrzejTex;
std::vector<GLuint> hands;
std::vector<GLuint> andrzej;
Scene scene;

GLuint LoadTexture(char * file, int magFilter, int minFilter) {

    // Odczytanie bitmapy
    Bitmap *tex = new Bitmap();
    if (!tex->loadBMP(file)) {
        printf("ERROR: Cannot read texture file \"%s\".\n", file);
        return -1;
    }

    // Utworzenie nowego id wolnej tekstury
    GLuint texId;
    glGenTextures(1, &texId);

    // "Bindowanie" tekstury o nowoutworzonym id
    glBindTexture(GL_TEXTURE_2D, texId);

    // Okreœlenie parametrów filtracji dla tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); // Filtracja, gdy tekstura jest powiêkszana
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter); // Filtracja, gdy tekstura jest pomniejszana

    // Wys³anie tekstury do pamiêci karty graficznej zale¿nie od tego, czy chcemy korzystaæ z mipmap czy nie
    if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
        // Automatyczne zbudowanie mipmap i wys³anie tekstury do pamiêci karty graficznej
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex->width, tex->height, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    }
    else {
        // Wys³anie tekstury do pamiêci karty graficznej 
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    }

    // Zwolnienie pamiêci, usuniêcie bitmapy z pamiêci - bitmapa jest ju¿ w pamiêci karty graficznej
    delete tex;

    // Zwrócenie id tekstury
    return texId;
}

int main(int argc, char* argv[]){
#pragma region Initialize
    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1920, 1080);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glutCreateWindow("TOM");
    glutFullScreen();

    glutDisplayFunc(onRender);
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyUp);
    //glutTimerFunc(17, onTimer, 0);
    glutPassiveMotionFunc(onMouseMove);
    glutMouseFunc(onButtonPress);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_FOG);

#pragma endregion

#pragma region Lights Initialize
    float gl_amb[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
#pragma endregion

#pragma region Mouse Initialize
    glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
    mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    glutSetCursor(GLUT_CURSOR_NONE);
#pragma endregion


    scene.initialize();

    scene.enemies.push_back(new Enemy(6, 1, 2, 0.0, 0.0));
    scene.enemies.push_back(new Enemy(6, 2, 2, 0.0, 0.0));
    scene.map->print();
    scene.player->loadAnimation();
    for (auto enemy : scene.enemies){
        enemy->initialize();
        std::cout << enemy->getAnimLenght() << std::endl;
    }

    glutMainLoop();

    return 0;
}

void onKeyPress(unsigned char key, int x, int y) {
    if (!keystate[key]) {
        keystate[key] = true;
        onKeyDown(key, x, y);
    }
}

void onKeyDown(unsigned char key, int x, int y) {
    if (key == 27) {
        glutLeaveMainLoop();
    }

    scene.player->gridDir_ = scene.player->gridDir_ % 4;

#pragma region Move

    switch (scene.player->gridDir_){
    case 0:
        if (keystate['w']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] + 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['s']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] - 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['a']){
            if (scene.map->map_[scene.player->gridPos_[0] - 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['d']){
            if (scene.map->map_[scene.player->gridPos_[0] + 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        break;

        // Retarded but working part          
    case 1:
        if (keystate['w']){
            if (scene.map->map_[scene.player->gridPos_[0] + 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['s']){
            if (scene.map->map_[scene.player->gridPos_[0] - 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['a']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] + 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['d']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] - 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        break;
    case 2:
        if (keystate['w']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] - 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['s']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] + 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['a']){
            if (scene.map->map_[scene.player->gridPos_[0] + 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['d']){
            if (scene.map->map_[scene.player->gridPos_[0] - 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        break;
    case 3:
        if (keystate['w']){
            if (scene.map->map_[scene.player->gridPos_[0] - 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['s']){
            if (scene.map->map_[scene.player->gridPos_[0] + 1][scene.player->gridPos_[1]] == '.'){
                scene.player->pos_.setZ(scene.player->pos_.getZ() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[0] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['a']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] - 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() - GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] -= 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }
        if (keystate['d']){
            if (scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1] + 1] == '.'){
                scene.player->pos_.setX(scene.player->pos_.getX() + GRID);
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '.';
                scene.player->gridPos_[1] += 1;
                scene.map->map_[scene.player->gridPos_[0]][scene.player->gridPos_[1]] = '@';
            }
        }

    }
#pragma endregion

    if (keystate['q']){
        scene.player->gridDir_ += 3;
    }
    if (keystate['e']){
        scene.player->gridDir_ += 1;


    }

    if (key == 'f'){
        scene.player->interact();
    }

}


void onKeyUp(unsigned char key, int x, int y) {
    keystate[key] = false;
}

void onMouseMove(int x, int y) {
    mouseX = x;
    mouseY = y;
}

bool isAnimationChanged = false;
void onButtonPress(int button, int button_state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN && !scene.player->getIsBlocking() && !scene.player->getIsAttacking()){
        scene.player->attack();
    }
    if (button == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN && !scene.player->getIsAttacking() && !scene.player->getIsBlocking()){
        scene.player->changeIsBlocking();
        isAnimationChanged = true;
    }
}

//void onTimer(int id) {
//    glutTimerFunc(17, onTimer, 0);
//
//}

void onRender(){
    if (!scene.player->isDead()){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(
            scene.player->pos_.getX(), scene.player->pos_.getY(), scene.player->pos_.getZ(),
            scene.player->pos_.getX() + scene.player->dir_.getX(), scene.player->pos_.getY() + scene.player->dir_.getY(), scene.player->pos_.getZ() + scene.player->dir_.getZ(),
            0.0f, 1.0f, 0.0f
            );

        scene.player->render();

        // Attack animation
        if (scene.player->getIsAttacking()){
            ++scene.player->animationFrame_;
            if (scene.player->animationFrame_ == scene.player->getAttackLenght()){
                scene.player->animationFrame_ = 0;
                scene.player->changeIsAttacking();
            }
        }
        // Blocking Animation
        if (scene.player->getIsBlocking()){
            if (isAnimationChanged){
                scene.player->animationFrame_ = scene.player->getAttackLenght();
                isAnimationChanged = false;
            }
            ++scene.player->animationFrame_;
            if (scene.player->animationFrame_ == scene.player->getBlockLenght() + scene.player->getAttackLenght()){
                scene.player->animationFrame_ = 0;
                scene.player->changeIsBlocking();
            }
        }

        GLfloat fogColor[] = { 0.48f, 0.14f, 0.0f, 1 };
        glFogfv(GL_FOG_COLOR, fogColor);
        glFogi(GL_FOG_MODE, GL_LINEAR);
        glFogf(GL_FOG_START, 7.0f);
        glFogf(GL_FOG_END, 20.0f);

        // Game world rotation
        glPushMatrix();
        glTranslatef(scene.player->pos_.getX(), 0.0f, scene.player->pos_.getZ());
        glRotatef(scene.player->gridDir_ * 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(-scene.player->pos_.getX(), 0.0f, -scene.player->pos_.getZ());

        for (auto object : scene.environment){
            object->render();
        }

        int i = 0;
        for (auto enemy : scene.enemies){
            /*if ((enemy->attackDelay_ >= 120) && !enemy->isDead()){
                enemy->attackDelay_ = 0;
                }*/

            if (enemy->getIsAttacking()){
                ++enemy->animationFrame_;
                if (enemy->animationFrame_ == 119 && enemy->getForwardSymbol() == '@'){
                    scene.player->takeDamage(enemy->getDamage());
                    std::cout << scene.player->getHealth() << std::endl;
                }
                if (enemy->animationFrame_ == enemy->getAttackLenght()){
                    enemy->changeIsAttacking();
                    enemy->animationFrame_ = 0;
                }
            }
            else if (enemy->isDead()){
                ++enemy->animationFrame_;
                std::cout << enemy->animationFrame_ << std::endl;
                if (enemy->animationFrame_ == enemy->getAnimLenght() - 1){
                    //std::cout << "dead" << std::endl;
                    scene.enemies.erase(scene.enemies.begin() + i);
                    --i;
                    scene.map->map_[enemy->gridPos_[0]][enemy->gridPos_[1]] = '.';
                    break;
                }
            }
            else{
                if (enemy->getForwardSymbol() == '@'){
                    enemy->attack();
                }
            }

            /*if (!enemy->isDead()){
                ++enemy->attackDelay_;
                }*/
            enemy->render();
            if (enemy->moveDelay_ == 60 && !enemy->isDead()){
                enemy->moveDelay_ = 0;
                if (!enemy->getIsAttacking()){
                    enemy->move(scene.player);
                }
            }
            ++enemy->moveDelay_;
            ++i;
        }

        // ****************************************************************************************

#pragma region HUD
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, 1920, 1080, 0.0, -1.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_CULL_FACE);

        glClear(GL_DEPTH_BUFFER_BIT);

        glColor3f(0.8627f, 0.0784f, 0.2352f);
        glBegin(GL_QUADS);
        glVertex2f(30.0, 950.0);
        glVertex2f(33 * scene.player->getHealth(), 950.0);
        glVertex2f(33 * scene.player->getHealth(), 975.0);
        glVertex2f(30.0, 975.0);
        glEnd();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
#pragma endregion

        glPopMatrix();
        glutSwapBuffers();
        glFlush();
        glutPostRedisplay();
    }
    else{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, reinterpret_cast<const unsigned char*>(lostMessage));
        glutSwapBuffers();
        glFlush();
        glutPostRedisplay();
    }
}
void onReshape(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    gluPerspective(50.0f, (float)width / height, .01f, 100.0f);
}

GLuint LoadObj(std::string fileName) {
    char* file = const_cast<char*>(fileName.c_str());

    FILE * fp = fopen(file, "r");

    if (fp == NULL) {
        printf("ERROR: Cannot read model file \"%s\".\n", file);
        return -1;
    }

    std::vector<vec3> * v = new std::vector<vec3>();
    std::vector<vec3> * n = new std::vector<vec3>();
    std::vector<vec3> * t = new std::vector<vec3>();
    std::vector<SFace> * f = new std::vector<SFace>();

    char buf[128];

    while (fgets(buf, 128, fp) != NULL) {
        if (buf[0] == 'v' && buf[1] == ' ') {
            vec3 * vertex = new vec3();
            sscanf(buf, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
            v->push_back(*vertex);
        }
        if (buf[0] == 'v' && buf[1] == 't') {
            vec3 * vertex = new vec3();
            sscanf(buf, "vt %f %f", &vertex->x, &vertex->y);
            t->push_back(*vertex);
        }
        if (buf[0] == 'v' && buf[1] == 'n') {
            vec3 * vertex = new vec3();
            sscanf(buf, "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
            n->push_back(*vertex);
        }
        if (buf[0] == 'f' && buf[1] == ' ') {
            SFace * face = new SFace();
            sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &face->v[0], &face->t[0], &face->n[0],
                &face->v[1], &face->t[1], &face->n[1],
                &face->v[2], &face->t[2], &face->n[2]
                );
            f->push_back(*face);
        }
    }

    fclose(fp);

    GLuint dlId;
    dlId = glGenLists(1);
    glNewList(dlId, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < f->size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            vec3 * cv = &(*v)[((*f)[i].v[j] - 1)];
            vec3 * ct = &(*t)[((*f)[i].t[j] - 1)];
            vec3 * cn = &(*n)[((*f)[i].n[j] - 1)];
            glTexCoord2f(ct->x, ct->y);
            glNormal3f(cn->x, cn->y, cn->z);
            glVertex3f(cv->x, cv->y, cv->z);
        }
    }
    glEnd();
    glEndList();

    delete v;
    delete n;
    delete t;
    delete f;

    return dlId;
}