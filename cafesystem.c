#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<conio.h>
/*
Future implementation:
- Adding more items to current user's bill
- Monthly reminders to pay the bill
check for last date of month and print due balance as reminder to pay
*/

void speak(char s[500])
{
    char command[500];
    strcpy(command, "espeak \"");
    strcat(command, s);
    strcat(command, "\"");
    system(command);
}
char tod() {
    time_t seconds;
    int s;
    struct tm *timeStruct;
    seconds=time(NULL);
    timeStruct=localtime(&seconds);
    s=timeStruct->tm_hour;
    if (s>8&&s<=12)
        return 'm';
    else if (s>12&&s<=16)
        return 'a';
    else
        return 'n';
}
typedef struct student {
    char name[50];
    char srn[50];
    float wallet;
    bool type;
}s;

typedef struct menu {
    char item[50];
    float price;
}m;

void updatedb(s arr_s[]);

void main()
{
    s arr_s[10];
    FILE *fp = fopen("database.csv","r");
    if (!fp)
    {
        printf("Error occured");
        return 0;
    }
    char text[1024];
    int row_count = 0;
    int field_count = 0;

    int i=0;
    while(fgets(text, 1024, fp))
    {
        field_count = 0;
        row_count++;
        if (row_count == 1)
        continue;

        char *field = strtok(text, ",");
        while(field)
        {
            if(field_count == 0)
            strcpy(arr_s[i].name, field);

            if(field_count == 1)
            strcpy(arr_s[i].srn, field);

            if(field_count == 2)
            arr_s[i].wallet=(float)(*field);

            if(field_count == 3)
            arr_s[i].type=(int)(*field);

            field = strtok(NULL, ",");
            field_count++;

        }
        i++;
    }
    fclose(fp);

    m arr_mb[5]={{"Dosa",49.99},{"Chapathi",34.99},{"Idli",44.99},{"Poori",59.99},{"Sandwich",34.99}};

    m arr_ml[5]={{"SouthThaali",79.99},{"NorthThaali",99.99},{"Minimeals",49.99},{"JeeraRice",69.99},{"CurdRice",49.99}};

    char srn[50];
    char food[50];
    float bill;
    while(1)
    {
        if (tod()=='m')
        {
            printf("\nGood Morning\n");
            speak("Good Morning");
            printf("\nMENU:\nItem:");
            printf("       Price:\n");
            for (i=0;i<5;i++)
            {
                printf("%s%7.2f\n",arr_mb[i].item, arr_mb[i].price);
            }
            printf("\nSRN: ");
            scanf("%s",srn);
            if (strcmp(srn, "Q")==0)
            {
                speak("Goodbye");
                break;
            }
            printf("Food item: ");
            scanf("%s",food);
            for(int i=0;i<5;i++)
            {
                if (strcmp(arr_mb[i].item,food)==0)
                {
                     bill=arr_mb[i].price;
                     break;
                }
            }
        }
        else if (tod()=='a')
        {
            printf("\nGood Afternoon!\n");
            speak("Good Afternoon");
            printf("\nMENU:\nItem:");
            printf("       Price:\n");
            for (i=0;i<5;i++)
            {
                printf("%s%7.2f\n",arr_ml[i].item, arr_ml[i].price);
            }

            printf("\nSRN: ");
            scanf("%s",srn);
            if (strcmp(srn, "Q")==0)
            {
                speak("Goodbye");
                break;
            }
            printf("\nFood item: ");
            scanf("%s",food);
            for(int i=0;i<5;i++)
            {
                if (strcmp(arr_ml[i].item,food)==0)
                {
                     bill=arr_ml[i].price;
                     break;
                }
            }
        }
        else
        {
        printf("\nService Closed\n-------------------------------------------------------------");
        speak("Service Closed");
        break;
        }

        for(int i=0;i<10;i++)
        {
        if (strcmp(arr_s[i].srn,srn)==0)
            {
                printf("\nInitial wallet= %f\n", arr_s[i].wallet);
                arr_s[i].wallet+=bill;
                printf("\nFinal wallet= %f\n", arr_s[i].wallet);
                printf("\nBill= %f\n", bill);
                updatedb(arr_s);
                printf("\nPrice added to virtual wallet.\n-------------------------------------------------------------");
                speak("Price added to virtual wallet");
                reminder(arr_s[i]);
                break;
            }
         }
}
}
void updatedb(s arr_s[])
        {
          FILE *file;
          file = fopen("database.csv", "w");
          if (file == NULL)
          {
            printf("Error opening file.\n");

          }
          fprintf(file, "Name,SRN,Wallet,Type\n");
          for (int i = 0; i < 10; i++)
          {

            fprintf(file,
                          "%s,%s,%f,%d\n",
                          arr_s[i].name,
                          arr_s[i].srn,
                          arr_s[i].wallet,
                          arr_s[i].type);
            if (ferror(file))
            {
              printf("Error writing to file.\n");
            }
          }

          fclose(file);
}

void reminder(struct student s)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int d=tm.tm_mday;
        int m=tm.tm_mon+1;
        if(d==31&&(m==1||m==3||m==5||m==7||m==8||m==10||m==12)||d==28&&m==2||d==30&&(m==4||m==6||m==9||m==11))
            {
            printf("\nMonthly reminder to pay %f\n",s.wallet);
            speak("Monthly reminder to pay");
            }
}
