#include "header.h"
#include "queue.h"

void buildTree(treePtr* t, itemType val)
{
	*t = (treePtr)malloc(sizeof(tree));
	(*t)->info = val;
	(*t)->left = NULL;
	(*t)->right = NULL;
}

void insertIntoTree(treePtr* t, treePtr s)
{
	if (!(*t))
		*t = s;
	else if ((*t)->info > s->info && (*t)->info != s->info)
	{
		if (!((*t)->left))
			(*t)->left = s;
		else insertIntoTree(&(*t)->left, s);
	}
	else if ((*t)->info < s->info && (*t)->info != s->info)
	{
		if (!((*t)->right))
			(*t)->right = s;
		else insertIntoTree(&(*t)->right, s);
	}
}

void insertTree(treePtr* t, itemType val)
{
	treePtr node;
	buildTree(&node, val);
	insertIntoTree(t, node);
}

void freeTree(treePtr* t)
{
	if (!(*t)) return;

	freeTree(&((*t)->left));
	freeTree(&((*t)->right));

	free(*t);
}

void inScan(treePtr* t)
{
	if (!((*t)->right) && !((*t)->left))
	{
		printf("%d ", (*t)->info);
		return;
	}

	if (!((*t)->left))
		inScan(&(*t)->left);
	
	printf("%d ", (*t)->info);
	
	if (((*t)->right))
		inScan(&(*t)->right);
}

void preScan(treePtr* t)
{
	if (!((*t)->right) && !((*t)->left))
	{
		printf("%d ", (*t)->info);
		return;
	}

	printf("%d ", (*t)->info);

	if (!((*t)->left))
		preScan(&(*t)->left);

	if (!((*t)->right))
		preScan(&(*t)->right);
}

void postScan(treePtr* t)
{
	if (!((*t)->right) && !((*t)->left))
	{
		printf("%d ", (*t)->info);
		return;
	}

	if (!((*t)->left))
		postScan(&(*t)->left);

	if (!((*t)->right))
		postScan(&(*t)->right);

	printf("%d ", (*t)->info);
}

void levelScan(treePtr t)
{
	treePtr s;

	if (!t)
	{
		queue Q;

		queueInit(&Q);
		enqueue(&Q, t);
		
		while (!isQueueEmpty(Q))
		{
			s = dequeue(&Q);
			printf("%d ", s->info);
			if (s->left) enqueue(&Q, s->left);
			if (s->right) enqueue(&Q, s->right);
		}
	}

	printf("\n");
}

int isInTree(treePtr t, itemType val)
{
	treePtr s = t;

	while (s)
	{
		if (s->info == val)
			return 1;
		else if (s->info > val)
			if (s->left)
				s = s->left;
		else if (s->right) s = s->right;
	}

	return 0;
}


treePtr getParent(treePtr* t, itemType val)
{
	treePtr s = *t;
	
	while (s && (*t))
	{
		if ((s->right && s->right->info == val) ||
			(s->left && s->left->info == val))
			return s;
		if (val < s->info)
			if (s->left)
				s = s->left;
		else if (s->right)
			s = s->right;
	}

	return s;
}

treePtr getMin(treePtr t)
{
	treePtr s = t;

	while (s->left)
		s = s->left;

	return s;
}

treePtr nextInOrderImp(treePtr* t, itemType val, treePtr s)
{
	if (!*t) return NULL;
	
	if ((*t)->info == val)
	{
		if ((*t)->right)
			return getMin((*t)->right);

		return getParent(&s, val);
	}
	if (val < (*t)->info)
			return nextInOrderImp(&(*t)->left, val, s);
	return nextInOrderImp(&(*t)->right, val, s);
}

treePtr nextInOrder(treePtr* t, itemType val)
{
	return nextInOrderImp(t, val, *t);
}

treePtr removeMin(treePtr* t)
{
	treePtr s = *t;
	treePtr tmp;

	while (s)
	{
		if (s->left)
		{
			if (!(s->left->left))
			{
				tmp = s->left;
				s->left = NULL;
				return tmp;
			}
			s = s->left;
		}
		else return NULL;
	}

	return s;
}

void deleteNode(treePtr* t, itemType val)
{
	treePtr s = *t, tmp, left, right;

	if (s)
	{
		if (s->info == val)
		{
			if (!(s->left) && !(s->right))
			{
				free(*t);
				*t = NULL;
			}
			else if (s->left && s->right)
			{
				left = s->left;
				tmp = removeMin(&(s->right));
				if (tmp)
				{
					right = s->right;
					free(*t);
					*t = tmp;
					(*t)->left = left;
					(*t)->right = right;
				}
				else
				{
					tmp = s->right;
					free(*t);
					*t = tmp;
					(*t)->left = left;
				}
			}
			else if (s->right)
			{
				tmp = s->right;
				free(*t);
				*t = NULL;
				*t = tmp;
			}
			else if (s->left)
			{
				tmp = s->left;
				free(*t);
				*t = NULL;
				*t = tmp;
			}
		}
		else if (s->info > val)
			if (s->left)
				deleteNode(&s->left, val);
		else if (s->right)
				deleteNode(&s->right, val);
	}
}

