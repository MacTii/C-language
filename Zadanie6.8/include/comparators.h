#ifndef __COMPARATORS_H__
#define __COMPARATORS_H__

struct point_t
{
    double x;
    double y;
};

int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);

int sort(void *tab, int size, int _sizeof, int(*comparator)(const void*, const void*));

#endif // !__COMPARATORS_H__