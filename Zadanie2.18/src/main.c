#include <stdio.h>
#include <math.h>

#define INCORRECT -1
#define PI 3.141592
#define INCORRECT_AREA 1
#define N 50
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

struct point_t
{
    int x;
    int y;
};

struct rectangle_t
{
    struct point_t p;
    int width;
    int height;
};

struct circle_t
{
    struct point_t c;
    float r;
};

struct triangle_t
{
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

enum figure_types
{
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct figure_t
{
    union
    {
        struct rectangle_t rect;
        struct triangle_t triangle;
        struct circle_t circ;
    };
    enum figure_types type;
};

float area_triangle(const struct triangle_t *t)
{
    if(t==NULL) return INCORRECT;
    float a=sqrt(pow(t->p2.x-t->p1.x,2)+pow(t->p2.y-t->p1.y,2));
    float b=sqrt(pow(t->p3.x-t->p2.x,2)+pow(t->p3.y-t->p2.y,2));
    float c=sqrt(pow(t->p1.x-t->p3.x,2)+pow(t->p1.y-t->p3.y,2));
    if(a==0 || b==0 || c==0 || a+b<=c || a+c<=b || b+c<=a) return INCORRECT;
    float p=(a+b+c)/2;
    float pole=sqrt(p*(p-a)*(p-b)*(p-c));
    return pole;
}

float area_rectangle(const struct rectangle_t *r)
{
    if(r==NULL || r->height<=0 || r->width<=0) return INCORRECT;
    float pole=r->height*r->width;
    return pole;
}

float area_circle(const struct circle_t *c)
{
    if(c==NULL || c->r<=0) return INCORRECT;
    float pole=PI*pow(c->r,2);
    return pole;
}

float area_figure(const struct figure_t *f)
{
    if(f==NULL) return INCORRECT;
    float wynik=0;
    if(f->type==TRIANGLE) wynik=area_triangle(&f->triangle);
    else if(f->type==RECTANGLE) wynik=area_rectangle(&f->rect);
    else if(f->type==CIRCLE) wynik=area_circle(&f->circ);
    else return INCORRECT;
    return wynik;
}

void display_rectangle(const struct rectangle_t *rect)
{
    if(rect==NULL) return;
    printf("Rectangle (%d, %d), width = %d, height = %d\n",rect->p.x,rect->p.y,rect->width,rect->height);
}

void display_triangle(const struct triangle_t *t)
{
    if(t==NULL) return;
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n",t->p1.x,t->p1.y,t->p2.x,t->p2.y,t->p3.x,t->p3.y);
}

void display_circle(const struct circle_t *circ)
{
    if(circ==NULL) return;
    printf("Circle (%d, %d), radius = %f\n",circ->c.x,circ->c.y,circ->r);
}

void display_figure(struct figure_t *f)
{
    if(f==NULL) return;
    if(f->type==TRIANGLE) display_triangle(&f->triangle);
    if(f->type==RECTANGLE) display_rectangle(&f->rect);
    if(f->type==CIRCLE) display_circle(&f->circ);
}

int sort_by_area(struct figure_t **figures, int size)
{
    if(figures==NULL || size<=0) return INCORRECT_AREA;
    float area1=0,area2=0;
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size-1;j++)
        {
            area1=area_figure(*(figures+j));
            area2=area_figure(*(figures+j+1));
            if(area1==-1 || area2==-1) return INCORRECT_AREA;
            if(area1<area2)
            {
                struct figure_t *tmp=*(figures+j);
                *(figures+j)=*(figures+j+1);
                *(figures+j+1)=tmp;
            }
        }
    }
    return 0;
}

int main()
{
    struct figure_t tab[N];
    int i,x=0,number=0;
    for(i=0;i<N;i++)
    {
        printf("Enter figure's type: ");
        x=scanf("%d",&number);
        if(x!=1) return printf("Incorrect input"),INCORRECT_INPUT;
        if(number<0 || number>3) return printf("Incorrect input data"),INCORRECT_INPUT_DATA;
        if(number==0) break;
        (tab+i)->type=number;
        switch((tab+i)->type)
        {
            case 1:
                printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
                x=scanf("%d %d %d %d %d %d",&(tab+i)->triangle.p1.x,&(tab+i)->triangle.p1.y,&(tab+i)->triangle.p2.x,&(tab+i)->triangle.p2.y,&(tab+i)->triangle.p3.x,&(tab+i)->triangle.p3.y);
                if(x!=6) return printf("Incorrect input"),INCORRECT_INPUT;
                break;
            case 2:
                printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
                x=scanf("%d %d %d %d",&(tab+i)->rect.p.x,&(tab+i)->rect.p.y,&(tab+i)->rect.width,&(tab+i)->rect.height);
                if(x!=4) return printf("Incorrect input"),INCORRECT_INPUT;
                break;
            case 3:
                printf("Enter coordinates of a circle (x y radius)");
                x=scanf("%d %d %f",&(tab+i)->circ.c.x,&(tab+i)->circ.c.y,&(tab+i)->circ.r);
                if(x!=3) return printf("Incorrect input"),INCORRECT_INPUT;
                break;
        }
    }
    struct figure_t *tab1[N];
    int j;
    for(j=0;j<i;j++) *(tab1+j) = tab+j;
    int sort = sort_by_area(tab1, j);
    if(sort==1) return printf("Incorrect input data"),INCORRECT_INPUT_DATA;
    for(j=0; j<i; j++) display_figure(*(tab1+j));
    return 0;
}