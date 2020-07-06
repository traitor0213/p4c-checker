#include <stdio.h>
#include <Windows.h>

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
		fclose(fp);

		if(fgets(buffer, sizeof(buffer) - 1, list_file) == NULL) 
		{
			free(fdata);
			fdata = NULL;
			
			break;
		}

		if( (ptr = strstr(fdata, "p4c")) != NULL)
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
		}

		free(fdata);
		fdata = NULL;

		count += 1;
	}

	fclose(list_file);
	
	return 0;
}