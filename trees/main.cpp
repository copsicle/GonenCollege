#include "header.h"

treePtr scanTree(boolean AVL);

int main()
{
	int choice, exit = 0;
	treePtr t;
	
	while (!exit)
	{
		t = NULL;

		printf("Enter question no. to test(2-6): ");
		scanf("%d", &choice);
		
		switch (choice)
		{
		case 0:
			exit = 1;
			break;
		case 2:
			t = scanTree(FALSE);
			levelScan(t);
			printMaxInLevels(t);
			break;
		case 3:
			t = scanTree(FALSE);
			printf("%d\n", balanceCheck(t));
			break;
		case 4:
			t = scanTree(FALSE);
			printBiggestLevel(t);
			break;
		case 5:
			t = scanTree(FALSE);
			printf("Enter level: ");
			scanf("%d", &choice);
			printLevel(t, choice);
			break;
		case 6:
			t = scanTree(TRUE);
			inScan(&t);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	
		if (t) freeTree(&t);
	}

	return 0;
}

treePtr scanTree(boolean AVL)
{
	treePtr t;
	itemType num;
	
	printf("Enter value for the root of the tree: ");
	scanf("%d", &num);
	buildTree(&t, num);

	printf("\nEnter values for the tree and end with 0:\n");
	scanf("%d", &num);

	while (num)
	{
		AVL ? insertIntoAVL(&t, num) : insertTree(&t, num);
		scanf("%d", &num);
	}

	return t;
}