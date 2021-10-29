#ifndef INITDB_H
#define INITDB_H


class DB_Functions
{
public:
    DB_Functions();
    static void createDatabase();

private:
    static void createUsers();
    static void fillGenders();
    static void fillUserRoles();
};

#endif // INITDB_H
