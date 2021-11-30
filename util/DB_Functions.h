#ifndef DB_FUNCTIONS_H
#define DB_FUNCTIONS_H


class DB_Functions
{
public:
    DB_Functions();
    static void createDatabase();

private:
    static void createUsers();
    static void createVacDays();
    static void fillGenders();
    static void fillUserRoles();
};

#endif // DB_FUNCTIONS_H
