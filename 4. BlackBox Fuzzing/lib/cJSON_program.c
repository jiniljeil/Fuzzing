#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "cJSON.h"

/*
{
    "person":
    {
        "firstName":"z",
        "lastName":"jadena",
        "email":"jadena@126.com",
        "age":8,
        "height":1.17
    }       
    "person":
    {
        "firstName":"a",
        "lastName":"pple",
        "email":"apple@2912.com",
        "age":22,
        "height":1.82
    }
    "person":
    {
        "firstName":"r",
        "lastName":"obot",
        "email":"robot@126.com",
        "age":41,
        "height":1.77
    }
}
*/
typedef struct 
{
	int id;
	char firstName[32];
	char lastName[32];
	char email[64];
	int age;
	float height;
} people;

//parse a struct array
int cJSON_to_struct_array(char *text, people worker[])
{
	cJSON *json, *arrayItem, *item, *object;
	int i;

	json = cJSON_Parse(text);
	if (!json)
	{
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else
	{
		arrayItem=cJSON_GetObjectItem(json,"people");
		if(arrayItem!=NULL)
		{
			int size = cJSON_GetArraySize(arrayItem);
			printf("cJSON_GetArraySize: size=%d\n",size);

			for(i = 0; i < size; i++)
			{
				printf("i=%d\n",i);
				object = cJSON_GetArrayItem(arrayItem, i);

				item = cJSON_GetObjectItem(object, "firstName");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s\n", item->type,item->string);
					memcpy(worker[i].firstName, item->valuestring, strlen(item->valuestring));
				}

				item = cJSON_GetObjectItem(object,"lastName");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s\n",item->type,item->string,item->valuestring);
					memcpy(worker[i].lastName, item->valuestring, strlen(item->valuestring));
				}

				item = cJSON_GetObjectItem(object,"email");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, valuestring=%s\n",item->type, item->string, item->valuestring);
					memcpy(worker[i].email, item->valuestring, strlen(item->valuestring));
				}

				item = cJSON_GetObjectItem(object,"age");
				if(item!=NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, valueint=%d\n",item->type, item->string, item->valueint);
					worker[i].age = item->valueint;
				}
				else
				{
					printf("cJSON_GetObjectItem: get age failed\n");
				}

				item = cJSON_GetObjectItem(object,"height");
				if(item != NULL)
				{
					printf("cJSON_GetObjectItem: type=%d, string is %s, value=%f\n",item->type, item->string, item->valuedouble);
					worker[i].height = item->valuedouble;
				}
			}
		}

		for(i = 0; i < 3; i++) {
			printf("i=%d, firstName=%s,lastName=%s,email=%s,age=%d,height=%f\n",
				i,
				worker[i].firstName,
				worker[i].lastName,
				worker[i].email,
				worker[i].age,
				worker[i].height);
		}

		cJSON_Delete(json);
	}
	return 0;
}

int main(int argc, char **argv)
{
    people worker[3]={{0}};

	cJSON_to_struct_array(argv[1], worker);
	return 0;
}
