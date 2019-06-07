#include<stdio.h>

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
//#include <malloc.h>


int cmp1 = 0 , cmp2 = 0 , cmp3 = 0 ;
char buffer2[2048] , buff1[1000],buff2[1000],buff3[1000];

void adjust_buffer(char * buffer)
{
  for (int i = 0 ; i < strlen (buffer); i++)
  {
    buffer[i] = buffer [i+1];
  }
}

void decode_sous_label(  char * line  )
{
  char s1[2] = ":";

    char *l;
    printf ("String  \"%s\" is split into tokens2:\n",line);
    l = strtok (line,s1);
    while (l!= NULL)
    {
      printf ("%s\n",l);
      l = strtok (NULL, s1);
    }
}

void decode_label(  char * tab  )
{
  char s1[2] = ",";
  //char s2[2] = ":";
    char *p;
    printf ("String  \"%s\" is split into tokens:\n",tab);
    p = strtok (tab,s1);
    l = strtok (p,s2);
    while (p!= NULL )
    {
      printf (" p = %s\n",p);
      p = strtok (NULL, s1);
    //  while (l!= NULL )
    //  {
    //    l = strtok (NULL,s2);
      //  printf (" l =%s\n",l);
      }


    }
}

/* fill buffer with struct */
void fillbuf (int label, char str )
{
  switch (label)
  {
    case 1:
    buff1[cmp1] = str ;
    cmp1++;
    break;

    case 2:
    buff2[cmp2] = str ;
    cmp2++;
    break;

    case 3:
    buff3[cmp3] = str ;
    cmp3++;
    break;
  }
}
/* terminer les buffer avec anti slach zero */
void antislach(char * buffer , int cmp)
{
  buffer[cmp] = '\0' ;
}


/* separer les structures dans des buffers */
void Fillstruct (char * buffer)
{
   int i = 0 , JsonLevel = 0, label = 0;
   bool IsString = false ;
   char str ;
printf("\n************* start of fill struct************\n" );
//   sizebuf = malloc_usable_size (buffer) ;
//   printf(" size of pointer array = %ld\n",sizebuf );
//   str = buffer[i] ;
   int BufferLength;

   BufferLength = strlen(buffer);
   for (int k = 0 ; k < BufferLength ; k ++ )
   {
  //    printf("\n json level %d\n",JsonLevel );
       str = buffer[k] ;

          switch (str)
          {
            case '{' :
            JsonLevel++;
            if (JsonLevel == 2 && label < 3)
            {
               label ++ ;
            }
            else
            {
              //do nothing
            }
            break;

            case '}':
            JsonLevel --;
            break;


         }
//printf("\n-----label %d\n",label );
        if(label <3 && JsonLevel != 1)
        {
          fillbuf ( label,str);
        }
        else if (label == 3)
        {
          fillbuf ( label,str);
        }
    }
    antislach(buff1,cmp1);
    antislach(buff2,cmp2);
    antislach(buff3,cmp3);

}


void SkipSpace_and_FillBuffer(FILE *fp , char * buffer)
{
   bool     IsJsonLevel = false ;
   bool     IsString = false ;
   int      i = 0 , JsonLevel = 0 , NumberWarning = 0 ,
            LabelNumber = 0 , cmp = 0 ;

   char     ch;

                                        //return to the start of file

   while((ch = fgetc(fp)) != EOF)
   {
      if (IsJsonLevel == true)                     //test at the end of object
      {
         if (! isspace((int) ch ) )
         {
            NumberWarning++ ;
         }
      }
      else
      {
         if (! IsString)                         //check if its not a string
         {
            if(ch == '{')
            {
               JsonLevel++;
              if (JsonLevel == 1 )              //first label
               {
                  LabelNumber++;

            /*      buff[cmp] =ch;                  //fill buffer with label
                  cmp++ ;*/
               }
               else if (JsonLevel == 2 )        //first label
               {

               }
            }
            else if(ch == '}')
            {
               JsonLevel--;
               if (JsonLevel == 0 )
               {
                  IsJsonLevel = true ;
               }
               else if (JsonLevel == 1 )                                        //another  label
               {
                  LabelNumber++;
               }
            }
            else if (ch == '"')
            {
               IsString = true;
               printf("\033[0;31m");
            }
            if (!isspace((int) ch ))                                            //check if the caracter is not a white space character
            {
               buffer2[i] = ch;
               i++;
            }
         }
         else
         {

            if (ch == '"')
            {
               IsString = false;
               printf("\033[0m");
            }
            buffer2[i] = ch;
            i++;

         }
      }
   }
   antislach(buffer2,i);
/*   for (int j = 0 ; j < i  ; j++ )
   {
      printf("%c",buffer2[j]);
   }*/
   if (IsJsonLevel == false)
   {
      printf("\033[0;31m");
      printf("\nSyntax error in JSON format!!!\n");
      printf("\033[0m");
   }

   if (NumberWarning != 0 )
   {
      printf("\033[0;33m");
      printf("\n warning2 ch = %d \n",NumberWarning);
      printf("\033[0m");
   }
}

//void init (struct )

int main(int argc, char **argv)
{
  FILE *fp;
  char *buffer;
  long int len;


  size_t n_friends;

  size_t i;

  fp = fopen("/home/mohamed-oussema.ben-/workspace/oussema/parser_json/json/config.json","r");
  fseek(fp, 0, SEEK_END);                         //go to the end of file
  len = ftell(fp);                                //calculate length of file
  buffer = (char *) malloc((len)*sizeof(char));
  rewind(fp);
  SkipSpace_and_FillBuffer(fp,buffer);
  rewind(fp);
  fread(buffer, len, 1, fp);

  fclose(fp);
  for (int i = 0 ; i < sizeof(buffer2)  ; i++ )
  {
     printf("%c",buffer2[i]);
  }

  Fillstruct(buffer2);

  printf("\nbuff1\n");
  for (int i = 0 ; i < strlen(buff1)  ; i++ )
  {
     printf("%c",buff1[i]);
  }
  printf("\nbuff2\n");
  for (int i = 0 ; i < strlen(buff2)  ; i++ )
  {
     printf("%c",buff2[i]);
  }
  printf("\nbuff3\n");
  for (int i = 0 ; i < strlen(buff3)  ; i++ )
  {
     printf("%c",buff3[i]);
  }
  adjust_buffer(buff1);
  decode_label(buff1);

//  seperatestruct (buffer);

}
