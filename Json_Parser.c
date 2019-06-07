/**
 * \file parser.c
 * \brief A parser program.
 * \author Mohamed Oussema BEN KHEDER
 * \version 0.1
 * \date 29 Mai 2019
 *
 * Parser Program for Json file.
 *
 */
 
#include <json/json.h>
#include <stdio.h>

#define JSON_PATH "../json/config.json"
#define BUFFER_SIZE 2048

json_object* returnObj;
json_object* returnObjTab;


void JsonParseArray( json_object *jobj, char *key);

/**
 * \fn JsonParse(json_object * jobj) 
 * \brief printing the value corresponding to boolean, double, integer, strings, object and array 
 * param jobj json_object.
 * return void.
 */
void JsonParse(json_object * jobj) 
{
   
   enum json_type type;
   
   json_object_object_foreach(jobj, key, val) //get the value of each key 
   {
      type = json_object_get_type(val);       //get the type of the key value
      switch (type) 
      {
            case json_type_string:            //print a string value
               printf("key:%s ", key);
               printf("value: %s \n", json_object_get_string(val));
            
            break;
            
            case json_type_boolean:           //print a boolean value
               printf("key:%s ", key);
               printf("value: %s\n", json_object_get_boolean(val)? "true": "false");
               break;
                               
            case json_type_double:           //print a double value
               printf("key:%s ", key);
               printf("value: %lf\n", json_object_get_double(val));
               break;
                               
            case json_type_int:              //print an integer value
               printf("key:%s ", key); 
               printf("value: %d\n", json_object_get_int(val));
               break;
            
            case json_type_object:           //print an object keys values
               printf("\n***object:%s***\n", key);
               json_object_object_get_ex (jobj,key,&returnObj);
               JsonParse(returnObj); 
               break;
                              
           case json_type_array:             //print an array elements values
              printf("\njson_array: %s ",key); 
              JsonParseArray(jobj, key);
              break;
      }
   }
}

/**
 * \fn JsonParseArray( json_object *jobj, char *key) 
 * \brief extract and print array key value. 
 * param1 jobj json_object.
 * param2 key *char
 * return void.
 */
void JsonParseArray( json_object *jobj, char *key) 
{
   json_object_object_get_ex (jobj,key,&returnObjTab);               
   int arraylen = json_object_array_length(returnObjTab);
   printf("\nArray Length: %d \n",arraylen);
   int i;
   json_object * jvalue;
   for (i=0; i< arraylen; i++)
   {
      jvalue = json_object_array_get_idx(returnObjTab, i);
      printf("value[%d]: %s\n",i, json_object_get_string(jvalue));
   }  
} 


int main() {
   FILE *fp;
	char buffer[BUFFER_SIZE];
   fp = fopen(JSON_PATH,"r");                       // open file stream in reading mode
	fread(buffer, BUFFER_SIZE, 1, fp);               // read from the stream and copy in the buffer
	fclose(fp);
   json_object * jobj = json_tokener_parse(buffer); // read a string and returnd in a json object
   JsonParse(jobj);                                
}

