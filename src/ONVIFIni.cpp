#include "ONVIFIni.h"  
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
namespace yyhonviflib
{   
ONVIFIni::ONVIFIni()  
{  
}  

ONVIFIni::~ONVIFIni()  
{  
}  

int ONVIFIni::ReadIni(const char *Path, char *Root, char *Key, char *Value)
{
    char *buffer = new char[256];
    char *ptr    = NULL;
    char *ptr1   = NULL;
    int length   = 0;
    int result   = -1;
    FILE *fp;
    fp = fopen(Path, "rb+");
    if(fp == NULL)
    {
        cout<<Path<<" doesnot exist"<<endl;
        return result;
    }  
    while (!feof(fp))  
    {  
        memset(buffer, 0, 256);
        fgets(buffer, 256, fp);
        if(strchr(buffer, '['))
        {
            if(strstr(buffer, Root))
            {
                memset(buffer, 0, 256);
                fgets(buffer, 256, fp);
                while (!feof(fp) && !strchr(buffer, '['))
                {
                   if(strstr(buffer, Key))
                   {
                       ptr = strchr(buffer, '=');
                       ptr1 = strchr(buffer, '\n');
                       length = ptr1 - ptr; 
                       memcpy(Value, ptr+1, length-1);
                       result = 0;
                       break;
                   }
                   memset(buffer, 0, 256);
                   fgets(buffer, 256, fp);
                }
                break;
            }
        }
        
    }  
    delete[] buffer;
    if(fp != NULL)
        fclose(fp);
    return result;
}  
int ONVIFIni::WriteIni(const char *Path, char *Root, char *Key, char *Value)
{
    char *buffer = new char[256];
    char *bufferMove = new char[204800];
    int result = -1;
    FILE *fp;
    long offset = 0;
    fp = fopen(Path, "rb+");
    if(fp == NULL)
    {
        cout<<Path<<" doesnot exist"<<endl;
        return result;
    }
    while(!feof(fp))
    {
        memset(buffer, 0, 256);
        fgets(buffer, 256, fp); 
        if(strchr(buffer, '['))
        {
            if(strstr(buffer, Root))
            {
                do
                {
                    offset = ftell(fp);
                    memset(buffer, 0, 256);
                    fgets(buffer, 256, fp);
                    if(strstr(buffer, Key))
                    {
                        memset(buffer, 0, 256);
                        sprintf(buffer, "%s=%s\n", Key, Value);
                        memset(bufferMove, 0, 204800);
                        fread(bufferMove, 1, 204800, fp);
                        fseek(fp, offset, SEEK_SET);
                        fwrite(buffer, 1, strlen(buffer), fp);
                        fwrite(bufferMove, 1, strlen(bufferMove), fp);
                        result = 0;
                        break;
                    }
                }while(!feof(fp) && !strchr(buffer, '['));
                break;
            }
        }
    }
    delete[] buffer;
    delete[] bufferMove;
    if(fp != NULL)
        fclose(fp);
    return result;
}

} //end namespace