struct Ct{
    float perimeter;
    float area;
    float x;
    float y;
    float radius;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    unsigned short id;
    char type;
} c[10];

short argt(char *m, short i, short column);
short argc(char *m, short i, short column);
short circle(char *m, short i, short column);
short triangle(char *m, short i, short column);
short error_detector(char *m);
short numcalculator(char *m, struct Ct* c);