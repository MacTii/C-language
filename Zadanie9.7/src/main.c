#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

#define FAIL_ALLOCATE 8
#define INCORRECT_INPUT 1

int main()
{
	struct linked_list_t *list;
	list = ll_create();
	if (!list)
		return printf("Failed to allocate memory\n"), FAIL_ALLOCATE;
	int wyb, liczba, value, err_code, index;
	do
	{
		printf("Co chcesz zrobic? ");
		if (scanf("%d", &wyb) != 1)
		{
			printf("Incorrect input\n");
			ll_clear(list);
			free(list);
			return INCORRECT_INPUT;
		}
		switch (wyb)
		{
		case 0:
			ll_clear(list);
			//free(list);
			break;
		case 1:
			printf("Podaj liczbe ");
			if (scanf("%d", &liczba) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			int x = ll_push_back(list, liczba);
			if (x != 0)
			{
				printf("Failed to allocate memory\n");
				ll_clear(list);
				free(list);
				return FAIL_ALLOCATE;
			}
			break;
		case 2:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			value = ll_pop_back(list, NULL);
			printf("%d\n", value);
			break;
		case 3:
			printf("Podaj liczbe ");
			if (scanf("%d", &liczba) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			x = ll_push_front(list, liczba);
			if (x == 2)
			{
				printf("Failed to allocate memory\n");
				ll_clear(list);
				free(list);
				return FAIL_ALLOCATE;
			}
			break;
		case 4:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			value = ll_pop_front(list, NULL);
			printf("%d\n", value);
			break;
		case 5:
			printf("Podaj liczbe ");
			if (scanf("%d", &liczba) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			printf("Podaj index ");
			if (scanf("%d", &index) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			x = ll_insert(list, (int)index, liczba);
			if (x == 1)
				printf("Index out of range\n");
			if (x == 2)
			{
				printf("Failed to allocate memory\n");
				ll_clear(list);
				free(list);
				return FAIL_ALLOCATE;
			}
			break;
		case 6:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			printf("Podaj index ");
			if (scanf("%d", &index) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			value = ll_remove(list, (int)index, &err_code);
			if (!!err_code)
			{
				printf("Index out of range\n");
				break;
			}
			printf("%d\n", value);
			break;
		case 7:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			printf("%d\n", ll_back(list, NULL));
			break;
		case 8:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			printf("%d\n", ll_front(list, NULL));
			break;
		case 9:
			if ((ll_is_empty(list)) == 1)
				printf("%d\n", 1);
			else
				printf("%d\n", 0);
			break;
		case 10:
			printf("%d\n", ll_size(list));
			break;
		case 11:
			ll_clear(list);
			//free(list);
			break;
		case 12:
			if (ll_is_empty(list))
			{
				printf("List is empty\n");
				break;
			}
			printf("Podaj index ");
			if (scanf("%d", &index) != 1)
			{
				printf("Incorrect input\n");
				ll_clear(list);
				free(list);
				return INCORRECT_INPUT;
			}
			value = ll_at(list, (int)index, &err_code);
			if (value == 1)
				printf("Index out of range\n");
			else
				printf("%d\n", value);
			break;
		case 13:
			if ((ll_is_empty(list)) != 0)
			{
				printf("List is empty\n");
				break;
			}
			ll_display(list);
			printf("\n");
			break;
		default:
			printf("Incorrect input data\n");
			//dll_clear(list);
			//free(list);
			break;
		}
	} while (wyb != 0);
	free(list);
	return 0;
}