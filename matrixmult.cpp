#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

float xform[4][4]; //Matrix of Transformation
float moveOrigin[4][4]; //Translation to (0,0,0)
float moveBack[4][4]; //Translation to the original place
float moveBezier[4][4];//Translation to the bezier curve coord
float rotX[4][4], rotY[4][4], rotZ[4][4];

class Vertex{
    public:
    float x, y, z;
};

Vertex p1, p2, p3, p4; //Pivots for Bezier Curve

// void initMat(float m[4][4]){
//     for(int i = 0; i < 4; i++){
//         for(int j = 0; j < 4; j++){
//             m[i][j] = 0;
//         }
//     }
// }

// void fillMat(float m[4][4]){
//     for(int i = 0; i < 4; i++){
//         for(int j = 0; j < 4; j++){
//             cout << "Element[" << i << "][" << j << "]= ";
//             cin >> m[i][j];
//         }
//     }
// }

// void printMat(float m[4][4]){
//     for(int i = 0; i < 4; i++){
//         for(int j = 0; j < 4; j++){
//             cout << m[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

void initRotateX(float degX){
    float radX = degX * M_PI /180;
    rotX[0][0] = 1;
    rotX[0][1] = 0;
    rotX[0][2] = 0;
    rotX[0][3] = 0;
    rotX[1][0] = 0;
    rotX[1][1] = cos(radX);
    rotX[1][2] = -sin(radX);
    rotX[1][3] = 0;
    rotX[2][0] = 0;
    rotX[2][1] = sin(radX);
    rotX[2][2] = cos(radX);
    rotX[2][3] = 0;
    rotX[3][0] = 0;
    rotX[3][1] = 0;
    rotX[3][2] = 0;
    rotX[3][3] = 1;
}

void initRotateY(float degY){
    float radY = degY * M_PI / 180;
    rotY[0][0] = cos(radY);
    rotY[0][1] = 0;
    rotY[0][2] = sin(radY);
    rotY[0][3] = 0;
    rotY[1][0] = 0;
    rotY[1][1] = 1;
    rotY[1][2] = 0;
    rotY[1][3] = 0;
    rotY[2][0] = -sin(radY);
    rotY[2][1] = 0;
    rotY[2][2] = cos(radY);
    rotY[2][3] = 0;
    rotY[3][0] = 0;
    rotY[3][1] = 0;
    rotY[3][2] = 0;
    rotY[3][3] = 1;
}

void initRotateZ(float degZ){
    float radZ = degZ * M_PI / 180;
    rotZ[0][0] = cos(radZ);
    rotZ[0][1] = -sin(radZ);
    rotZ[0][2] = 0;
    rotZ[0][3] = 0;
    rotZ[1][0] = sin(radZ);
    rotZ[1][1] = cos(radZ);
    rotZ[1][2] = 0;
    rotZ[1][3] = 0;
    rotZ[2][0] = 0;
    rotZ[2][1] = 0;
    rotZ[2][2] = 1;
    rotZ[2][3] = 0;
    rotZ[3][0] = 0;
    rotZ[3][1] = 0;
    rotZ[3][2] = 0;
    rotZ[3][3] = 1;
}

void initPivot(float pivX, float pivY, float pivZ){
    calcTransl(moveOrigin, pivX, pivY, pivZ);
}

void initBezier(float coords[12]){
    p1.x = coords[0];
    p1.y = coords[1];
    p1.z = coords[2];
    p2.x = coords[3];
    p2.y = coords[4];
    p2.z = coords[5];
    p3.x = coords[6];
    p3.y = coords[7];
    p3.z = coords[8];
    p4.x = coords[9];
    p4.y = coords[10];
    p4.z = coords[11];
}

