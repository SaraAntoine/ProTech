
#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 300





// How to compile : gcc get.c -lcurl -ljson-c 

//gcc -o gps gps.c -lm -lgps 


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


struct gps_data_t gps_data;




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
 * Call API Google 
 * Create a file JSON with data   
 * Parse JSON 
 * Fill the new structure with parser  
 * 
 * Parameters 
 * double doubleLatitude        => The coordinates of the initial position  
 * double doubleLongitude       => the coordinates of the initial position
 * char *villeDestination[MAX]  => City Destination 
 * 
 * Note : For the moment you can only go to a specific city ! 
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

  // Parser 

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


    struct json_object *distance ;
    struct json_object *steps;



    size_t routeslen = json_object_array_length(routes);
    printf("There are %zd routes.\n", routeslen);
    for (size_t idx = 0; idx < routeslen; ++idx){
        printf("route %zd:\n", idx);
        struct json_object *route = json_object_array_get_idx(routes, idx);
        printf("bounds is %s\n", json_object_get_string(json_object_object_get(route, "bounds")));
        
        //printf("legs is %s\n", json_object_get_string(json_object_object_get(route, "legs")));
        struct json_object *legs = json_object_object_get(route, "legs");
        size_t legslen = json_object_array_length(legs);
        printf("thera are %zd legs \n",legslen );

        for (size_t idy = 0; idy < legslen; ++idy){
            //printf("legs %zd:\n", idy);
            struct json_object *distance = json_object_array_get_idx(legs, idx);
            printf("Object Distance is %s\n", json_object_get_string(json_object_object_get(distance, "distance")));
              
            struct json_object *duration = json_object_array_get_idx(legs, idx);
            printf("Object duration is %s\n", json_object_get_string(json_object_object_get(duration, "duration")));

            struct json_object *end_location = json_object_array_get_idx(legs, idx);
            printf("Object end_location is %s\n", json_object_get_string(json_object_object_get(end_location, "end_location")));


            //struct json_object *steps = json_object_array_get_idx(legs, idx);
            //printf("Object steps is %s\n", json_object_get_string(json_object_object_get(steps, "steps")));
            struct json_object *leg = json_object_array_get_idx(legs, idx);
            struct json_object *steps = json_object_object_get(leg, "steps");
            size_t stepslen = json_object_array_length(steps);
            printf("thera are %zd steps \n",stepslen );
            
            // Browse steps ! 
            for (size_t idz = 0; idz < stepslen; ++idz){
                
                printf("steps %zd:\n", idz);

                // Fill new struct table(s) 

                struct json_object *distance = json_object_array_get_idx(steps, idz);
                printf("Object stepsDistance is %s\n", json_object_get_string(json_object_object_get(distance, "distance")));
                struct json_object *obj = json_tokener_parse(json_object_get_string(json_object_object_get(distance, "distance")));
                printf("distance text is %s\n",           json_object_get_string(json_object_object_get(obj, "text")));
                obj = json_tokener_parse(json_object_get_string(json_object_object_get(distance, "distance")));
                printf("distance value is %d\n",           json_object_get_int(json_object_object_get(obj, "value")));


                // maneuver to speech to text 
                struct json_object *maneuver = json_object_array_get_idx(steps, idz);
                if(json_object_get_string(json_object_object_get(maneuver, "maneuver"))!=NULL)
                printf("Object maneuver is %s\n", json_object_get_string(json_object_object_get(maneuver, "maneuver")));
                
                // start lat/lng calculation
                struct json_object *start_location = json_object_array_get_idx(steps, idz);
                printf("Object start_location is %s\n", json_object_get_string(json_object_object_get(start_location, "start_location")));
                
                    // lat 
                    obj = json_tokener_parse(json_object_get_string(json_object_object_get(start_location, "start_location")));
                    printf("lat start_location is %s\n",           json_object_get_string(json_object_object_get(obj, "lat")));
                    // lng
                    obj = json_tokener_parse(json_object_get_string(json_object_object_get(start_location, "start_location")));
                    printf("lng start_location is %s\n",           json_object_get_string(json_object_object_get(obj, "lng")));


                // end lat/lng calculation
                struct json_object *end_location = json_object_array_get_idx(steps, idz);
                printf("Object end_location is %s\n", json_object_get_string(json_object_object_get(end_location, "end_location")));  

                    // lat 
                    obj = json_tokener_parse(json_object_get_string(json_object_object_get(end_location, "end_location")));
                    printf("lat end_location is %s\n",           json_object_get_string(json_object_object_get(obj, "lat")));
                    // lng
                    obj = json_tokener_parse(json_object_get_string(json_object_object_get(end_location, "end_location")));
                    printf("lng end_location is %s\n\n",           json_object_get_string(json_object_object_get(obj, "lng")));


            }


        }
        
    }







  //printf("%s\n",curl_easy_perform(curl));//DEBUG
  if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}

  


/*
 * Function : getCoordinate  
 * Call GPS 
 * Get local cordinate   
 * 
 * No Parameters 
 * 
 * Return 
 *
 *
 * 
 */
  void getCoordinate(){

      if ((gps_read(&gps_data)) == -1) {
          printf("error occured reading gps data. code: %d, reason: %s\n", errno, gps_errstr(errno));
      } else {
          /* Display data from the GPS receiver. */
          if ((gps_data.status == STATUS_FIX) &&
                    (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                    !isnan(gps_data.fix.latitude) &&
                    !isnan(gps_data.fix.longitude)) {
                        printf("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", gps_data.fix.latitude, gps_data.fix.longitude, gps_data.fix.speed, gps_data.fix.time);
                } else {
                    printf("no GPS data available\n");
                }


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
  
  getCoordinate();

  getRoad(50.642782,2.833267,"nieppe");






  return 0;
}
