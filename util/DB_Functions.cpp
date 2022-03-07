#include "DB_Functions.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

namespace DB_Functions_NS {
static const char* CREATE_USERS = "CREATE TABLE users ( "
                                  "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                  "username varchar(256) UNIQUE, "
                                  "password varchar(256), "
                                  "first_name varchar(256), "
                                  "last_name varchar(256), "
                                  "personal_email varchar(256) UNIQUE, "
                                  "work_email varchar(256) UNIQUE, "
                                  "date_birth date, "
                                  "date_employment date, "
                                  "user_role_id integer NOT NULL, "
                                  "gender_id integer NOT NULL, "
                                  "CONSTRAINT users_pkey PRIMARY KEY (id), "
                                  "CONSTRAINT fk_user_role_id FOREIGN KEY (user_role_id) "
                                  "    REFERENCES public.user_roles (id) MATCH SIMPLE "
                                  "    ON UPDATE NO ACTION ON DELETE NO ACTION, "
                                  "CONSTRAINT fk_gender_id FOREIGN KEY (gender_id) "
                                  "    REFERENCES public.genders (id) MATCH SIMPLE "
                                  "    ON UPDATE NO ACTION ON DELETE NO ACTION "
                                  ");";

static const char* CREATE_GENDERS = "CREATE TABLE genders ( "
                                    "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                    "name varchar(256) UNIQUE, "
                                    "CONSTRAINT genders_pkey PRIMARY KEY (id) "
                                    ");";

static const char* CREATE_USER_ROLES = "CREATE TABLE user_roles ( "
                                       "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                       "role_name varchar(256) UNIQUE, "
                                       "CONSTRAINT user_roles_pkey PRIMARY KEY (id) "
                                       ");";

static const char* CREATE_USER_DAYS = "CREATE TABLE user_days ("
                                          "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                          "user_id integer NOT NULL, "
                                          "year integer NOT NULL, "
                                          "days integer NOT NULL, "
                                          "CONSTRAINT user_days_pkey PRIMARY KEY (id), "
                                          "CONSTRAINT fk_user FOREIGN KEY (user_id) "
                                          "     REFERENCES public.users (id) MATCH SIMPLE "
                                          "     ON UPDATE NO ACTION ON DELETE NO ACTION "
                                          ");";

static const char* CREATE_HOLIDAYS = "CREATE TABLE holidays ( "
                                     "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                     "date date UNIQUE, "
                                     "description varchar(256) NOT NULL, "
                                     "CONSTRAINT holidays_pkey PRIMARY KEY (id) "
                                     ");";

static const char* CREATE_AL_DAYS = "CREATE TABLE annual_leave_days ("
                                    "id INT GENERATED BY DEFAULT AS IDENTITY, "
                                    "user_id integer NOT NULL, "
                                    "date_from date NOT NULL, "
                                    "date_to date NOT NULL, "
                                    "used_days integer NOT NULL, "
                                    "CONSTRAINT annual_leave_days_pkey PRIMARY KEY (id), "
                                    "CONSTRAINT fk_user FOREIGN KEY (user_id) "
                                    "     REFERENCES public.users (id) MATCH SIMPLE "
                                    "     ON UPDATE NO ACTION ON DELETE NO ACTION "
                                    ");";

static const char* FILL_GENDERS = "INSERT INTO genders(\"id\", \"name\") VALUES (1, 'Male');"
                                  "INSERT INTO genders(\"id\", \"name\") VALUES (2, 'Female');";

static const char* FILL_USER_ROLES = "INSERT INTO user_roles(\"id\", \"role_name\") VALUES (1, 'Admin');"
                                     "INSERT INTO user_roles(\"id\", \"role_name\") VALUES (2, 'User');";

}

using namespace DB_Functions_NS;

DB_Functions::DB_Functions()
{

}

void DB_Functions::createDatabase()
{
    createUsers();
    createVacDays();
    createHolidays();
    createAlDays();
}

void DB_Functions::createUsers()
{
    QSqlQuery q;
    if(!q.exec(CREATE_USER_ROLES))
        qWarning()<<"Unable to create table user roles, error: "<<q.lastError()<<" last query: "<<q.lastQuery();

    if(!q.exec(CREATE_GENDERS))
        qWarning()<<"Unable to create table genders, error: "<<q.lastError()<<" last query: "<<q.lastQuery();

    if(!q.exec(CREATE_USERS))
        qWarning()<<"Unable to create table users, error: "<<q.lastError()<<" last query: "<<q.lastQuery();

    if(!q.exec(FILL_GENDERS))
        qWarning()<<"Unable to fill table genders, error: "<<q.lastError()<<" last query: "<<q.lastQuery();

    if(!q.exec(FILL_USER_ROLES))
        qWarning()<<"Unable to fill table user roles, error: "<<q.lastError()<<" last query: "<<q.lastQuery();
}

void DB_Functions::createVacDays()
{
    QSqlQuery q;
    if(!q.exec(CREATE_USER_DAYS))
        qWarning()<<"Unable to create table vacation days, error: "<<q.lastError()<<" last query: "<<q.lastQuery();
}

void DB_Functions::createHolidays()
{
    QSqlQuery q;
    if(q.exec(CREATE_HOLIDAYS))
        qWarning()<<"Unable to create table holidays, error: "<<q.lastError()<<" last query: "<< q.lastQuery();
}

void DB_Functions::createAlDays()
{
    QSqlQuery q;
    if(q.exec(CREATE_AL_DAYS))
        qWarning()<<"Unable to create table annual leave days, error: "<<q.lastError()<<" last query: "<< q.lastQuery();
}