int maximum(int a, int b)
{
	return a > b ? a : b;
}

int findHeight(treePtr t, int h)
{
	if (t)
	{
		if (!(t->right) && !(t->left))
			return h;
		
		return maximum(findHeight(t->right, h + 1), findHeight(t->left, h + 1));
	}

	return 0;
}

void maxInLevels(treePtr t, int* arr, int i)
{
	if (!t) return;
	arr[i] = maximum(arr[i], t->info);
	maxInLevels(t->right, arr, i + 1);
	maxInLevels(t->left, arr, i + 1);
}

void printMaxInLevels(treePtr t)
{
	int h = findHeight(t, 0);

	int* arr = (int*)calloc(h + 1, sizeof(int));
	
	maxInLevels(t, arr, 0);

	for (int i = 0; i < h + 1; i++)
		printf("%d in %d\n", arr[i], i);

	free(arr);
}

int countNodes(treePtr t)
{
	if (!t) return 0;
	
	return 1 + countNodes(t->right) + countNodes(t->left);
}

int balanceCheck(treePtr t)
{
	if (!t) return 1;
	
	if (t->left && t->right) 
	{
		if (countNodes(t->right) < countNodes(t->left)) 
			return balanceCheck(t->right) * balanceCheck(t->left);  
		return 0;
	}
	else if (!(t->left) && t->right) return 0;
	
	return 1;
}

void countNodesByLevel(treePtr t, int* arr, int i)
{
	if (!t) return;
	
	arr[i]++;

	countNodesByLevel(t->right, arr, i + 1);
	countNodesByLevel(t->left, arr, i + 1);
}

void printBiggestLevel(treePtr t)
{
	int h = findHeight(t, 0);

	int* arr = (int*)calloc(h + 1, sizeof(int));
	
	countNodesByLevel(t, arr, 0);

	int max = arr[0], level = 0;

	for (int i = 1; i < h + 1; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
			level = i;
		}
	}

	printf("%d %d\n", max, level);

	free(arr);
}

void printLevelImp(treePtr t, int i, int level)
{
	if (!t) return;
	
	if (i == level && (t->right || t->left))
		printf("%d ", t->info);
	
	printLevelImp(t->right, i + 1, level);
	printLevelImp(t->left, i + 1, level);
}

void printLevel(treePtr t, int level)
{
	printLevelImp(t, 0, level);
	printf("\n");
}
 
int isAVL(treePtr t)
{
	int h1, h2;
	if (t)
	{
		h1 = findHeight(t->right, 0);
		h2 = findHeight(t->left, 0);
		
		if (abs(h1 - h2) > 1)
			return 0;

		return (isAVL(t->right) && isAVL(t->left));
	}

	return 1;
}

int checkBalance(treePtr t)
{
	if (!t) return NULL;
	
	return (findHeight(t->left, 1) - findHeight(t->right, 1));
}

void rotateR(treePtr* t)
{
	treePtr sub, s, r;

	s = (*t);
	sub = (*t)->left;
	r = sub->right;
	sub->right = s;
	(*t) = sub;
	s->left = r;
}

void rotateL(treePtr* t)
{
	treePtr sub, s, r;

	s = (*t);
	sub = (*t)->right;
	r = sub->left;
	sub->left = s;
	(*t) = sub;
	s->right = r;
}

void insertAVL(treePtr* t, treePtr s)
{
	if (!(*t))
	{
		*t = s;
		return;
	}

	if ((*t)->info > s->info)
		insertAVL(&(*t)->left, s);
	else if ((*t)->info < s->info)
		insertAVL(&(*t)->right, s);
	else return;

	int val = s->info;
	int bal = checkBalance((*t));
	treePtr sub;

	if (bal < -1)
	{
		sub = (*t)->right;

		if (sub->left && val < sub->info)
		{
			rotateR(&(*t)->right);
			rotateL(t);
		}
		else if (sub->right && val > sub->info)
			rotateL(t);
	}
	else if (bal > 1)
	{
		sub = (*t)->left;
		if (sub->left && val < sub->info)
			rotateR(t);
		else if (sub->right && val > sub->info)
		{
			rotateL(&(*t)->right);
			rotateR(t);
		}
	}
}

void insertIntoAVL(treePtr* t, itemType val)
{
	treePtr node = (treePtr)malloc(sizeof(tree));
	node->info = val;
	node->left = NULL;
	node->right = NULL;
	insertAVL(t, node);
}