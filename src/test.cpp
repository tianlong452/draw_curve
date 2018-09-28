#include "GeomLib.h"

int main()
{
    Point4 ap(1,2,3);
    Point4 bp;
    bp.copyFrom(ap);
    cout << "copyFrom: bp=  " << bp << endl;
    bool copyPOK = (bp == Point4(1,2,3));

    Vector4 av(1,2,3);
    Vector4 bv;
    bv.copyFrom(av);
    cout << "copyFrom: bv=  " << bv << endl;
    bool copyVOK = (bv == Vector4(1,2,3));

    bp = Point4(4,5,6);
    bp += av;
    cout << "add: bp=       " << bp << endl;
    bool addOK = (bp == Point4(5,7,9));

    ap = Point4(1,2,3);
    bp = Point4(4,5,6);
    av = ap - bp;
    cout << "subtract: av=  " << av << endl;
    bool subtractOK = (av == Vector4(-3,-3,-3));

    av = Vector4(1,2,3);
    bv = Vector4(4,5,6);
    cout << "dot=" << av * bv << endl;
    bool dotOK = (fabs(av * bv - 32) < 0.001);

    cout << "length(av)=   " << av.length() << endl;
    bool lengthOK = (fabs(av.length() - 3.741657) < 0.001);

    Float4 af(1,2,3,4);
    ap = af.homogenized();
    cout << "af.homogenized=" << ap << endl;
    bool homogenizeOK = (ap == Point4(0.25f,0.5f,0.75f));

    av = Vector4(1,2,3);
    av = av.normalized();
    cout << "av.normalize= " << av << endl;
    bool normalizeOK = (av == Vector4(0.26726f,0.53452f,0.80178f));

    av = Vector4(1,2,3);
    av *= 2;
    cout << "av * 2 =  " << av << endl;
    bool scaleOK = (av == Vector4(2,4,6));

    av = Vector4(1,2,3);
    bv = Vector4(4,5,6);
    av = av ^ bv;
    cout << "a cross b=   " << av << endl;
    bool crossOK = (av == Vector4(-3,6,-3));

    ap = Point4(1,2,3);
    bp = Point4(4,5,6);
    cout << "dist(a b)=   " << ap.distanceTo(bp) << endl;
    bool distOK = (fabs(ap.distanceTo(bp) - 5.1962) < 0.001);

    av = Vector4(1,2,0);
    bv = Vector4(4,5,0);
    cout << "angle(a b)=   " << av.angle(bv) << endl;
    bool angleOK = (fabs(av.angle(bv) - 0.211) < 0.001);

    bool allOK = true;
    if (!copyPOK)
    {
        cout << "copy point not OK\n";
        allOK = false;
    }
    if (!copyVOK)
    {
        cout << "copy vector not OK\n";
        allOK = false;
    }
    if (!addOK)
    {
        cout << "add not OK\n";
        allOK = false;
    }
    if (!subtractOK)
    {
        cout << "subtract not OK\n";
        allOK = false;
    }
    if (!dotOK)
    {
        cout << "dot not OK\n";
        allOK = false;
    }
    if (!lengthOK)
    {
        cout << "length not OK\n";
        allOK = false;
    }
    if (!homogenizeOK)
    {
        cout << "homogenize not OK\n";
        allOK = false;
    }
    if (!normalizeOK)
    {
        cout << "normalize not OK\n";
        allOK = false;
    }
    if (!scaleOK)
    {
        cout << "scale not OK\n";
        allOK = false;
    }
    if (!crossOK)
    {
        cout << "cross not OK\n";
        allOK = false;
    }
    if (!distOK)
    {
        cout << "dist not OK\n";
        allOK = false;
    }

    if (!allOK)
    {
        cout << "something's broken\n";
    }
    else
    {
        cout << "ALL OK!\n";
    }
	system("pause");
}
