#include <string>
#include "Models/User.h"
#include "Models/Visit.h"
#include "Models/GarbageCollector.h"
#include "Models/IndexTable.h"
#ifndef MENU_H
#define MENU_H



struct Menu {
    GarbageCollector* user_gc = new GarbageCollector(USERS_GC_PATH);
    GarbageCollector* visit_gc = new GarbageCollector(VISITS_GC_PATH);
    IndexTable* user_ind = new IndexTable(USERS_IND_PATH);

    ~Menu();
    static void start();

    static std::string getCommand();
    void executeCommand(const std::string& command) const;

    void getM() const;
    void getS() const;
    void delM() const;
    void delS() const;
    void updateM() const;
    void updateS() const;
    void insertM() const;
    void insertS() const;
    void calcM() const;
    void calcS() const;
    static void utM();
    static void utS();

    static void help();
    static void help_get_m();
    static void help_get_s();
    static void help_del_m();
    static void help_del_s();
    static void help_update_m();
    static void help_update_s();
    static void help_insert_m();
    static void help_insert_s();
    static void help_calc_m();
    static void help_calc_s();
    static void help_ut_m();
    static void help_ut_s();
};



#endif //MENU_H
