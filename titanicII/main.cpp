#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>

void display();
void reshape(int w, int h);
void OnMouseClick(int button, int state, int x, int y);
void SpecialInput(int key, int x, int y);
void keyboard(unsigned char Key, int x, int y);
void timer(int);

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,200);
    glutInitWindowSize(1200,600);
    glutCreateWindow("211001120 Ahmad Fakher  211002622 Ziad Said");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(OnMouseClick);

    glutTimerFunc(0,timer,0);
    glutSpecialFunc(SpecialInput);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    glutMainLoop();
}



static float elapsedTime = 0; // Variable to keep track of elapsed time

//rotate angle
float rangle = 0.0;

//increment in x
float ax = 0.0;

//increment in y
float ay = 0.0;

// Lights Variable
bool lightOn = true;

//mouse click function to move ship left or right
void OnMouseClick(int button, int state, int x, int y){

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){if(ax<28){ax++;}}

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){if(ax<28){ax--;}}

}


void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            if(ay<1 && ax<28){ay+=0.1;}
        break;

        case GLUT_KEY_DOWN:
            if(ay>-1 && ax<28){ay-=0.1;}
        break;

        case GLUT_KEY_LEFT:
            if(ax<28){ax-=0.2;}
        break;

        case GLUT_KEY_RIGHT:
            if(ax<28){ax+=0.2;}
        break;
    }
}

bool fullScreen;

void keyboard(unsigned char key,int x,int y)
{
    switch (key)
    {
        case 'd' : if(ax<28){ax+=0.2;}
        break;

        case 'a' : if(ax<28){ax-=0.2;}
        break;

        case 'w' : if(ay<1 && ax<28){ay+=0.1;}
        break;

        case 's' : if(ay>-1 && ax<28){ay-=0.1;}
        break;

        case 'f': fullScreen = !fullScreen;
        if (fullScreen)
        {
            glutFullScreen();
        }
        else
        {
            glutReshapeWindow(1200, 600);
            glutPositionWindow(200,200);
        }
        break;

        case 'l' : lightOn = !lightOn;
        break;

        case 'r' : ax = 0;
        ay = 0;
        break;

        case 27 : exit(0);
        break;
    }
}

//radius beam
float radius2 = 6;

typedef struct {
    float x, y;   // Position
    float vx, vy; // Velocity
    float life;   // Life
} Particle;

#define MAX_PARTICLES 100
Particle particles[MAX_PARTICLES];

void InitParticles() {
    for(int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = 10.5 + ax; // Starting x position based on ship position
        particles[i].y = 40 + ay; // Starting y position based on ship position
        particles[i].vx = (rand() % 10 - 5) / 100.0; // Random x velocity
        particles[i].vy = (rand() % 10 + 20) / 100.0; // Random y velocity
        particles[i].life = rand() % 100 / 10.0; // Random life
    }
}

void UpdateParticles() {
    for(int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;

        // Increase the vertical velocity a bit to simulate rising
        particles[i].vy += 0.01;

        // Reduce the life of the particle
        particles[i].life -= 0.02;

        if (particles[i].life <= 0) {
            particles[i].x = 10.5 + ax;
            particles[i].y = 40 + ay;
            particles[i].vx = (rand() % 20 - 10) / 100.0; // Wider range for x velocity
            particles[i].vy = (rand() % 10 + 20) / 100.0; // Random y velocity
            particles[i].life = rand() % 100 / 10.0 + 1.0; // Longer life
        }
    }
}




bool renderParticles = true;

