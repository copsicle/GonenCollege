#include "header.h"

coords drc[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
				{1, 1}, {1, 0}, {1, -1}, {0, -1}};

char** getMatrix()
{
	int rows = MATROW + (WALLSIZE * 2), cols = MATCOL + (WALLSIZE * 2);
	
	char** ans = (char**)malloc(rows * sizeof(char*));
	if (!ans) return NULL;

	for (int i = 0; i < rows; i++)
	{
		ans[i] = (char*)malloc(cols * sizeof(char));
		if (!ans[i]) return NULL;
	}

	printf("Please enter the Matrix\n");

	char c;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j < WALLSIZE || j >= (MATCOL + WALLSIZE) ||
				i < WALLSIZE || i >= (MATROW + WALLSIZE))
				ans[i][j] = '\0';
			else
			{
				c = getchar();
				while (c == '\n' || c == ' ') c = getchar();
				if (c < 'a') c += 32;
				ans[i][j] = c;
			}
		}
	}

	getchar();

	return ans;
}

void printArr(char* str)
{
	for (int i = WALLSIZE; i < (MATCOL + WALLSIZE); i++) printf("%c ", str[i]);
	printf("\n");
}

void printMat(char** mat)
{
	printf("Matrix with %d rows and %d columns \n", MATROW, MATCOL);

	for (int i = WALLSIZE; i < (MATROW + WALLSIZE); i++) printArr(mat[i]);
}

char* getWord()
{
	printf("Please enter the word to search\n");

	char* str = NULL, c;
	int size = 0;

	while ((c = getchar()) != '\n' && size <= MATROW && size <= MATCOL)
	{
		str = (char*)realloc(str, (++size + 1) * sizeof(char));
		if (!str) return NULL;
		if (c < 'a') c += 32;
		str[size - 1] = c;
	}

	if (size > MATROW || size > MATCOL)
	{
		free(str);
		printf("Word too long\n");
		return NULL;
	}
	else if (size == 0) return NULL;
	
	str[size] = '\0';
	return str;
}

void findWord(char** mat, char* word)
{
	int strl = strlen(word), l = 0, x = 0, y = 0;

	for (int i = WALLSIZE; i < (WALLSIZE + MATROW); i++)
	{
		for (int j = WALLSIZE; j < (WALLSIZE + MATCOL); j++)
		{
			for (int k = 0; k < DIRECTIONS && mat[i][j] == word[0]; k++)
			{
				x = drc[k].nRow + i;
				y = drc[k].nCol + j;
				for (l = 1; l < strl && mat[x][y] == word[l]; l++)
				{
					x = (drc[k].nRow * (l + 1)) + i;
					y = (drc[k].nCol * (l + 1)) + j;
				}
				if (l == strl)
				{
					printf("[%d][%d]\n", i - WALLSIZE, j - WALLSIZE);
					return;
				}
			}
		}
	}
	printf("Not Found\n");
}

void freeMat(char** mat)
{
	for (int i = 0; i < (MATROW + (WALLSIZE * 2)); i++)
		free(mat[i]);
	free(mat);
}

void bulkMain()
{
	char** mat = getMatrix();
	char* word = getWord();
	if (mat && word) findWord(mat, word);
	if (mat) freeMat(mat);
	if (word) free(word);
}