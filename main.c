#include "main.h"


int main() {


    GUEST *guests = NULL;
    guests = read_guests_txt(guests, "guests.txt");
    //print_guests(guests);
    //save_guests_txt(guests);
    //save_guests_bin(guests, "guests.bin");
    //read_guests_bin(guests, "guests.bin");
    //remove_guest(guests, 35384);
    //print_guests(guests);


    BUILDING *buildings = NULL;
    BUILDING *buildings_aux = NULL;
    buildings = read_buildings_txt(buildings, "buildings.txt");
    //buildings_aux = read_buildings_txt(buildings_aux, "buildings.txt");
   /* int i = 0;

    while(buildings_aux != NULL){
        i++;
        buildings_aux = buildings_aux->pnext;
    }
    int array[i];
    free(buildings_aux);
    buildings_aux = read_buildings_txt(buildings_aux, "buildings.txt");*/


   // binary_search(array, buildings->id, 0, 2);
    //save_buildings_txt(buildings);
    //print_buildings(buildings);
    //buildings = remove_building(buildings, 4);
    //print_buildings(buildings);


    STUDIO *studios = NULL;
    read_studios_txt(buildings, "studios.txt");

    (*buildings->studios)->occupation = 1;
    (*(buildings->studios + 1))->occupation = 1;
    (*buildings->pnext->studios)->occupation = 1;

    generate_occupation_report(buildings);

    CALENDAR *calendar_aux = create_calendar_on_studio(buildings, 4, 16, 1, "AirBnC");
    (*buildings->studios)->calendar[1]->days_array = (DAY_ARRAY *) calloc(5, sizeof(DAY_ARRAY));
    (*buildings->studios)->calendar[1]->days_array->days = (DAY *) calloc(5, sizeof(DAY));
    (*buildings->studios)->calendar[1]->days_array->size_days = 5;
    (*buildings->studios)->calendar[1]->days_array->n_days = 1;


    (*buildings->studios)->calendar[1]->days_array->days->day = 1;
    (*buildings->studios)->calendar[1]->days_array->days->month = 1;
    (*buildings->studios)->calendar[1]->days_array->days->year = 2021;

    generate_billing_report_park(buildings);

    //create_calendar_on_studio(buildings, 1, 1, 1, "AirBnC");

    //create_booking(buildings, 1, 1, 1, 1, 2, 2020, 2, 2, 2020, guests, 35384, 1);

    //print_studios_of_buildings(buildings);
    //buildings = change_building(buildings, studios);

    //print_studios_of_buildings(buildings);
    //studios = remove_studio(buildings, studios, 50);
    //print_studios(studios);


    //PLATFORM *platforms = NULL;
    //platforms = insert_platform(platforms, "AirBnC", 1);
    //platforms = insert_platform(platforms, "AirBnD", 2);
    //platforms = insert_platform(platforms, "AirBnE", 3);
    //platforms = insert_platform(platforms, "AirBnF", 4);
    //print_platforms(platforms);
    //platforms = remove_platform(platforms, 1);
    //print_platforms(platforms);



    return 0;
}

/*+++++++++++++++++++++++++++++++++++++
  +             GUESTS                +
  +++++++++++++++++++++++++++++++++++++*/

 /**
  * Função que insere os dados de um hóspede na respetiva lista de hóspedes
  * @param guest_list lista onde os hóspedes estão armazenados
  * @param name nome do hóspede que estamos a inserir
  * @param id id do hóspede que estamos a inserir
  * @param birth_year ano de nascimento do hóspede que estamos a inserir
  * @return lista de hóspedes depois da inserção
  */
GUEST *insert_guest(GUEST *guest_list, char *name, int id, int birth_year){

    GUEST *guest_current = NULL, *aux = NULL;

    if (guest_list == NULL){

        guest_list = (GUEST*) malloc (sizeof (GUEST));
        guest_list->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(guest_list->name, name);
        guest_list->id = id;
        guest_list->birth_year = birth_year;
        guest_list->pnext = NULL;
        return guest_list;
    }else{

        guest_current = find_guest_by_id(guest_list, id);
        if(guest_current != NULL){
            printf("\nGuests already registed!\n");
            return guest_list;
        }

        aux = (GUEST *) malloc(sizeof (GUEST));
        aux->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(aux->name, name);
        aux->id = id;
        aux->birth_year = birth_year;
        aux->pnext = (struct guests *) guest_list;

        guest_list = aux;

        return guest_list;
    }
}

/**
 * Função que remove um hóspede da respetiva lista de hóspedes através do id inserido
 * @param guest_list lista de hóspedes
 * @param id id do hóspede a remover
 * @return lista de hóspedes depois da remoção
 */
GUEST *remove_guest(GUEST *guest_list, int id){

    if(guest_list == NULL){
        printf("Guest's List empty \n");
        return guest_list;
    }
    if(guest_list->id == id){
        GUEST *gDel = guest_list;
        guest_list = (GUEST *) guest_list->pnext;
        printf("\nThe guest with the id: '%d' and name: '%s' was successfully removed!\n", gDel->id, gDel->name);
        free(gDel);
        return guest_list;
    }

    GUEST *current = guest_list, *next = (GUEST *) guest_list->pnext;

    while(next != NULL && next->id != id){
        current = next;
        next = (GUEST *) next->pnext;
    }
    if(next != NULL && next->id == id){
        current->pnext = next->pnext;
        printf("\nThe guest with the id: '%d' and name: '%s' was successfully removed!\n", next->id, next->name);
        free(next);
    }
    return guest_list;
}

/**
 * Função que encontra o hóspede na respetiva lista de hóspedes pelo seu id, retornando-o
 * @param guest_list lista de todos os hóspedes
 * @param id id do hóspede a encontrar
 * @return hóspede caso seja encontrado a
 * @return NULL se não encontrar o id inserido
 */
GUEST *find_guest_by_id(GUEST *guest_list, int id){

    while (guest_list != NULL){
        if (guest_list->id == id){
            return guest_list;
        }
        guest_list = (GUEST *) guest_list->pnext;
    }
    return NULL;
}

/**
 * Função qeu printa todos os hóspedes presentes na lista de hóspedes
 * @param guests_list lista de hóspedes
 */
