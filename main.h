//
// Created by marcelo on 30/11/20.
//

#ifndef PORTOFLATS_MAIN_H
#define PORTOFLATS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type{Entry, Exit, Booking, Cleaning, Maintenance}TYPE;
// 0 - entrada hóspede
// 1 - saída hóspede
// 2 - registar a reserva
// 3 - limpeza
// 4 - manutenção


//enum para regras das políticas

typedef struct guest
{
    int id;
    char *name;
    int birth_year;
    struct guests *pnext;

}GUEST;

typedef struct event
{
    int id;
    int type;
    //int hour;
    //int minutes;
    TYPE event_type;

    //essencialmente trabalhar apenas por dias
    GUEST *guest;
    struct event *pnext;

}EVENT;

typedef struct day
{
    int day;
    int month;
    int year;
    EVENT *events;

}DAY;

typedef struct day_array{
    int n_days;
    int size_days;
    DAY *days;
}DAY_ARRAY;
//tem de ficar com os dias ordenados para fazer pesquisa binária
//insiro aleatoriamente e quando terminar a inserçao faço ordenação

typedef struct calendar
{
    DAY_ARRAY *days_array;
    int id_platform;
    char *platform_name;
    struct calendar *pnext;
    struct calendar *previous;

}CALENDAR;

typedef struct platform{
    int id;
    char *name;
    char *politica;
    int n_platforms;
}PLATFORM;


typedef struct studio
{
    int id;
    int number;
    char *configuration;
    int area;
    char *extra_information;
    float price_per_day;
    CALENDAR *calendar[10]; // posição 0 master e o resto para cada plataforma
    int occupation; // 0 - free, 1 - busy


}STUDIO;

typedef struct building
{
    int id;
    char *name;
    char *address;
    float latitude;
    float price_day_m2;
    float longitude;
    STUDIO **studios;
    int max_studios;
    int busy_studios;
    struct building *pnext;

}BUILDING;


// GUEST
GUEST *insert_guest(GUEST *guest_list, char *name, int id, int birth_year);
GUEST *find_guest_by_id(GUEST *guest_list, int id);
GUEST *remove_guest(GUEST *guest_list, int id);
void print_guests(GUEST *guests_list);
GUEST *read_guests_txt(GUEST *guests_list, char fn[]);
void save_guests_txt(GUEST *guests_list);
void save_guests_bin(GUEST *guests_list, char *fn);
void read_guests_bin(GUEST *guests_list, char *fn);

// Building
BUILDING *insert_building(BUILDING *building_list, char *name, int building_id, char *address, float latitude, float longitude, float price_day_m2);
BUILDING *read_buildings_txt(BUILDING *building_list, char *fn);
void save_buildings_txt(BUILDING *buildings_list);
BUILDING *find_building_by_id(BUILDING *building_list, int building_id);
BUILDING *remove_building(BUILDING *building_list, int id);
void print_buildings(BUILDING *building_list);
void print_studios_of_buildings(BUILDING *building);
BUILDING *change_building(BUILDING *building_list);

// Studio
STUDIO *create_studio (STUDIO *studio, int id, int number, char *configuration, int area, char *extra_information);
void read_studios_txt(BUILDING *buildings, char fn[]);
void remove_studio(BUILDING *building, int studio_id);
void associate_building(BUILDING *pBuilding, STUDIO *studio);

// Platform
PLATFORM *insert_platform(PLATFORM *platform_list, char *name, int id);
PLATFORM *find_platform_by_id(PLATFORM *platform_list, int id);
PLATFORM *remove_platform(PLATFORM *platform_list, int id);
void print_platforms(PLATFORM *platform_list);


STUDIO *find_studio_on_building_by_id(BUILDING *building, int studio_id);

void create_booking(BUILDING *building_list, int building_id, int studio_id, int id_calendar, int start_day, int start_month, int start_year, int end_day, int end_month, int end_year, GUEST *guests, int guest_id, int event_id);


CALENDAR *find_calendar_on_studio_by_id(STUDIO *pStudio, int calendar_id);

DAY *find_day_on_calendar(CALENDAR *pCalendar, int day, int month, int year);

DAY *create_day(int day, int month, int year);

void create_day_and_associate_to_dayarray_ordered(DAY_ARRAY *days_array, int day, int month, int year);

void read_events_txt(BUILDING *building_list, PLATFORM *platforms, GUEST *guests, char fn[]);

int return_building_id_by_studio_id(BUILDING *building_list, int studio_id);

int find_platform_id_by_name(PLATFORM *platforms, char *platform_name);

int binary_search(int array[], int left, int right, int number);


void generate_occupation_report(BUILDING *buildings);

void generate_occupation_report_txt(float percentage_building, int n_studios, int studios_id[n_studios], char *studios_occupation[n_studios], int building_id);

float generate_billing_report_of_studio(STUDIO *studio);

void generate_billing_report_of_studio_txt(int studio_id, int n_days, float total_billed);

float generate_billing_report_of_building(BUILDING *building);

void generate_billing_report_of_building_txt(float total, int number_busy_studios, int studios_id[], float studios_billed[], int building_id);

void generate_billing_report_park(BUILDING *buildings);

void generate_billing_report_park_txt(int number_of_buildings, int buildings_id[], float buildings_billed[], float total_billed);

CALENDAR *create_calendar_on_studio(BUILDING *buildings, int building_id, int studio_id, int id_platform, char *platform_name);

int main();

#endif //PORTOFLATS_MAIN_H
