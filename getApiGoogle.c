
#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 300





// How to compile : gcc get.c -lcurl -ljson-c

// Lien du github utilisé 
// https://github.com/DaveGamble/cJSON#including-cjson 

#include <json-c/json.h>

/*
 * Function : 
 *
 * 
 *
 *
 */

struct string {
  char *ptr;
  size_t len;
};




/*
 * Function : 
 *
 * 
 *
 *
 */

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
 
  }
  s->ptr[0] = '\0';
}



/*
 * Function : 
 *
 * 
 *
 *
 */

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}


/*
 * Function : 
 *
 * 
 *
 *
 */

void getRoad(double doubleLatitude, double doubleLongitude,char *villeDestination[MAX]){
  
  printf("Function : getRoad\n");
  printf("parameters latitude -%f-\n",doubleLatitude);
  printf("parameters longitude -%f-\n",doubleLongitude);
  printf("parameters villeDestination -%s-\n",villeDestination);

  char URL_BASE[MAX],URL;
  

  // CONVERT DOUBLE TO STRING 
  char stringLatitude[50];
  char stringLongitude[50];

  snprintf(stringLatitude, 50, "%f",doubleLatitude);
  snprintf(stringLongitude, 50, "%f",doubleLongitude);

  //printf("%s",stringLatitude); //DEBUG
  //printf("%s",stringLongitude); //DEBUG


  // WE ARE BUILDING URL URL 
  strcpy (URL_BASE,"https://maps.googleapis.com/maps/api/directions/json?origin=");
  strcat(URL_BASE,stringLatitude);
  strcat(URL_BASE,",");
  strcat(URL_BASE,stringLongitude);
  strcat(URL_BASE,"&destination=");
  strcat(URL_BASE,villeDestination);
  strcat(URL_BASE,"&avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g");

  // OUR URL, YOU CAN TEST IT IN FIREFOX ! 
  printf("%s\n",URL_BASE);

  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  if(curl) {

    struct string s;
    init_string(&s);

    curl_easy_setopt(curl, CURLOPT_URL, URL_BASE);

  #ifdef SKIP_PEER_VERIFICATION  
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  #endif

  #ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  #endif

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

  res = curl_easy_perform(curl);
   
  //printf("%s\n", s.ptr);//DEBUG



  // OPEN A FILE AND WRITE DATA 
  FILE *fptr;
  fptr = fopen("dataJson.json", "w");
  if (fptr == NULL) {
    printf("Error!");
    exit(1);
  }
  fprintf(fptr, "%s", s.ptr);
  fclose(fptr);



    struct json_object *obj = json_tokener_parse(s.ptr);
    if (!obj) { fputs("json_tokener_parse failed\n", stderr); return; }

    struct json_object *way = json_object_object_get(obj, "geocoded_waypoints");
    if (!way) { fputs("no geocoded_waypoints\n", stderr); return; }

    size_t len = json_object_array_length(way);
    printf("There are %zd waypoints.\n", len);
    for (size_t idx = 0; idx < len; ++idx)
    {   printf("waypoint %zd:\n", idx);
        struct json_object *point = json_object_array_get_idx(way, idx);
        printf("geocoder_status is %s\n", json_object_get_string(json_object_object_get(point, "geocoder_status")));
        printf("place_id is %s\n",        json_object_get_string(json_object_object_get(point, "place_id")));
        printf("types is %s\n",           json_object_get_string(json_object_object_get(point, "types")));
    }

    struct json_object *routes = json_object_object_get(obj, "routes");
    if (!routes) { fputs("no routes\n", stderr); return; }

    size_t routeslen = json_object_array_length(routes);
    printf("There are %zd routes.\n", routeslen);
    for (size_t idx = 0; idx < routeslen; ++idx)
    {   printf("route %zd:\n", idx);
        struct json_object *route = json_object_array_get_idx(routes, idx);
        printf("bounds is %s\n", json_object_get_string(json_object_object_get(route, "bounds")));
    }


  //printf("%s\n",curl_easy_perform(curl));//DEBUG
  if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}





  // Documentation : https://developers.google.com/maps/documentation/directions/get-directions?hl=fr

  /*
   * Exemple type requête avec un lieu de départ/arrivé : 
   * https://maps.googleapis.com/maps/api/directions/json?origin= 
   * &destination=
   * &avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
   * https://maps.googleapis.com/maps/api/directions/json?origin=Toronto&destination=Montreal&avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
  */


  /*
   * Exemple type requête avec des coordonnées de départ/arrivé : 
   * https://maps.googleapis.com/maps/api/directions/json?origin= 
   * &destination=
   * &avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
   * https://maps.googleapis.com/maps/api/directions/json?origin=50.642782,2.833267&destination=50.636565,3.063528&avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
   *
   * Domaine des peupliers Fleurbaix
   * Latitude 50.642782 | Longitude : 2.833267
   *
   * Lille 
   * Latitude : 50.636565 | Longitude : 3.063528
   *
   * https://maps.googleapis.com/maps/api/directions/json?origin=50.642782,2.833267&destination=50.636565,3.063528&avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
   *
   */


  /*
   * Exemple type adepart avec des coordonnées 
   * 
   * origin 50.642782,2.833267
   * destination paris
   *
   * https://maps.googleapis.com/maps/api/directions/json?origin=50.642782,2.833267&destination=paris&avoid=highways&mode=bicycling&key=AIzaSyBpj0XoMAHi8naH5k-S8mAr0nexwCQvv2g
  */




int main(void){
  
  //getCoordinate();
  getRoad(50.642782,2.833267,"nieppe");






  return 0;
}