void calcTransl(float mat[4][4], float movX, float movY, float movZ){
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = movX;

    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[1][3] = movY;

    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
    mat[2][3] = movZ;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

void calcBezier(float t){
    float newX, newY, newZ;

	newX = pow((1-t), 3) * p1.x + 3*pow((1-t), 2)*t * p2.x + 3*(1-t)*pow(t, 2) * p3.x + pow(t, 3) * p4.x;
	newY = pow((1-t), 3) * p1.y + 3*pow((1-t), 2)*t * p2.y + 3*(1-t)*pow(t, 2) * p3.y + pow(t, 3) * p4.y;
	newZ = pow((1-t), 3) * p1.z + 3*pow((1-t), 2)*t * p2.z + 3*(1-t)*pow(t, 2) * p3.z + pow(t, 3) * p4.z;

    calcTransl(moveBezier, newX, newY, newZ);
}

void multMat(float A[4][4], float B[4][4], float matRes[4][4]){
    matRes[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + A[0][2]*B[2][0] + A[0][3]*B[3][0];
    matRes[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1] + A[0][2]*B[2][1] + A[0][3]*B[3][1];
    matRes[0][2] = A[0][0]*B[0][2] + A[0][1]*B[1][2] + A[0][2]*B[2][2] + A[0][3]*B[3][2];
    matRes[0][3] = A[0][0]*B[0][3] + A[0][1]*B[1][3] + A[0][2]*B[2][3] + A[0][3]*B[3][3];

    matRes[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0] + A[1][2]*B[2][0] + A[1][3]*B[3][0];
    matRes[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1] + A[1][2]*B[2][1] + A[1][3]*B[3][1];
    matRes[1][2] = A[1][0]*B[0][2] + A[1][1]*B[1][2] + A[1][2]*B[2][2] + A[1][3]*B[3][2];
    matRes[1][3] = A[1][0]*B[0][3] + A[1][1]*B[1][3] + A[1][2]*B[2][3] + A[1][3]*B[3][3];

    matRes[2][0] = A[2][0]*B[0][0] + A[2][1]*B[1][0] + A[2][2]*B[2][0] + A[2][3]*B[3][0];
    matRes[2][1] = A[2][0]*B[0][1] + A[2][1]*B[1][1] + A[2][2]*B[2][1] + A[2][3]*B[3][1];
    matRes[2][2] = A[2][0]*B[0][2] + A[2][1]*B[1][2] + A[2][2]*B[2][2] + A[2][3]*B[3][2];
    matRes[2][3] = A[2][0]*B[0][3] + A[2][1]*B[1][3] + A[2][2]*B[2][3] + A[2][3]*B[3][3];

    matRes[3][0] = A[3][0]*B[0][0] + A[3][1]*B[1][0] + A[3][2]*B[2][0] + A[3][3]*B[3][0];
    matRes[3][1] = A[3][0]*B[0][1] + A[3][1]*B[1][1] + A[3][2]*B[2][1] + A[3][3]*B[3][1];
    matRes[3][2] = A[3][0]*B[0][2] + A[3][1]*B[1][2] + A[3][2]*B[2][2] + A[3][3]*B[3][2];
    matRes[3][3] = A[3][0]*B[0][3] + A[3][1]*B[1][3] + A[3][2]*B[2][3] + A[3][3]*B[3][3];
}

//Rotate in X, Y and Z and returns the point back to its "original" pivot point.
void myRotate(Vertex v, float degX, float degY, float degZ, float res[4]){
    float aux[4][4];
    float ver[4];

    initRotateX(degX);
    initRotateY(degY);
    initRotateZ(degZ); 

    ver[0] = v.x;
    ver[1] = v.y;
    ver[2] = v.z;
    ver[3] = 1;

    multMat(moveBack, rotZ, aux);
    multMat(aux, rotY, xform);
    multMat(xform, rotX, aux);
    multMat(aux, moveOrigin, xform);

    res[0] = xform[0][0]*ver[0] + xform[0][1]*ver[1] + xform[0][2]*ver[2] + xform[0][3]*ver[3];
    res[1] = xform[1][0]*ver[0] + xform[1][1]*ver[1] + xform[1][2]*ver[2] + xform[1][3]*ver[3];
    res[2] = xform[2][0]*ver[0] + xform[2][1]*ver[1] + xform[2][2]*ver[2] + xform[2][3]*ver[3];
    res[3] = xform[3][0]*ver[0] + xform[3][1]*ver[1] + xform[3][2]*ver[2] + xform[3][3]*ver[3];
}

//Rotates in X, Y and Z and then translates to Bezier's next point
void myRot_and_Bezier(Vertex v, float degX, float degY, float degZ, float t, float res[4]){
    float aux[4][4];
    float ver[4];

    initRotateX(degX);
    initRotateY(degY);
    initRotateZ(degZ);
    calcBezier(t); //Pivot points are known from the begining

    ver[0] = v.x;
    ver[1] = v.y;
    ver[2] = v.z;
    ver[3] = 1;

    multMat(moveBezier, rotZ, aux);
    multMat(aux, rotY, xform);
    multMat(xform, rotX, aux);
    multMat(aux, moveOrigin, xform);

    res[0] = xform[0][0]*ver[0] + xform[0][1]*ver[1] + xform[0][2]*ver[2] + xform[0][3]*ver[3];
    res[1] = xform[1][0]*ver[0] + xform[1][1]*ver[1] + xform[1][2]*ver[2] + xform[1][3]*ver[3];
    res[2] = xform[2][0]*ver[0] + xform[2][1]*ver[1] + xform[2][2]*ver[2] + xform[2][3]*ver[3];
    res[3] = xform[3][0]*ver[0] + xform[3][1]*ver[1] + xform[3][2]*ver[2] + xform[3][3]*ver[3];
}

/*Implementación en una biblioteca propia*/
int main(){
    float rX[4][4], rY[4][4], rZ[4][4];
    float ans[4];
    Vertex v;
    v.x = 5; v.y = 4; v.z = 1;
    calcTransl(moveBack, 10.0/3, 4.0, 4.0/3);
    calcTransl(moveOrigin, -10.0/3, -4.0, -4.0/3);

    myRotate(v, 15.0, 65.0, 30.0, ans);

    cout << "x = " << ans[0] << endl;
    cout << "y = " << ans[1] << endl;
    cout << "z = " << ans[2] << endl;
    cout << "h = " << ans[3] << endl;
}