void RenderParticles() {
    if (!renderParticles) {
        return; // If renderParticles is false, don't draw anything
    }

    float particle_size = 0.7; // Scale Smoke Particles
    for(int i = 0; i < MAX_PARTICLES; i++) {
        if(particles[i].life > 0) {
            // Decrease alpha as the particle's life decreases
            float alpha = particles[i].life / 2;
            glColor4f(0.5, 0.5, 0.5, alpha); // Smoke color with alpha

            // Draw larger quads for the smoke particles
            glBegin(GL_QUADS);
            glVertex2f(particles[i].x - particle_size / 2, particles[i].y - particle_size / 2);
            glVertex2f(particles[i].x + particle_size / 2, particles[i].y - particle_size / 2);
            glVertex2f(particles[i].x + particle_size / 2, particles[i].y + particle_size / 2);
            glVertex2f(particles[i].x - particle_size / 2, particles[i].y + particle_size / 2);
            glEnd();
        }
    }
}

void drawWindow(float x, float y, bool lightOn) {
    // Set the color based on whether the light is on or off
    if (lightOn) {
        glColor3f(1.0f, 0.9f, 0.4f); // Light yellow for lights on
    } else {
        glColor3f(0.1f, 0.1f, 0.1f); // Dark for lights off
    }

    // Draw the window as a small square
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1.0f, y);
    glVertex2f(x + 1.0f, y + 1.0f);
    glVertex2f(x, y + 1.0f);
    glEnd();
}

