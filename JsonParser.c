//#ifndef _TOKENPARSER
//#define	_TOKENPARSER 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct JsonStru
{
  char Name[100];
  char Value[100];
} JsonStru;

typedef enum jsonFieldType_
{
  Name = 0,
  Value = 1
} jsonFieldType;

// char jsonStrMain[] = "{ \r\n \"Name\":\"Masoud\", \r\n \"Family\":\"Rajaei\",\r\n \"tel\":\"0913\",\r\n }";

int IdxDicOrValue = 0;
char *lastString;
JsonStru *FlatJsonStru(char JsonStr[]);
int findDic(JsonStru *myDic, jsonFieldType Field, char *Value, int isPrintList);


// this method convert Json string to structure with name and value
JsonStru *FlatJsonStru(char JsonStr[])
{
  struct JsonStru *MyDic = {0};
  int idxChar = 0;
  int modeNumber = 0;

  int dicCounter = 0;

  int curStringIdx = 0;
  int qotCount = 0;

  MyDic = (JsonStru *)malloc(sizeof(JsonStru) * 100);

  printf("Starting \r\n");

  lastString = (char *)malloc(2000);
  char curChar = JsonStr[idxChar];
  int finished = 0;
  int Head = 0;
  int Tail = 0;
  while ( *JsonStr != '\0' )
  {
    // JsonStr[idxChar] != '}' && JsonStr[idxChar] != '\0';
    JsonStr++;
    curStringIdx = 0;
    // "{\"HEAD\":null,\"DES_URL\":\"ddffff"
    if (*JsonStr == '"')
    {
      JsonStr++; //skip first char "
        while ((*(JsonStr))!='\"')
        {
          lastString[curStringIdx + 0] = *JsonStr;
          lastString[curStringIdx + 1] = '\0';
          curStringIdx++;
          JsonStr++;
        }
      //printf("%s\r\n", lastString);
      strcpy(MyDic[dicCounter].Name, lastString);
      strcpy(MyDic[dicCounter+1].Name, (char*)"\0");

      JsonStr++; //skip secound "
      while ((*(JsonStr))!=':') JsonStr++;
      JsonStr++; //skip char :
      while ((*(JsonStr))==' ') JsonStr++;

      curStringIdx = 0;
      while ((*JsonStr)!=',' && (*JsonStr)!='}')
        {
          if (*JsonStr!='\"' && (*JsonStr)!='\r' && (*JsonStr)!='\n')
          {
            lastString[curStringIdx + 0] = *JsonStr;
            lastString[curStringIdx + 1] = '\0';
            curStringIdx++;
          }
          JsonStr++;
        }
    //printf("%s\r\n", lastString);
    strcpy(MyDic[dicCounter].Value, lastString);
    strcpy(MyDic[dicCounter+1].Value, (char*)"\0");

    dicCounter++;

    }
  }
  return (JsonStru *)MyDic;
}

int findDic(JsonStru *myDic, jsonFieldType Field, char *sValue, int isPrintList)
{
  int result = -1;
  int i = 0;
  for (; strlen(myDic[i].Name) > 0; i++)
  {
    if (isPrintList == 1)
      printf("Name=%s Value=%s \r\n", myDic[i].Name, myDic[i].Value);

    if (Field == Value)
    {
      if (strcmp(myDic[i].Value, sValue) == 0)
      {
        result = i;
        if (isPrintList != 1)
          break;
      }
    }
    else
    {
      if (strcmp(myDic[i].Name, sValue) == 0)
      {
        result = i;
        if (isPrintList != 1)
          break;
      }
    }
  }

  return result;
}

int dicToJson(JsonStru *myDic,char *result)
{
  char temp[80];
  int i = 0;
  strcpy(result,"{ ");
  for (; strlen(myDic[i].Name) > 0; i++)
  { 
      if (i>0) strcat(result,",");
      strcat(result,(char*)myDic[i].Name);
      strcat(result,":");  
      //printf("%s \r\n",result);
      if (!strcmp(myDic[i].Value,"null"))
      {
        sprintf(temp,"%s",(char*)myDic[i].Value);
      }
      else 
      {
        sprintf(temp,"\"%s\"",(char*)myDic[i].Value);
      }
      strcat(result,temp);
    
  }
  strcat(result,"}");
  return 0;
}
main(void)
{
  //sample json string
  char jsonStrMain[] = "       {\r\n   \"HEAD\":null,\r\n  \"DES_URL\":\"http://xxx.xx.xxx.3:8xxxx/xxx/xxxx/rcv\",\r\n\"SRC_URL\":\"http://192.168.1.1:8085/Home/Create\",\"BODYS\":\"Guten tag\",\"DATES\":\"20221012231359\",\"IDS\":\"SMC/044\",\"ACK_KEY\":\"9821619\""
                       ",              \"LOGIN_ENABLE\":1 \r\n,\"LOGIN_USR\":\"null\"\r\n,\"LOGIN_PASS\":\"null\"\r\n,\"TAIL\":null\r\n}\r\n";
  char *jsonStrMain1;
  jsonStrMain1=(char *)malloc(1000);
  JsonStru *myDic = FlatJsonStru(jsonStrMain);
  
  int idxf=findDic(myDic, Name, (char *)"DES_URL", 1);
  if (idxf!=-1) 
      printf("\r\n %s\r\n", myDic[idxf].Value);

  strcpy(myDic[1].Value,"dfdff"); //change value 
  dicToJson(myDic,jsonStrMain1);  //convert struct to json string
  
  printf("%s\r\n",jsonStrMain1);
  printf("OK\r\n");
  return 0;
}

//#endif