void print_guests(GUEST *guests_list){

    printf("\n------------------------- GUEST -------------------------\n");

    GUEST *guest_current = NULL;
    if (guests_list == NULL){
        printf("\nGuest's List Empty!\n");
    }else{

        printf("\n");
        guest_current = guests_list;
        while (guest_current != NULL){
            printf("ID: %d | Name: %s | Birth_Year: %d\n", guest_current->id, guest_current->name, guest_current->birth_year);
            guest_current = (GUEST *) guest_current->pnext;
        }
    }
    printf("\n----------------------------------------------------------\n");
}

/**
 * Função que lê hóspedes de um ficheiro txt e faz a respetiva inserção na lista de hóspedes através da função insert
 * @param guests_list lista de hóspedes onde os mesmos vão ser inseridos
 * @param fn ficheiro onde vamos ler os hóspedes
 * @return lista de hóspedes
 */
GUEST *read_guests_txt(GUEST *guests_list, char fn[]){

    GUEST *guest_current = NULL;

    FILE *fp = fopen (fn, "r");

    if(fp != NULL){

        int guest_id, year_of_birth;
        char name[100], buffer[100];

        fgets (buffer, 100, fp);
        while(fgets (buffer, 100, fp) != NULL){
            char *token = strtok (buffer, ",");

            strcpy (name, token);
            token = strtok (NULL, ",");
            guest_id = atoi (token);
            token = strtok (NULL, ",");
            year_of_birth = atoi (token);

            guest_current = insert_guest(guest_current, name, guest_id, year_of_birth);
        }
        fclose (fp);
        guests_list = guest_current;
        return guests_list;
    }else{
        printf("\nERROR!!\n");
        return guests_list;
    }
}

/**
 * Função que guarda os hóspedes armazenados em memória na lista de hóspedes num ficheiro txt
 * @param guests_list lista hóspedes armazenados em memória
 */