void display() {

    glClearColor(0.09803921568627451,0.20392156862745098,0.3686274509803922,0); //loon elsama
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //sea behind ship

    glColor3f(0.26666666666666666, 0.4823529411764706, 0.7137254901960784);
    glBegin(GL_QUADS);
    glVertex2f(0,15);
    glVertex2f(0,12);
    glVertex2f(100,12);
    glVertex2f(100,15);
    glEnd();

    glColor3f(0.26666666666666666, 0.5333333333333333, 0.792156862745098);
    glBegin(GL_TRIANGLES);
    glVertex2f(100,13);
    glVertex2f(100,12);
    glVertex2f(40,13);
    glEnd();

    //moon beam

    int j;
    double angle1;
    glBegin(GL_POLYGON);
    glColor4f(0.9333333333333333,0.9176470588235294,0.9176470588235294, 0.1);
    for(j = 0; j <= 360; j++) {
    angle1 = j * 3.14 / 180;
    glVertex2f(92.5+radius2 * cos(angle1), 42+radius2 * sin(angle1));
    }
    glEnd();

    //moon

    int i;
    double radius1 = 5;
    double angle;
    glBegin(GL_POLYGON);
    glColor3f(0.9333333333333333,0.9176470588235294,0.9176470588235294);
    for(i = 0; i <= 360; i++) {
    angle = i * 3.14 / 180;
    glVertex2f(92.5+radius1 * cos(angle), 42+radius1 * sin(angle));
    }
    glEnd();

    //stars

    glColor3f(0.9333333333333333,0.9176470588235294,0.9176470588235294);
    glBegin(GL_POINTS);
    glVertex2f(5.1,43.2);
    glVertex2f(1.5,41);
    glVertex2f(5.7,36.5);
    glVertex2f(7.2,29.2);
    glVertex2f(4.8,24.8);
    glVertex2f(12.9,42);
    glVertex2f(21.1,43.2);
    glVertex2f(24.4,44.2);
    glVertex2f(34.7,44.3);
    glVertex2f(31.7,41.3);
    glVertex2f(41.4,43.0);
    glVertex2f(40,40);
    glVertex2f(44.2,38.4);
    glVertex2f(42.6,33.4);
    glVertex2f(46.6,34.5);
    glVertex2f(41.7,29.2);
    glVertex2f(38.6,34.8);
    glVertex2f(47.6,28);
    glVertex2f(51.4,23.6);
    glVertex2f(57,27.1);
    glVertex2f(62.1,30.3);
    glVertex2f(60.9,43.5);
    glVertex2f(55.6,40.5);
    glVertex2f(58.5,39.7);
    glVertex2f(60.7,36.9);
    glVertex2f(65.1,39.5);
    glVertex2f(70.1,44.5);
    glVertex2f(77.4,42.3);
    glVertex2f(78.5,36.2);
    glVertex2f(80.4,32.6);
    glVertex2f(85.1,28.2);
    glVertex2f(72.5,29.8);
    glVertex2f(76.3,25.1);
    glVertex2f(69.3,25);
    glVertex2f(73.5,38.5);
    glEnd();

    //ship

    //base
    glColor3f(0.6627450980392157, 0.3568627450980392, 0.47843137254901963);

    //rotation initializing

    if (ax >= 28) {
    glPushMatrix();
    glTranslatef(ax,0,0);
    glRotatef(rangle,0,0,1);
    glTranslatef(-ax, 0, 0);
    }

    //drawing cont.

    glBegin(GL_QUADS);
    glVertex2f(64 + ax,14 + ay);
    glVertex2f(64 + ax,12 + ay);
    glColor3f(0.3764705882352941, 0.23921568627450981, 0.3176470588235294);
    glVertex2f(8 + ax,12 + ay);
    glVertex2f(8 + ax,14 + ay);
    glEnd();

    //main body
    glColor3f(0.13725490196078433, 0.21176470588235294, 0.3058823529411765);
    glBegin(GL_QUADS);
    glVertex2f(67 + ax,20 + ay);
    glVertex2f(64 + ax,14 + ay);
    glColor3f(0.0784313725490196, 0.12549019607843137, 0.19607843137254902);
    glVertex2f(8 + ax,14 + ay);
    glVertex2f(3 + ax,20 + ay);
    glEnd();

    glColor3f(0.6274509803921569, 0.35294117647058826, 0.4588235294117647);
    glBegin(GL_QUADS);
    glVertex2f(68 + ax,21.5 + ay);
    glVertex2f(67 + ax,20 + ay);
    glColor3f(0.3764705882352941, 0.23529411764705882, 0.3333333333333333);
    glVertex2f(3 + ax,20 + ay);
    glVertex2f(1.5 + ax,21.5 + ay);
    glEnd();


    //roof
    glColor3f(0.4823529411764706, 0.5568627450980392, 0.5882352941176471);
    glBegin(GL_QUADS);
    glVertex2f(48.5 + ax,26 + ay);
    glVertex2f(48.5 + ax,21.5 + ay);
    glColor3f(0.4, 0.49411764705882355, 0.5411764705882353);
    glVertex2f(8 + ax,21.5 + ay);
    glVertex2f(8 + ax,26 + ay);
    glEnd();

    glColor3f(0.1411764705882353, 0.2235294117647059, 0.35294117647058826);
    glBegin(GL_QUADS);
    glVertex2f(48.5 + ax,26.5 + ay);
    glVertex2f(48.5 + ax,26 + ay);
    glColor3f(0.0784313725490196, 0.13725490196078433, 0.21176470588235294);
    glVertex2f(8 + ax,26 + ay);
    glVertex2f(8 + ax,26.5 + ay);
    glEnd();



    //chimneys

    //chimney 1

    //part 1
    glColor3f(0.2980392156862745, 0.3568627450980392, 0.47058823529411764);
    glBegin(GL_QUADS);
    glVertex2f(13 + ax,36 + ay);
    glVertex2f(13 + ax,26.5 + ay);
    glColor3f(0.10980392156862745, 0.1411764705882353, 0.21568627450980393);
    glVertex2f(8 + ax,26.5 + ay);
    glVertex2f(8 + ax,36 + ay);
    glEnd();

    //part 2
    glColor3f(0.6980392156862745, 0.6, 0.4470588235294118);
    glBegin(GL_QUADS);
    glVertex2f(13 + ax,40 + ay);
    glVertex2f(13 + ax,36 + ay);
    glColor3f(0.48627450980392156, 0.34901960784313724, 0.26666666666666666);
    glVertex2f(8 + ax,36 + ay);
    glVertex2f(8 + ax,40 + ay);
    glEnd();

    //chimney 2

    //part 1
    glColor3f(0.2980392156862745, 0.3568627450980392, 0.47058823529411764);
    glBegin(GL_QUADS);
    glVertex2f(21 + ax,36 + ay);
    glVertex2f(21 + ax,26.5 + ay);
    glColor3f(0.10980392156862745, 0.1411764705882353, 0.21568627450980393);
    glVertex2f(16 + ax,26.5 + ay);
    glVertex2f(16 + ax,36 + ay);
    glEnd();

    //part 2
    glColor3f(0.6980392156862745, 0.6, 0.4470588235294118);
    glBegin(GL_QUADS);
    glVertex2f(21 + ax,40 + ay);
    glVertex2f(21 + ax,36 + ay);
    glColor3f(0.48627450980392156, 0.34901960784313724, 0.26666666666666666);
    glVertex2f(16 + ax,36 + ay);
    glVertex2f(16 + ax,40 + ay);
    glEnd();

    //chimney 3

    //part 1
    glColor3f(0.2980392156862745, 0.3568627450980392, 0.47058823529411764);
    glBegin(GL_QUADS);
    glVertex2f(29 + ax,36 + ay);
    glVertex2f(29 + ax,26.5 + ay);
    glColor3f(0.10980392156862745, 0.1411764705882353, 0.21568627450980393);
    glVertex2f(24 + ax,26.5 + ay);
    glVertex2f(24 + ax,36 + ay);
    glEnd();

    //part 2
    glColor3f(0.6980392156862745, 0.6, 0.4470588235294118);
    glBegin(GL_QUADS);
    glVertex2f(29 + ax,40 + ay);
    glVertex2f(29 + ax,36 + ay);
    glColor3f(0.48627450980392156, 0.34901960784313724, 0.26666666666666666);
    glVertex2f(24 + ax,36 + ay);
    glVertex2f(24 + ax,40 + ay);
    glEnd();

    //chimney 4

    //part 1
    glColor3f(0.2980392156862745, 0.3568627450980392, 0.47058823529411764);
    glBegin(GL_QUADS);
    glVertex2f(37 + ax,36 + ay);
    glVertex2f(37 + ax,26.5 + ay);
    glColor3f(0.10980392156862745, 0.1411764705882353, 0.21568627450980393);
    glVertex2f(32 + ax,26.5 + ay);
    glVertex2f(32 + ax,36 + ay);
    glEnd();

    //part 2
    glColor3f(0.6980392156862745, 0.6, 0.4470588235294118);
    glBegin(GL_QUADS);
    glVertex2f(37 + ax,40 + ay);
    glVertex2f(37 + ax,36 + ay);
    glColor3f(0.48627450980392156, 0.34901960784313724, 0.26666666666666666);
    glVertex2f(32 + ax,36 + ay);
    glVertex2f(32 + ax,40 + ay);
    glEnd();


    for (float yPos = 16.0f; yPos < 20.0f; yPos += 2.0f) {
        for (float xPos = 10.0f; xPos < 60.0f; xPos += 3.0f) {
            drawWindow(xPos + ax, yPos + ay, lightOn);
            lightOn = !lightOn; // Alternate lights on and off
        }
    }
    glPopMatrix();


    //sea in front of ship

    glColor3f(0.20784313725490197, 0.4666666666666667, 0.615686274509804);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(0,12);
    glVertex2f(100,12);
    glVertex2f(100,0);
    glEnd();

    glColor3f(0.2235294117647059, 0.49019607843137253, 0.7019607843137254);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,9);
    glVertex2f(0,8);
    glVertex2f(25,8);
    glEnd();

    glColor3f(0.19215686274509805, 0.44313725490196076, 0.6274509803921569);
    glBegin(GL_TRIANGLES);
    glVertex2f(100,5);
    glVertex2f(100,6);
    glVertex2f(50,6);
    glEnd();

    glColor3f(0.13725490196078433, 0.3176470588235294, 0.41568627450980394);
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(0,4);
    glVertex2f(100,4);
    glVertex2f(100,0);
    glEnd();

    //large icebergs

    //iceberg 1

    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glBegin(GL_TRIANGLES);
    glVertex2f(0,18);
    glVertex2f(0,15);
    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glVertex2f(4.5,15);
    glEnd();

    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glBegin(GL_QUADS);
    glVertex2f(0,15);
    glVertex2f(0,10);
    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glVertex2f(8,10);
    glVertex2f(4.5,15);
    glEnd();

    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glBegin(GL_QUADS);
    glVertex2f(0,10);
    glVertex2f(0,6);
    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glVertex2f(8,6);
    glVertex2f(8,10);
    glEnd();

    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glBegin(GL_TRIANGLES);
    glVertex2f(8,10);
    glVertex2f(8,6);
    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glVertex2f(20,6);
    glEnd();

    //darker side

    glColor3f(0.5843137254901961, 0.7019607843137254, 0.7568627450980392);
    glBegin(GL_QUADS);
    glVertex2f(0,6);
    glVertex2f(0,5.5);
    glVertex2f(20,5.5);
    glVertex2f(20,6);
    glEnd();

    //iceberg 2

    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glBegin(GL_TRIANGLES);
    glVertex2f(100,17);
    glVertex2f(100,13);
    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glVertex2f(98,13);
    glEnd();

    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glBegin(GL_QUADS);
    glVertex2f(100,13);
    glVertex2f(100,9);
    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glVertex2f(92,9);
    glVertex2f(92,13);
    glEnd();

    glColor3f(0.7764705882352941, 0.8941176470588236, 0.9725490196078431);
    glBegin(GL_TRIANGLES);
    glVertex2f(92,13);
    glVertex2f(92,9);
    glColor3f(0.7215686274509804, 0.8627450980392157, 0.9137254901960784);
    glVertex2f(84,9);
    glEnd();

    //darker side

    glColor3f(0.5843137254901961, 0.7019607843137254, 0.7568627450980392);
    glBegin(GL_QUADS);
    glVertex2f(100,9);
    glVertex2f(100,8.5);
    glVertex2f(84,8.5);
    glVertex2f(84,9);
    glEnd();


    //small icebergs

    //small iceberg 1

    glColor3f(0.9098039215686274, 0.9647058823529412, 0.9764705882352941);
    glBegin(GL_QUADS);
    glVertex2f(19.65,7.75);
    glVertex2f(22.6,7.3);
    glVertex2f(24.2,5.6);
    glVertex2f(21.8,5.9);
    glEnd();

    glColor3f(0.9098039215686274, 0.9647058823529412, 0.9764705882352941);
    glBegin(GL_QUADS);
    glVertex2f(22.6,7.3);
    glVertex2f(24.2,5.6);
    glColor3f(0.9411764705882353, 0.9725490196078431, 0.984313725490196);
    glVertex2f(27,7);
    glVertex2f(25.8,8.85);
    glEnd();

    glColor3f(0.9411764705882353, 0.9725490196078431, 0.984313725490196);
    glBegin(GL_QUADS);
    glVertex2f(25.8,8.85);
    glVertex2f(27,7);
    glVertex2f(29.7,6.4);
    glVertex2f(28.3,8.1);
    glEnd();

    //darker side

    glColor3f(0.6196078431372549, 0.7176470588235294, 0.7686274509803922);
    glBegin(GL_QUADS);
    glVertex2f(19.65,7.75);
    glVertex2f(19.65,7.4);
    glVertex2f(21.8,5.55);
    glVertex2f(21.8,5.9);
    glEnd();

    glColor3f(0.7254901960784313, 0.8352941176470589, 0.8901960784313725);
    glBegin(GL_QUADS);
    glVertex2f(21.8,5.9);
    glVertex2f(21.8,5.55);
    glVertex2f(24.2,5.25);
    glVertex2f(24.2,5.6);
    glEnd();

    glColor3f(0.5843137254901961, 0.7019607843137254, 0.7568627450980392);
    glBegin(GL_QUADS);
    glVertex2f(24.2,5.6);
    glVertex2f(24.2,5.25);
    glVertex2f(27,6.65);
    glVertex2f(27,7);
    glEnd();


    glColor3f(0.6431372549019608, 0.7529411764705882, 0.796078431372549);
    glBegin(GL_QUADS);
    glVertex2f(27,7);
    glVertex2f(27,6.65);
    glVertex2f(29.7,6.05);
    glVertex2f(29.7,6.4);
    glEnd();

    //small iceberg 2

    glColor3f(0.9098039215686274, 0.9647058823529412, 0.9764705882352941);
    glBegin(GL_QUADS);
    glVertex2f(65.5,7.5);
    glVertex2f(69,8);
    glVertex2f(72,7);
    glVertex2f(68.5,6.5);
    glEnd();

    //darker side

    glColor3f(0.7294117647058823, 0.8549019607843137, 0.9137254901960784);
    glBegin(GL_QUADS);
    glVertex2f(65.5,7.5);
    glVertex2f(68.5,6.5);
    glVertex2f(68.5,6.15);
    glVertex2f(65.5,7.15);
    glEnd();

    glColor3f(0.3764705882352941, 0.48627450980392156, 0.5490196078431373);
    glBegin(GL_QUADS);
    glVertex2f(68.5,6.5);
    glVertex2f(68.5,6.15);
    glVertex2f(72,6.75);
    glVertex2f(72,7);
    glEnd();

    //small iceberg 3

    glColor3f(0.9098039215686274, 0.9647058823529412, 0.9764705882352941);
    glBegin(GL_QUADS);
    glVertex2f(50,4);
    glVertex2f(52.5,3.1);
    glVertex2f(55,4.1);
    glVertex2f(53.5,5.3);
    glEnd();

    //darker side

    glColor3f(0.5686274509803921, 0.6549019607843137, 0.6901960784313725);
    glBegin(GL_QUADS);
    glVertex2f(50,4);
    glVertex2f(50,3.75);
    glVertex2f(52.5,2.85);
    glVertex2f(52.5,3.1);
    glEnd();

    glColor3f(0.5333333333333333, 0.6274509803921569, 0.6666666666666666);
    glBegin(GL_QUADS);
    glVertex2f(52.5,3.1);
    glVertex2f(52.5,2.85);
    glVertex2f(55,3.85);
    glVertex2f(55,4.1);
    glEnd();
    RenderParticles();

    glFlush();

}

void reshape(int w, int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,50);
    glMatrixMode(GL_MODELVIEW);
}




int State = 1;
void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    // Update time
    elapsedTime += 1.0 / 60.0; // Increment by one frame

    // Update the ship's position and angle
    if (ax >= 28) {
        if (rangle > -20) {
            rangle -= 0.1;
        } else {
            // Increment ax and decrement ay once per frame until ay is <= -25
            if (ay > -25) {
                ax += 0.05;
                ay -= 0.05;
            } else {
                ax = 0;
                ay = 0;
                rangle = 0;
                elapsedTime = 0; // Reset elapsed time if the ship resets
            }
        }
    }

    // moon beam update
    switch (State) {
        case 1: {
            if (radius2 < 7) {
                radius2 += 0.01;
            } else {
                State = -1;
            }
            break;
        }
        case -1: {
            if (radius2 > 6) {
                radius2 -= 0.01;
            } else {
                State = 1;
            }
            break;
        }
    }

    // Update Particles until sinking
    renderParticles = rangle == 0;
    if (renderParticles) {
        UpdateParticles();
    }
}

