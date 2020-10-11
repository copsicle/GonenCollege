#include "header.h"

polyPtr getPolynom()
{
	printf("Please enter polynom\n");
	
	char c = ' ', * str = NULL;
	polyPtr p, head = NULL, prev = NULL;
	int size;

	while (c != '\n')
	{
		p = (polyPtr)malloc(sizeof(poly));
		if (!p) return NULL;
		size = 1;

		while ((c = getchar()) != ' ')
		{
			str = (char*)realloc(str, (size + 1) * sizeof(char));
			if (!str) return NULL;
			str[size++ - 1] = c;
		}

		str[--size] = '\0';
		p->base = atoi(str);
		size = 1;

		while ((c = getchar()) != ' ' && c != '\n')
		{
			str = (char*)realloc(str, (size + 1) * sizeof(char));
			if (!str) return NULL;
			str[size++ - 1] = c;
		}

		str[--size] = '\0';
		p->exp = atoi(str);

		p->next = NULL;
		if (!head) head = p;
		else prev->next = p;
		p->next = NULL;
		prev = p;
	}
	free(str);

	return head;
}

void printPolynom(polyPtr head)
{
	if (!head) printf("Error");
	else for (polyPtr p = head; p; p = p->next)
		printf("%d %d ", p->base, p->exp);
	printf("\n");
}

polyPtr copyPolynom(polyPtr head)
{
	polyPtr ans = NULL, temp = NULL, prev = NULL;
	for (polyPtr p = head; p; p = p->next)
	{
		temp = (polyPtr)malloc(sizeof(poly));
		if (!temp) return NULL;
		temp->base = p->base;
		temp->exp = p->exp;
		if (!ans)
			ans = temp;
		else
			prev->next = temp;
		temp->next = NULL;
		prev = temp;
	}
	return ans;
}

void freePolynom(polyPtr head)
{
	polyPtr tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

polyPtr sortPolynom(polyPtr head)
{
	int i, j, swa = 1, count = 0;
	for (polyPtr p = head; p; p = p->next) count++;
	polyPtr temp, x, t, s;

	for (i = 0; i < count && swa; i++)
	{
		t = head;
		s = t;
		swa = 0;
		for (j = 0; j < count - i - 1; j++)
		{
			x = t->next;
			if (t->exp < x->exp)
			{
				if (t == head)
				{
					temp = x->next;
					head = x;
					head->next = t;
					t->next = temp;
				}
				else
				{
					temp = x->next;
					x->next = t;
					t->next = temp;
					s->next = x;
				}
				s = x;
				swa = 1;
			}
			else if (t->exp == x->exp)
			{
				t->base = t->base + x->base;
				t->next = x->next;
				free(x);
				swa = 1;
			}
			else
			{
				s = t;
				t = t->next;
			}
		}
	}
	return head;
}

polyPtr addPolynoms(polyPtr h1, polyPtr h2)
{
	polyPtr p1 = copyPolynom(h1), p2 = copyPolynom(h2);
	if (!p1 || !p2) return NULL;

	for (polyPtr p = p1; p; p = p->next)
	{
		if (!(p->next))
		{
			p->next = p2;
			break;
		}
	}
	return sortPolynom(p1);
}

polyPtr mulPolynoms(polyPtr h1, polyPtr h2)
{
	polyPtr ans = NULL, tmp = NULL;

	for (polyPtr p1 = h1; p1; p1 = p1->next)
	{
		for (polyPtr p2 = h2; p2; p2 = p2->next)
		{
			tmp = (polyPtr)malloc(sizeof(poly));
			if (!tmp) return NULL;
			tmp->base = p1->base * p2->base;
			tmp->exp = p1->exp + p2->exp;
			tmp->next = ans;
			ans = tmp;
		}
	}

	return sortPolynom(ans);
}

polyPtr diffPolynom(polyPtr head)
{
	printf("Please enter derivative depth\n");
	
	int num;
	scanf("%d", &num);
	
	polyPtr p = sortPolynom(copyPolynom(head));
	if (!p) return NULL;

	polyPtr prev;

	for (int i = 0; i < num && p; i++)
	{
		prev = p;
		for (polyPtr tmp = p; tmp; tmp = tmp->next)
		{
			if (tmp->exp == 0)
			{
				free(tmp);
				if (prev != tmp) prev->next = NULL;
				else
				{
					prev = NULL;
					tmp = NULL;
					p = NULL;
				}
				break;
			}
			tmp->base = tmp->base * tmp->exp;
			tmp->exp = tmp->exp - 1;
			prev = tmp;
		}
		printPolynom(p);
	}

	return p;
}

void polyMain()
{
	polyPtr p1 = getPolynom(), p2 = getPolynom(), p3, p4, p5;

	if (p1 && p2)
	{
		p3 = addPolynoms(p1, p2);
		p4 = mulPolynoms(p1, p2);
		freePolynom(p1);
		freePolynom(p2);
		printPolynom(p3);
		printPolynom(p4);
		if (p3) freePolynom(p3);
		if (p4)
		{
			p5 = diffPolynom(p4);
			freePolynom(p4);
			if (p5) freePolynom(p5);
		}
	}
	else if (p1) freePolynom(p1);
	else if (p2) freePolynom(p2);
}