void save_guests_txt(GUEST *guests_list){

    GUEST *guest_current = (GUEST *) malloc(sizeof(GUEST));
    guest_current = guests_list;

    FILE *fp;
    fp = fopen("guests_saved.txt", "a");

    if(fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fputs("name,id,year_of_birth\n", fp);

    while (guest_current != NULL){
        fprintf(fp, "%s,", guest_current->name);
        fprintf(fp, "%d,", guest_current->id);
        fprintf(fp, "%d\n", guest_current->birth_year);

        guest_current = (GUEST *) guest_current->pnext;
    }

    printf("\nAll guests has been saved on text file!\n");

    fclose(fp);
}

/**
 * Função que guarda os hóspedes armazenados em memória na lista de hóspedes num ficheiro binário
 * @param guests_list lista de hóspedes aramazenados em memória
 * @param fn ficheiro onde vamos guardar os hóspedes
 */
void save_guests_bin(GUEST *guests_list, char *fn){
    GUEST *current = (GUEST *) malloc(sizeof (GUEST)), *temp = (GUEST*)malloc(sizeof (GUEST));
    current = guests_list;
    temp = guests_list;
    int i = 0;

    while(temp != NULL){
        i++;
        temp = (GUEST *) temp->pnext;
    }

    FILE *fp = fopen(fn, "ab");

    if (fp != NULL)
    {
        while(current != NULL){
            fwrite(&i, sizeof(int), 1, fp);
            fwrite(&current->name, sizeof(char*), 1, fp);
            fwrite(&current->id, sizeof(int), 1, fp);
            fwrite(&current->birth_year, sizeof(int), 1, fp);

            current = (GUEST *) current->pnext;
            i++;
        }
        printf("\nGuests has been saved on a binary File!\n");
        fclose(fp);
    }else{
        printf("\nFile doesn't open!!\n");
    }
}

/**
 * Função que lê os hóspedes armazenados no ficheiro binário selecionado e os insere em memória através da função de insert
 * @param guests_list lista de hóspedes onde vão ser armazenados os hóspedes lidos do ficheiro
 * @param fn ficheiro onde estão presentes os hóspedes em formato binário
 */
void read_guests_bin(GUEST *guests_list, char *fn){

    FILE *fp = fopen(fn, "rb");
    if(fp != NULL){

        int id, birth_year, size;
        char *name;
        GUEST *current = (GUEST *) malloc(sizeof (GUEST));

        fread(&size, sizeof(int), 1, fp);
        for(int i = 0; i < size; i++){
            fread(&name, sizeof(char), 1, fp);
            fread(&id, sizeof(int), 1, fp);
            fread(&birth_year, sizeof(int), 1, fp);
            current = insert_guest(guests_list, name, id, birth_year);
        }

    }


    fclose(fp);
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*+++++++++++++++++++++++++++++++++++++
  +           BUILDINGS               +
  +++++++++++++++++++++++++++++++++++++*/

/**
 * Função que insere um edifício na sua respetiva lista de edifícios
 * @param building_list lista de edifícios onde vamos inserir o edifício
 * @param name nome do edifício
 * @param building_id id do edifício
 * @param address morada do edifício
 * @param latitude latitude do edifício
 * @param longitude longitude do edifício
 * @param price_day_m2 preço por dia por metro quadrado para este edifício
 * @return lista de edifícios já com o edifício inserido ou não se já existir
 */
BUILDING *insert_building(BUILDING *building_list, char *name, int building_id, char *address, float latitude, float longitude, float price_day_m2){

    BUILDING *building_current = NULL, *aux = NULL;

    if (building_list == NULL){
        building_list = (BUILDING*) malloc(sizeof (BUILDING));
        building_list->address = (char*) malloc(sizeof (strlen(address) + 1));
        strcpy(building_list->address, address);
        building_list->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(building_list->name, name);
        building_list->id = building_id;
        building_list->latitude = latitude;
        building_list->longitude = longitude;
        building_list->price_day_m2 = price_day_m2;
        //building_list->max_studios = 5;
        //building_list->studios = (STUDIOLIST *) calloc(5, sizeof (STUDIOLIST));
        building_list->pnext = NULL;
        return building_list;
    }else{

        building_current = find_building_by_id(building_list, building_id);
        if(building_current != NULL){
            printf("\nBuilding already exists! \n");
            return building_list;
        }

        aux = (BUILDING*) malloc(sizeof (BUILDING));
        aux->address = (char *) malloc(sizeof (strlen(address) + 1));
        strcpy(aux->address, address);
        aux->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(aux->name, name);
        aux->id = building_id;
        aux->latitude = latitude;
        aux->longitude = longitude;
        aux->price_day_m2 = price_day_m2;
        //aux->max_studios = 5;
        //aux->studios = (STUDIOLIST *) calloc(5, sizeof (STUDIOLIST));
        aux->pnext = building_list;

        building_list = aux;

        return building_list;
    }
}

/**
 * Função que altera qualquer informação relativa a um edifício
 * @param building_list lista de edifícios
 * @return lista de edifícios atualizada
 */
BUILDING *change_building(BUILDING *building_list){


    int id;

    BUILDING *building_temp = (BUILDING *) malloc(sizeof (BUILDING));
    BUILDING *building_aux = (BUILDING *) malloc(sizeof (BUILDING));
    BUILDING *building_current = (BUILDING *) malloc(sizeof (BUILDING));
    building_current = building_list;


    print_buildings(building_list);
    printf("\nWhat ID of building do you want to change?\n");
    scanf("%d",&id);

    building_temp = find_building_by_id(building_list, id);

    if(building_temp != NULL){

        printf("\nChoose which of the following options corresponds to what you want to change:\n");

        printf("\n(1) Name\n(2) Address\n(3) Latitude\n(4) Longitude\n(5) Price per day per m2\n\n");
        int option;

        scanf("%d", &option);

        switch (option){
            case 1:
                printf("\nThe current Name of this building is '%s'", building_temp->name);
                printf("\nEnter the new Name for this Building\n");
                char *new_name = (char *)malloc(sizeof(strlen(new_name) +1));
                scanf(" %[^\n]s", new_name);
                strcpy(building_temp->name, new_name);
                while(building_current->id != id){
                    building_aux = insert_building(building_aux, building_list->name, building_list->id, building_list->address, building_list->latitude, building_list->longitude, building_list->price_day_m2);
                    building_current = building_current->pnext;
                }
                remove("buildings_saved.txt");
                break;
            case 2:
                printf("\nThe current Address of this Building is '%s'", building_temp->address);
                printf("\nEnter the new Address for this Building\n");
                char *new_address = (char *)malloc(sizeof(strlen(new_address) +1));
                scanf(" %[^\n]s", new_address);
                strcpy(building_temp->address, new_address);
                remove("buildings_saved.txt");
                break;
            case 3:
                printf("\nThe current Latitude of this Building is '%f'", building_temp->latitude);
                printf("\nEnter the new Latitude for this Building\n");
                float new_latitude;
                scanf("%f", &new_latitude);
                building_temp->latitude = new_latitude;
                remove("buildings_saved.txt");
                break;
            case 4:
                printf("\nThe current Longitude of this Building is '%f'", building_temp->longitude);
                printf("\nEnter the new Longitude for this Building\n");
                float new_longitude;
                scanf("%f", &new_longitude);
                building_temp->longitude = new_longitude;
                remove("buildings_saved.txt");
                break;
            case 5:
                printf("\nThe current Price per m2/day of this Building is '%f'", building_temp->price_day_m2);
                printf("\nEnter the new Price for this Building\n");
                float new_price_per_day_per_m2;
                scanf("%f", &new_price_per_day_per_m2);
                building_temp->price_day_m2 = new_price_per_day_per_m2;
                remove("buildings_saved.txt");
                break;
            default:
                printf("\nError! Option is not correct! Nothing changed!\n");
        }


        if(option == 1 || option == 2 || option == 3 || option == 4 || option == 5){

            building_aux->pnext = building_temp;

            free(building_list);
            building_list = (BUILDING *) malloc(sizeof (BUILDING));
            building_list = building_aux;
            save_buildings_txt(building_list);

            read_studios_txt(building_list, "studios.txt");
            print_studios_of_buildings(building_list);
        }

    }

    return building_list;

}

/**
 * Função que remove um edifício da lista de edifícios dado o seu id
 * @param building_list lista de edifícios
 * @param id id do edifício a remover
 * @return lista de edifícios apoós a remoção
 */
BUILDING *remove_building(BUILDING *building_list, int id) {

    if (building_list == NULL) {
        printf("Building's List empty \n");
        return building_list;
    }

    if (building_list->id == id) {
        BUILDING *bDel = building_list;
        building_list = building_list->pnext;
        printf("\nThe Build with the id: '%d' and address: '%s' was successfully removed!\n", bDel->id, bDel->address);
        free(bDel);
        return building_list;
    }

    BUILDING *current = building_list, *next = building_list->pnext;

    while (next != NULL && next->id != id){
        current = next;
        next = next->pnext;
    }

    if (next != NULL && next->id == id){
        current->pnext = next->pnext;
        printf("\nThe Build with the id: '%d' and address: '%s' was successfully removed!\n", next->id, next->address);
        free(next);
    }
    return building_list;
}

/**
 * Função que pesquisa na lista de edifícios o edifício com o id fornecido
 * @param building_list lista de edifícios
 * @param building_id id do edifício
 * @return edifício encontrado
 * @return NULL caso não seja encontrado
 */
BUILDING *find_building_by_id(BUILDING *building_list, int building_id) {

    while (building_list != NULL) {
        if (building_list->id == building_id) {
            return building_list;
        }
        building_list = building_list->pnext;
    }
    return NULL;
}

/**
 * Função que associa um estúdio ao seu respetivo edifício
 * @param pBuilding edifício onde se vai associar o estúdio
 * @param studio estúdio a ser associado
 */
void associate_building(BUILDING *pBuilding, STUDIO *studio) {

    if(pBuilding->studios == NULL) {
        pBuilding->max_studios = 5;
        pBuilding->studios = (STUDIO **) calloc(pBuilding->max_studios, sizeof(STUDIO*));

    }else if(pBuilding->busy_studios == pBuilding->max_studios){
            pBuilding->max_studios = 2 * pBuilding->max_studios;
            pBuilding->studios = (STUDIO **) realloc(pBuilding->studios, pBuilding->max_studios * sizeof(STUDIO *));
        }

        *(pBuilding->studios + pBuilding->busy_studios) = (STUDIO *) malloc(sizeof(STUDIO));
        (*(pBuilding->studios + pBuilding->busy_studios))->configuration = (char*) malloc(strlen(studio->configuration) + 1);
        strcpy((*(pBuilding->studios + pBuilding->busy_studios))->configuration, studio->configuration);
        (*(pBuilding->studios + pBuilding->busy_studios))->extra_information = (char*) malloc(strlen(studio->extra_information) + 1);
        strcpy((*(pBuilding->studios + pBuilding->busy_studios))->extra_information, studio->extra_information);
        (*(pBuilding->studios + pBuilding->busy_studios))->id = studio->id;
        (*(pBuilding->studios + pBuilding->busy_studios))->number = studio->number;
        (*(pBuilding->studios + pBuilding->busy_studios))->area = studio->area;
        (*(pBuilding->studios + pBuilding->busy_studios))->price_per_day = studio->area * pBuilding->price_day_m2;
        (*(pBuilding->studios + pBuilding->busy_studios))->occupation = 0;

        //printf("\nStudio id:%d| Studio number:%d | Configuration:%s | Area:%dm2 | Extra Information:%s | Price:%.2f€\n", (*(pBuilding->studios + pBuilding->busy_studios))->id, (*(pBuilding->studios + pBuilding->busy_studios))->number, (*(pBuilding->studios + pBuilding->busy_studios))->configuration, (*(pBuilding->studios + pBuilding->busy_studios))->area, (*(pBuilding->studios + pBuilding->busy_studios))->extra_information,(*(pBuilding->studios + pBuilding->busy_studios))->price_per_day);

        pBuilding->busy_studios++;

}

/**
 * Função que printa todos os edifícios em memória
 * @param building_list lista de edifícios em memória
 */
void print_buildings(BUILDING *building_list){

    printf("\n------------------------- BUILDINGS -------------------------\n");

    BUILDING *building_current = NULL;

    if (building_list == NULL){
        printf("\nBuilding's List Empty!\n");
    }else{
        printf("\n");
        building_current = building_list;

        while (building_current != NULL){
            printf("ID: '%d' | Name: '%s' | Address: '%s' | Latitude: '%f' | Longitude: '%f' | Number of Busy Studios: '%d'\n", building_current->id, building_current->name, building_current->address, building_current->latitude, building_current->longitude, building_current->busy_studios);
            building_current = building_current->pnext;
        }
    }
    printf("\n-------------------------------------------------------------\n");
}

/**
 * Função que imprime os estúdios dado um determinado edifício
 * @param building edifício a procurar os estúdios
 */
void print_studios_of_buildings(BUILDING *building){

    while(building != NULL){

        printf("\n------------------------- STUDIOS_OF_BUILDING '%s' -------------------------\n", building->name);

        if(building->studios == NULL){
            printf("\nThe list of studios on building is empty!\n");
        }else{
            printf("\n");
            while(building->pnext != NULL){
                for(int i = 0; i < building->busy_studios; i++){
                    //printf("\nStudio id:%d| Studio number:%d | Configuration:%s | Area:%dm2 | Extra Information:%s | Price:%.2f€\n", (*(building->studios + i))->id, (*(building->studios + i))->number, (*(building->studios + i))->configuration, (*(building->studios) + i)->area, (*(building->studios) + i)->extra_information, (*(building->studios) + i)->price_per_day);
                }
                building = building->pnext;
            }
        }
        printf("\n---------------------------------------------------------------------------------\n");
    }

}

/**
 * Função que lê edifícios presentes num ficheiro txt e insere numa determinada lista de edifícios
 * @param building_list lista de edifícios onde vamos inserir os edifícios lidos
 * @param fn ficheiro onde se encontram os edifícios a ler
 * @return lista de edifícios depois de serem carregados todos os edifícios
 */
BUILDING *read_buildings_txt(BUILDING *building_list, char fn[]){

    BUILDING *building_current = NULL;

    FILE *fp = fopen(fn, "r");

    if(fp != NULL){

        int building_id;
        float latitude, longitude, price_day_m2;
        char name_of_building[100], address[100], buffer[100];

        fgets(buffer, 100, fp);
        while (fgets(buffer, 100, fp) != NULL){
            char *token = strtok(buffer, ",");

            building_id = atoi(token);
            token = strtok(NULL, ",");
            strcpy(name_of_building, token);
            token = strtok(NULL, ",");
            latitude = atof(token);
            token = strtok(NULL, ",");
            longitude = atof(token);
            token = strtok(NULL, ",");
            strcpy(address, token);
            token = strtok(NULL, ",");
            price_day_m2 = atof(token);

            building_current = insert_building(building_current, name_of_building, building_id, address, latitude, longitude, price_day_m2);
        }
        fclose(fp);
        building_list = building_current;
        return building_list;
    }else{
        printf("\nERROR!!\n");
        return building_list;
    }
}

/**
 * Função que guarda os edifícios aramzenados numa lista de edifícios num ficheiro txt
 * @param buildings_list lista de edifícios a guardar
 */
void save_buildings_txt(BUILDING *buildings_list){

    BUILDING *building_current = (BUILDING *) malloc(sizeof (BUILDING));
    building_current = buildings_list;

    remove("buildings_saved.txt");

    FILE *fp = fopen("buildings_saved.txt", "a");

    if(fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fputs("edificio,nome,latitude,longitude,morada,preço_dia_m2\n", fp);

    while(building_current != NULL){
        fprintf(fp, "%d,", building_current->id);
        fprintf(fp, "%s,", building_current->name);
        fprintf(fp, "%f,", building_current->latitude);
        fprintf(fp, "%f,", building_current->longitude);
        fprintf(fp, "%s,", building_current->address);
        fprintf(fp, "%.1f\n", building_current->price_day_m2);

        building_current = building_current->pnext;
    }

    printf("\nAll buildings has been saved on text file!\n");

    fclose(fp);
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/




/*+++++++++++++++++++++++++++++++++++++
  +             STUDIOS               +
  +++++++++++++++++++++++++++++++++++++*/

/**
 * Função que cria um estúdio novo com os seus respetivos parâmetros
 * @param studio estúdio onde vão ficar guardadas todas as informações
 * @param id id do estúdio novo
 * @param number número do estúdio novo
 * @param configuration configuração do estúdio novo
 * @param area area do estúdio novo
 * @param extra_information informação extra estúdio novo
 * @return estúdio criado
 */
STUDIO *create_studio (STUDIO *studio, int id, int number, char *configuration, int area, char *extra_information){

    studio = (STUDIO*) malloc(sizeof (STUDIO));
    studio->configuration = (char*) malloc(strlen(configuration) + 1);
    strcpy(studio->configuration, configuration);
    studio->extra_information = (char*) malloc(strlen(extra_information) + 1);
    strcpy(studio->extra_information, extra_information);
    studio->id = id;
    studio->number = number;
    studio->area = area;
    studio->occupation = 0;

    return studio;
}


/**
 * Função que remove um estúdio do array de estúdio de um edifício através do seu id
 * @param building edifício onde o estúdio vai ser removido
 * @param studio_id id do estúdio a remover
 */
void remove_studio(BUILDING *building, int studio_id){

    if(building->studios == NULL){
        printf("\nThis building don't have studios!\n");
        return;
    }

    if ((*building->studios)->id == studio_id){

        STUDIO *sDel = *(building->studios);
        printf("\nThe Studio with id: '%d' and configuration: '%s' was successfully removed!\n", sDel->id, sDel->configuration);

        free(*building->studios);
        *(building->studios) = *(building->studios) + 1;

        building->busy_studios--;
    }


    STUDIO *current = *(building->studios), *next = *(building->studios) + 1;

    while (next != NULL && next->id != studio_id){
        current = next;
        next = next + 1;
    }

    if (next != NULL && next->id == studio_id){
        //current + 1 == next + 1;
        printf("\nThe Studio with id: '%d' and configuration: '%s' was successfully removed!\n", next->id, next->configuration);
        free(next);
        building->busy_studios--;
    }

}


//implementar pesquia binária
STUDIO *find_studio_on_building_by_id(BUILDING *building, int studio_id){

    for(int i = 0; i < building->busy_studios; i++){
        if((*(building->studios + i))->id == studio_id){
            return (*(building->studios + i));
        }
    }
    return NULL;
}


/**
 * Função que lê de um ficheiro txt os estúdios e os adiciona ao array de estúdio do respetivo edifício
 * @param buildings lista de edifícios
 * @param fn caminho para o ficheiro a ser lido
 */
void read_studios_txt(BUILDING *buildings, char fn[]){

    STUDIO *studio_current = NULL;
    STUDIO *aux = NULL;

    FILE *fp = fopen(fn, "r");

    if (fp != NULL){

        int studio_id, number, building_id, area;
        char configuration[100], extra_information[100], buffer[100];


        fgets(buffer, 100, fp);
        while (fgets(buffer, 100, fp) != NULL){

            char *token = strtok(buffer, ",");

            studio_id = atoi(token);
            token = strtok(NULL, ",");
            number = atoi(token);
            token = strtok(NULL, ",");
            building_id = atoi(token);
            token = strtok(NULL, ",");
            strcpy(configuration, token);
            token = strtok(NULL, ",");
            area = atoi(token);
            token = strtok(NULL, ",");
            strcpy(extra_information, token);

            aux = create_studio(aux, studio_id, number, configuration, area, extra_information);


            associate_building(find_building_by_id(buildings, building_id), aux);
        }
        fclose (fp);
    } else{
        printf("\nERROR!!\n");
    }
}


/***************************************************/









PLATFORM *insert_platform(PLATFORM *platform_list, char *name, int id){

    PLATFORM *platform_current = NULL, *aux = NULL;

    if(platform_list == NULL){

        platform_list = (PLATFORM*) malloc(sizeof(PLATFORM));
        platform_list->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(platform_list->name, name);
        platform_list->id = id;
        return platform_list;
    }else{

        platform_current = find_platform_by_id(platform_list, id);
        if(platform_current != NULL){
            printf("\nPlatform already exists!\n");
            return platform_list;
        }

        aux = (PLATFORM*) malloc(sizeof (PLATFORM));
        aux->name = (char *) malloc(sizeof (strlen(name) + 1));
        strcpy(aux->name, name);
        aux->id = id;
        //aux->pnext = *platform_list;

        platform_list = aux;

        return platform_list;
    }
}

PLATFORM *find_platform_by_id(PLATFORM *platform_list, int id){

    for (int i = 0; i < sizeof(platform_list); i++) {
        if (platform_list[i].id == id){
            return &platform_list[i];
        }
    }

    /* while(platform_list != NULL){
         if(platform_list->id == id){
             return platform_list;
         }
         platform_list = platform_list->pnext;
     }*/
    return NULL;
}

PLATFORM *remove_platform(PLATFORM *platform_list, int id){
    if(platform_list == NULL){
        printf("Platform's list empty\n");
        return platform_list;
    }

    if(platform_list->id == id){
        PLATFORM *pDel = platform_list;
        //platform_list = platform_list->pnext;
        printf("\nThe platform with id: '%d' and name: '%s' was successfully removed!\n", pDel->id, pDel->name);
        free(pDel);
        return platform_list;
    }

    /* PLATFORM *current = platform_list, *next = platform_list->pnext;

     while(next != NULL && next->id != id){
         current = next;
         next = next->pnext;
     }
     if(next != NULL && next->id == id){
         current->pnext = next->pnext;
         printf("\nThe guest with id: '%d' and name: '%s' was successfully removed!\n", next->id, next->name);
         free(next);
     }*/
    return platform_list;
}

void print_platforms(PLATFORM *platform_list){

    printf("\n------------------------- PLATFORMS -------------------------\n");

    PLATFORM *platform_current = NULL;

    if(platform_list == NULL){
        printf("\nPlatform's list empty!\n");
    }else{
        printf("\n");
        platform_current = platform_list;

        for (int i = 0; i < sizeof(platform_list); i++) {
            printf("ID: '%d' | Name: '%s'\n", platform_current[i].id, platform_current[i].name);
        }
    }

    printf("\n-------------------------------------------------------------\n");
}





// find edifício, find studio, find agenda, find day, inserir nesse dia (lsita ligada de eventos)
//find calendar by id dentro da platadorma
void create_booking(BUILDING *building_list, int building_id, int studio_id, int id_calendar, int start_day, int start_month, int start_year, int end_day, int end_month, int end_year, GUEST *guests, int guest_id, int event_id){

    GUEST *guest = find_guest_by_id(guests, guest_id);
    if(guest != NULL){
        BUILDING *building_current = NULL;
        STUDIO *studio_current = NULL;
        CALENDAR *schedule = NULL;
        DAY *current_day = NULL;

        building_current = find_building_by_id(building_list, building_id);

        if(building_current != NULL){

            studio_current = find_studio_on_building_by_id(building_current, studio_id);

            if(studio_current != NULL){

                schedule = find_calendar_on_studio_by_id(studio_current, id_calendar);

                if(schedule != NULL){

                    current_day = find_day_on_calendar(schedule, start_day, start_month, start_year);

                    if(current_day == NULL){
                        create_day_and_associate_to_dayarray_ordered(schedule->days_array, start_day, start_month, start_year);
                        current_day = find_day_on_calendar(schedule, start_day, start_month, start_year);
                    }

                    if(current_day->events == NULL){
                        current_day->events = (EVENT *)malloc(sizeof(EVENT));
                        current_day->events->id = event_id;

                        enum type event_type;
                        event_type = Booking;
                        studio_current->occupation = 1;

                        current_day->events->event_type = event_type;
                        current_day->events->type = (int)event_type;
                        current_day->events->guest = guest;
                        current_day->events->pnext = NULL;
                    }else{
                        EVENT *events = (EVENT *)malloc(sizeof(EVENT));
                        events->id = event_id;

                        enum type event_type;
                        event_type = Booking;
                        studio_current->occupation = 1;

                        events->event_type = event_type;
                        events->type = (int) event_type;
                        events->guest = guest;
                        events->pnext = NULL;

                        current_day->events->pnext = events;
                    }
                }else{
                    printf("\nUnable to add booking because this calendar does not exist!\n");
                }

            }else{
                printf("\nUnable to add booking because this studio does not exist!\n");
            }

        }else{
            printf("\nUnable to add booking because this building does not exist!\n");
        }

    }else{
        printf("\nUnable to add booking because this guest does not exist!\n");
    }

}

/**
 * Função para encontrar um dia específico pretendido dada uma agenda
 * @param pCalendar agenda a procurar o dia específico
 * @param day
 * @param month
 * @param year
 * @return dia encontrado
 */
DAY *find_day_on_calendar(CALENDAR *pCalendar, int day, int month, int year) {

    for (int i = 0; i < pCalendar->days_array->n_days; i++) {
        if((pCalendar->days_array->days + i)->day == day){
            if((pCalendar->days_array->days + i)->month == month){
                if((pCalendar->days_array->days + i)->year == year){
                    return pCalendar->days_array->days + i;
                }
            }
        }
    }
    return NULL;
}

/**
 * Função que cria um dia e associa ao array de dias ordenadamente
 * @param days_array array com todos os dias
 * @param day
 * @param month
 * @param year
 */
void create_day_and_associate_to_dayarray_ordered(DAY_ARRAY *days_array, int day, int month, int year) {

    DAY *new_day = NULL;
    new_day = create_day(day, month, year);

    if(days_array == NULL){

        days_array = (DAY_ARRAY *)malloc(sizeof(DAY_ARRAY));
        days_array->days = (DAY *)calloc(5, sizeof(DAY));
        days_array->size_days = 5;
        days_array->n_days ++;
        days_array->days = new_day;


    }else if(days_array->n_days == days_array->size_days){

        days_array->size_days = 2 * days_array->size_days;
        days_array->days = (DAY *)realloc(days_array->days, days_array->size_days * sizeof(DAY));
    }

    *(days_array->days + days_array->n_days) = *(DAY *) malloc(sizeof(DAY));
    *(days_array->days + days_array->n_days) = *new_day;

    days_array->n_days ++;

    /*int quicksort_compare (const void * a, const void * b)
    {

        DAY *dayA = (DAY *)a;
        DAY *dayB = (DAY *)b;

        return ( dayB-> - dayA-> );
    }


    qsort(days_array->days, days_array->n_days, sizeof(DAY), )*/

}

/**
 * Função que cria um dia
 * @param day
 * @param month
 * @param year
 * @return dia criado
 */
DAY *create_day(int day, int month, int year) {

    DAY *pDay = (DAY *)malloc(sizeof(DAY));
    pDay->day = day;
    pDay->month = month;
    pDay->year = year;
    return pDay;
}

/**
 * Função pra encontrar a agenda no estúdio por id
 * @param pStudio estúdio onde vamos tentar encontrar a agenda
 * @param calendar_id id a encontrar
 * @return agenda encontrada
 */
CALENDAR *find_calendar_on_studio_by_id(STUDIO *pStudio, int calendar_id) {

    if((pStudio->calendar[calendar_id]) != NULL){
        return pStudio->calendar[calendar_id];
    }

    return NULL;
}


void read_events_txt(BUILDING *building_list, PLATFORM *platforms, GUEST *guests, char fn[]){

    FILE *fp = fopen(fn, "r");

    if(fp != NULL){
        int event_id, guest_id, start_day, end_day, start_month, end_month, start_year, end_year, studio_id, platform_id;
        char type_event[100], buffer[100], platform_name[100];

        fgets(buffer, 100, fp);

        while(fgets(buffer, 100, fp) != NULL){
            char *token = strtok(buffer, ",");
            char *date_token = strtok(buffer, "-");

            event_id = atoi(token);
            token = strtok(NULL, ",");
            strcpy(type_event, token);
            token = strtok(NULL, ",");
            start_year = atoi(date_token);
            date_token = strtok(NULL, "-");
            start_month = atoi(date_token);
            date_token = strtok(NULL, "-");
            start_day = atoi(token);
            token = strtok(NULL, ",");
            end_year = atoi(date_token);
            date_token = strtok(NULL, "-");
            end_month = atoi(date_token);
            date_token = strtok(NULL, "-");
            end_day = atoi(token);
            token = strtok(NULL, ",");
            guest_id = atoi(token);
            token = strtok(NULL, ",");
            studio_id = atoi(token);
            token = strtok(NULL, ",");
            strcpy(platform_name, token);
            //platform_id = atoi(token);
            platform_id = find_platform_id_by_name(platforms, platform_name);

            if (platform_id == 0){

            } else{
                int building_id = return_building_id_by_studio_id(building_list, studio_id);
                int calendar_id = platform_id;
                create_booking(building_list, building_id, studio_id, calendar_id, start_day, start_month, start_year, end_day, end_month, end_year, guests, guest_id, event_id);
            }
        }
        fclose(fp);

    } else{
        printf("\nERROR!!\n");
    }
}

int return_building_id_by_studio_id(BUILDING *building_list, int studio_id){
    while(building_list != NULL){
        for(int i = 0; i < building_list->busy_studios; i++){
            if((*(building_list->studios + i))->id == studio_id){
                    return building_list->id;
                }
        }
        building_list = building_list->pnext;
    }
    return 0;

}

int find_platform_id_by_name(PLATFORM *platforms, char *platform_name){

    for (int i = 0; i < platforms->n_platforms; i++){
        if (strcmp((platforms->name + i), platform_name)){
            return platforms->id + i;
        }
    }
    return 0;
}


int binary_search(int array[], int left, int right, int number){

    while(left >= right){
        int mid = right + (left - right) / 2;

        // check if number is present at mid
        if (array[mid] == number){
            printf("\nElement is present at index %d\n", mid);
            return mid;
        }

        // if number greater, ignore left half
        if (array[mid] < number)
            right  = mid - 1;

        // if number is smaller, ignore right half
        else
            left = mid + 1;
    }

    // if we reach here, then element was not present
    printf("\nElement is not present in array\n");
    return -1;
}

/**
 * Função que imprime e guarda num ficheiro txt as percentagens de ocupação relativas ao parque de edifícios, relativas a cada edifćio e o estado de ocupação de cada estúdio de cada edifício no momento da análise
 * @param buildings edifícios a serem analisados
 */
void generate_occupation_report(BUILDING *buildings){

    printf("\n-------------------- OCCUPATION REPORT --------------------\n");

    BUILDING *buildings_current = (BUILDING *) malloc(sizeof (BUILDING));

    buildings_current = buildings;

    while (buildings_current != NULL){
        printf("\n\nReport of Building %d:\n", buildings_current->id);

        float percentage_building = 0.0, busy = 0.0, studios = 0.0;
        int studios_id[buildings_current->busy_studios];
        char *studios_occupation[buildings_current->busy_studios];

        if(buildings_current->studios == NULL){
            printf("\n\nThe list of studios on building is empty!\n");
        }else{
            printf("\t\tStudio id:\tOccupation:");

            for(int i = 0; i < buildings_current->busy_studios; i++){
                char *studio_occupation = NULL;
                if((*(buildings_current->studios + i))->occupation == 1){
                    studio_occupation = (char *)malloc(sizeof(strlen("busy") + 1));
                    strcpy(studio_occupation, "busy");
                    busy++;

                }else if((*(buildings_current->studios + i))->occupation == 0){
                    studio_occupation = (char *)malloc(sizeof(strlen("free") + 1));
                    strcpy(studio_occupation, "free");
                }
                studios++;

                studios_id[i] = (*(buildings_current->studios + i))->id;
                studios_occupation[i] = studio_occupation;

                printf("\n\t\t%d\t\t\t%s",(*(buildings_current->studios + i))->id, studio_occupation);
            }
        }

        percentage_building = busy/studios * 100;

        int number_busy_studios = buildings_current->busy_studios;
        generate_occupation_report_txt(percentage_building, studios, studios_id, studios_occupation, buildings_current->id);

        buildings_current = buildings_current->pnext;
    }

    printf("\n-----------------------------------------------------------\n");
}

/**
 * Função que guarda informação sobre percentagem de ocupação para um edifício e o estado de ocupação de cada estúdio
 * @param percentage_building percentagem de ocupação de estúdios num edifício
 * @param n_studios total de estúdios presentes no edifício
 * @param studios_id id's dos estúdios
 * @param studios_occupation ocupação por estúdio
 * @param building_id id do edifício
 */
void generate_occupation_report_txt(float percentage_building, int n_studios, int studios_id[n_studios], char *studios_occupation[n_studios], int building_id){

    char file[50];
    snprintf(file, 50, "building_%d_report.txt", building_id);

    remove(file);

    FILE *fp = fopen(file, "a");

    if (fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fputs("\nPercentage of occupation: ", fp);
    fprintf(fp, "%.1f%%\n", percentage_building);
    fputs("\n\tStudio id:\tOccupation:", fp);

    for (int i = 0; i < n_studios; i++) {

        fprintf(fp, "\n\t%d\t\t\t%s", studios_id[i], studios_occupation[i]);

    }

    //printf("\n\nAll information has been saved on text file!\n");

    fclose(fp);
}

/**
 * Função que gera um relatório de faturação para um estúdio
 * @param studio estúdio que vai ser usado para gerar o relatório
 * @return valor da faturação para esse estúdio
 */
float generate_billing_report_of_studio(STUDIO *studio){

    printf("\n-------------------- BILLING REPORT OF STUDIO %d --------------------\n", studio->id);

    STUDIO *studio_aux = (STUDIO*) malloc(sizeof(STUDIO));
    studio_aux = studio;

    int studio_id = studio->id;
    float total = 0.0;
    int busy_days = 0;

    for(int i = 1; i <= 9; i++){
        if(studio_aux->calendar[i] != NULL){
            busy_days += studio_aux->calendar[i]->days_array->n_days;
            total += (studio_aux->price_per_day) * (studio_aux->calendar[i]->days_array->n_days);
        }
    }

    printf("\nNumber of busy days on this Studio: %d\n", busy_days);
    printf("\nTotal billed: %.2f€\n", total);

    generate_billing_report_of_studio_txt(studio_id, busy_days, total);

    printf("\n-----------------------------------------------------------------\n");

    return total;
}

/**
 * Função que gera um relatório txt com informação de faturação de um determinado estúdio
 * @param studio_id id do estúdio que vai ser vamos gerar o relatório
 * @param n_days dias ocupados com reservas
 * @param total_billed total de faturação para o estúdio
 */
void generate_billing_report_of_studio_txt(int studio_id, int n_days, float total_billed) {

    char file[50];
    snprintf(file, 50, "studio_%d_billed_report.txt", studio_id);

    remove(file);

    FILE *fp = fopen(file, "a");

    if (fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fprintf(fp, "\nNumber of busy days: %d\n\nTotal billed: %.2f€", n_days, total_billed);

    //printf("\nAll information has been saved on text file!\n");

    fclose(fp);


}

/**
 * Função que gera um relatório com a faturação de um determinado edifício, inclusive de cada um dos seus estudios
 * @param building edifício a gerar relatório
 * @return total de faturação para este edifício
 */
float generate_billing_report_of_building(BUILDING *building) {


    float studio_billed = 0.0, total = 0.0;
    int building_id = 0;
    int studios_id[building->busy_studios];
    float studios_billed[building->busy_studios];

    if (building->studios == NULL) {
        printf("\nThe studios list is empty!\n");
        return 0;
    }

    for (int i = 0; i < building->busy_studios; i++) {

        studio_billed = generate_billing_report_of_studio((*(building->studios + i)));

        studios_id[i] = (*(building->studios + i))->id;
        studios_billed[i] = studio_billed;

        total += studio_billed;
    }

    printf("\n-------------------- BILLING REPORT OF BUILDING %d --------------------\n\n", building->id);

    for (int j = 0; j < building->busy_studios; j++) {
        printf("Studio id: %d\tTotal billed: %.2f€\n", studios_id[j], studios_billed[j]);
    }

    generate_billing_report_of_building_txt(total, building->busy_studios, studios_id, studios_billed, building->id);

    printf("\nTotal billed on Building %d: %.2f€\n", building->id, total);
    return total;
    printf("\n-----------------------------------------------------------------------\n\n");

}

/**
 * Função que gera um releatório em formato txt de faturação de um determinado edifício
 * @param total total faturado para o edifício
 * @param number_busy_studios número de estúdio ocupados
 * @param studios_id id's dos estúdios presentes neste edifício
 * @param studios_billed total faturado por cada estúdio presente neste edifício ordenado consoante a sua posição
 * @param building_id id do edifício a criar relatório
 */
void generate_billing_report_of_building_txt(float total, int number_busy_studios, int studios_id[], float studios_billed[], int building_id){


    char file[50];
    snprintf(file, 50, "building_%d_billed_report.txt", building_id);

    remove(file);

    FILE *fp = fopen(file, "a");

    if (fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fputs("\n\tStudio id:\tBilled:\n", fp);

    for (int i = 0; i < number_busy_studios; i++){
        fprintf(fp, "\t%d\t\t\t%.2f€\n", studios_id[i], studios_billed[i]);
    }

    fprintf(fp, "\nTOTAL BILLED: %.2f€", total);

    //printf("\nAll information has been saved on text file!\n");

    fclose(fp);

}

/**
 * Função que gera um relatório de faturação para o parque de edifícios
 * @param buildings todos os edifícios
 */
void generate_billing_report_park(BUILDING *buildings){

    BUILDING *building_current = (BUILDING *) malloc(sizeof (BUILDING));
    BUILDING *building_aux = (BUILDING *) malloc(sizeof (BUILDING));
    building_current = buildings;
    building_aux = buildings;

    int i = 0;

    while(building_aux != NULL){
        i++;
        building_aux = building_aux->pnext;
    }

    float total = 0.0, building_billed = 0.0, buildings_billed[i];
    int buildings_id[i];

    while(building_current != NULL){

        building_billed = generate_billing_report_of_building(building_current);

        buildings_id[building_current->id] = building_current->id;
        buildings_billed[building_current->id] = building_billed;


        total += building_billed;

        building_current = building_current->pnext;
    }

    printf("\n-------------------- BILLING REPORT OF ALL BUILDINGS --------------------\n\n");

    printf("Building id:\tTotal Billed:\n");
    for (int j = 1; j <= i; j++){
        printf("%d\t%.2f€\n", buildings_id[j], buildings_billed[j]);
    }


    printf("\nTOTAL BILLED ON PARK: %.2f€", total);

    generate_billing_report_park_txt(i, buildings_id, buildings_billed, total);

    printf("\n-------------------------------------------------------------------------\n\n");
}

/**
 * Função que gera um relatório em formato txt de faturação de um parque de edifícios
 * @param number_of_buildings número de edifícios presentes no parque
 * @param buildings_id id's dos edifícios presentes no parque
 * @param buildings_billed totais faturados por cada edifício
 * @param total_billed total faturado no parque
 */
void generate_billing_report_park_txt(int number_of_buildings, int buildings_id[], float buildings_billed[], float total_billed){

    remove("park_billed.txt");

    FILE *fp = fopen ("park_billed.txt", "a");

    if (fp == NULL){
        printf("\nERROR! Not possible open this file!\n");
        return;
    }

    fputs("Building id:\tBilled on Building:", fp);

    for (int i = 1; i <= number_of_buildings; i++){
        fprintf(fp, "\n%d\t\t\t\t%.2f€", buildings_id[i], buildings_billed[i]);
    }

    fprintf(fp, "\n\nTOTAL BILLED ON PARK: %.2f€", total_billed);

    //printf("\nAll information has been saved on text file!\n");

    fclose(fp);

}

/**
 * Função para criar e alocar memória para um calendário num estúdio
 * @param buildings edifícios a percorrer
 * @param building_id id do edifício onde vamos fazer a associação
 * @param studio_id id do estúdio a encontrar e associar
 * @param id_platform id da plataforma que corresponde à posição do calendário em questão
 * @param platform_name nome da plataforma
 * @return calendário adicionado
 */
CALENDAR *create_calendar_on_studio(BUILDING *buildings, int building_id, int studio_id, int id_platform, char *platform_name){

    BUILDING *building_current = (BUILDING *) malloc(sizeof (BUILDING));
    STUDIO *studio_aux = (STUDIO *) malloc(sizeof (STUDIO));


    building_current = find_building_by_id(buildings, building_id);
    studio_aux = find_studio_on_building_by_id(building_current, studio_id);

    studio_aux->calendar[id_platform] = (CALENDAR *)malloc(sizeof(CALENDAR));
    studio_aux->calendar[id_platform]->id_platform = id_platform;
    studio_aux->calendar[id_platform]->platform_name = (char *)malloc(sizeof(strlen(platform_name) + 1));
    strcpy(studio_aux->calendar[id_platform]->platform_name, platform_name);

    return studio_aux->calendar[id_platform];

}
