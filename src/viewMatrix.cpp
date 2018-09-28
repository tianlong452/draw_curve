#ifdef WIN32
#include <windows.h>
#endif

#include "GeomLib.h"

//#include <fstream>
#include <iostream>

//using namespace std;

int main(int argc, char** argv) {

    Point4  eye(2,3,4);  // camera eye point
    Point4  ref(1,1,1);  // camera look-at point
    Vector4 vup(0,1,0);  // which way is up.

    cout << "eye=" << eye << endl;
    cout << "ref=" << ref << endl;
    cout << "vup=" << vup << endl;

    Vector4 x,y,z;         // the camera basis vectors

    z = (eye - ref).normalized();

    cout << "eye-ref=" << eye-ref << endl;

    x = (vup^z).normalized();

    y = z^x;

    cout << "Camera basis vectors are:" << endl;
    cout << "x=" << x << endl;
    cout << "y=" << y << endl;
    cout << "z=" << z << endl;

    cout << "eye=" << eye << endl;
    cout << "ref=" << ref << endl;
    cout << "vup=" << vup << endl;

    //
    // Now, set up the viewing transformation.
    // Recall that M_vcs-wcs is:
    // Trans(eye) * [x,y,z,0]
    //   where x,y,z are written as 4x1 column vectors inside the 4x4 matrix.
    // So, M_wcs-vcs is the inverse of this matrix.
    // (A*B)^{-1} = B^{-1} * A^{-1}, so we want
    // [x,y,z,0]^T * Trans(-eye).
    //

    Matrix4 Rot(x[0], x[1], x[2], 0.0,
                y[0], y[1], y[2], 0.0,
                z[0], z[1], z[2], 0.0,
                0.0,   0.0,  0.0, 1.0);
    Matrix4 Trans = Matrix4::Translation(-eye[0], -eye[1], -eye[2]);

    Matrix4 Mview = Rot * Trans;

    cout << "rotation-only matrix is:" << endl;
    cout << Rot;
    cout << "translation is:" << endl;
    cout << Trans;
    cout << "Viewing transformation is:" << endl;
    cout << Mview;

    //
    // And now, we transform a few points from world to camera coords.
    //
    Point4 pw,pc;
    pw.set(0,0,0);
    pc = Mview*pw;
    cout << "point in world:  " << pw << "\n";
    cout << "point in camera: " << pc << endl;
    pw.set(1,1,1);
    pc = Mview*pw;
    cout << "point in world:  " << pw << endl;
    cout << "point in camera: " << pc << endl;

    pw.set(1,2,3);
    pc = Mview*pw;
    cout << "point in world:  " << pw << endl;
    cout << "point in camera: " << pc << endl;

    Vector4 vw(10,10,3);
    Float4 fc = Mview*vw;
    cout << "point in world:  " << vw << endl;
    cout << "point in camera: " << fc << endl;

    return 0;
}
