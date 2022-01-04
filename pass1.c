#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findsymtab(char la[50]);
int findoptab(char opcd[50]);

int main(){
    char la[50], opcd[50], opr[50];
     char d[]=" \t\r\n";
    int lc, start=0,l;
    char line[100];
    int len=3;
    lc = 0x0;
    FILE *fp1 = fopen("D:\\d drive\\Sem-5\\ss\\input.txt", "r");
    FILE *fp2, *fp3, *fp4;
    fp2 = fopen("D:\\d drive\\Sem-5\\ss\\symtab.txt", "w");
    fp3 = fopen("D:\\d drive\\Sem-5\\ss\\intermediate.txt", "w");
    fclose(fp2);
    while ((fgets(&line, &len, fp1)) != NULL)
    {
        int len = 0;
        strcpy(la, " ");//initializing
        strcpy(opcd, " ");//initializing
        strcpy(opr, " ");//initializing
        char *p = strtok (line, d);
        char *a[4];
        while (p != NULL)
        {
            a[len++] = p;
            p = strtok (NULL, d);
        }
        if(len == 1){
            strcpy(opcd, a[0]);
        }
        else if(len == 2){
            strcpy(opcd, a[0]);
            strcpy(opr, a[1]);
        }
        else if(len == 3){
            strcpy(la, a[0]);
            strcpy(opcd, a[1]);
            strcpy(opr, a[2]);
        }
        if(strcmp(opcd, "END")==0)
            break;

        if (strcmp(opcd, "START") == 0) {
            start = (int)strtol(opr, NULL, 16);
            lc = start;
            fprintf(fp3, "%x\t%s\t%s\t%s\n", lc, la, opcd, opr);
            continue;
        }
        if((!strcmp(la, " ")==0) || (!strcmp(opcd, " ")==0) || (!strcmp(opr, " ")==0))
        {
            fprintf(fp3, "%x\t%s\t%s\t%s\n", lc, la, opcd, opr);

            if (strcmp(la, " ") != 0)
                if(!findsymtab(la))
                {
                    fp2 = fopen("D:\\d drive\\Sem-5\\ss\\symtab.txt", "a");
                    fprintf(fp2, "%s\t%x\n", la, lc);
                    fclose(fp2);
                }
                else
                {
                    printf("Duplicate Symbol found  DUPLICATE SYMBOL = %s\n", la);

                }
            if(findoptab(opcd))
                lc += 3;
            else if (strcmp(opcd, "WORD") == 0)
            {
                lc += 3;
            }
            else if (strcmp(opcd, "RESW") == 0)
            {
                lc += 3 * atoi(opr);
            }
            else if (strcmp(opcd, "RESB") == 0)
            {
                lc += 1 * atoi(opr);
            }
            else if (strcmp(opcd, "BYTE") == 0)
            {
                if(opr[0] == 'C' || opr[0] == 'c')
                    lc += (strlen(opr) - 3);
                else
                    lc ++;
            }
            else
            {
                printf("Invalid opcode found location counter will remain same \n INVALID CODE USED = %s\n", opcd);
            }

          }
    }
    l = lc - start;
    fclose(fp1);
    fclose(fp3);
     FILE *fp6 = fopen("D:\\d drive\\Sem-5\\ss\\intermediate.txt", "r");
    printf("\nIntermediate File:-\n");
    char line1[100];
    int len1=4;
    while ((fgets(&line1, &len1, fp6)) != NULL)
        printf("%s", line1);

    fclose(fp6);
     printf("\n\n The length of code is %d in decimal\n", l);
    return 0;
}
int findsymtab(char la[50])
{
    char smbl[50];
    char addr[10];
    FILE *fp4=fopen("D:\\d drive\\Sem-5\\ss\\symtab.txt","r");
    int flag = 0;

    while(!feof(fp4))
    {
        fscanf(fp4,"%s\t%s",smbl,addr);
        if(strcmp(smbl,la)==0)
        {
            flag = 1;
            break;

        }
        fscanf(fp4,"%s\t%s",smbl,addr);
    }

    fclose(fp4);
    return flag;
}

int findoptab(char opcd[50])
{
    char addr[10];
    char mne[50];
    FILE *fp5=fopen("D:\\d drive\\Sem-5\\ss\\optab.txt","r");
    int flag = 0;
    while(!feof(fp5))
    {
        fscanf(fp5,"%s\t%s",mne,addr);
        if(strcmp(mne, opcd)==0)
        {
            flag = 1;
            break;

        }
    }

    fclose(fp5);
    return flag;
}
