#ifndef __COMPARATORS_H__
#define __COMPARATORS_H__

//width wiersze
//height kolumny

int comp_min(const int *ptr1, const int *ptr2, int width);
int comp_max(const int *ptr1, const int *ptr2, int width);
int comp_sum(const int *ptr1, const int *ptr2, int width);

int sort_rows(int **tab, int width, int height, int (*func_name)(const int *ptr1, const int *ptr2, int width));

#endif // !__COMPARATORS_H__
