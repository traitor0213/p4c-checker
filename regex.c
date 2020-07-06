#include <stdio.h>
#include <Windows.h>

LPCSTR KMP(const char* ptr1, const char* ptr2, int size)
{
	int length1 = size;
	int length2 = strlen(ptr2);

	for (int i = 0; i != length1; i++)
	{
		int j = 0;

		for (; j != length2; j++)
		{
			char word1 = ptr1[i + j];
			if (word1 >= 'A' && word1 <= 'Z') word1 += 32;

			char word2 = ptr2[j];
			if (word2 >= 'A' && word2 <= 'Z') word2 += 32;

			if (word1 != word2)
			{
				j = -1;
				break;
			}
		}

		if (j != -1) return ptr1 + i;
	}

	return NULL;
}

int main()
{
	char path[1024];

	int count = 0;
	
	int fsize = 0;
	FILE *fp = NULL;
	LPSTR fdata = NULL;
	LPCSTR ptr = NULL;

	const char *list_file_name = "study-blog-list.txt"; 

	char buffer[1024];
	FILE *list_file = fopen(list_file_name, "r");
	if(list_file == NULL) 
	{
		printf("[error] cannot open file: %s\n", list_file_name);
		return 0;
	}

	for(;;)
	{
		sprintf(path, "blogs/%d.html", count);

		//printf("%s\n", path);

		fp = fopen(path, "r");
		if(fp == NULL) break;

		fseek(fp, 0, SEEK_END);
		fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		fdata = (LPSTR)malloc(fsize);
		fread(fdata, fsize, 1, fp);

		/*
		for(int f = 0; f != fsize; f++)
		{
			if(fdata[f] >= 'A' &&  fdata[f] <= 'Z') 
			{
				fdata[f] += 32;	
			}
		}
		*/
		
		fclose(fp);

		if(fgets(buffer, sizeof(buffer) - 1, list_file) == NULL) 
		{
			free(fdata);
			fdata = NULL;
			
			break;
		}

		if( (ptr = KMP(fdata, "p4c", fsize)) != NULL)
		{
			strtok(buffer, "\r\n");

			printf("%s\n", buffer);

			int i = 0;
			for(;; i++)
			{
				int word = ptr[i];

				if( word >= 'A' && word <= 'Z' ||
					word >= 'a' && word <= 'z' ||
					word >= '0' && word <= '9' ||
					word == ' ')
				{
					printf("%c", ptr[i]);
				}
				else 
				{
					break;
				}
			}
			printf("\n");
		}

		free(fdata);
		fdata = NULL;

		count += 1;
	}

	fclose(list_file);

	printf("done!\n");
	
	return 0;
}