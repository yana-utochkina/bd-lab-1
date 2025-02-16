#include <iostream>
#include <cstring>
#include "constants.h"
#include "Models/Visit.h"
#include "Models/User.h"
#include "files.h"
#include "Models/GarbageCollector.h"
#include "Models/IndexTable.h"
#include "functions.h"


int main() {
    {
        GarbageCollector* u_gc = new GarbageCollector(USERS_GC_PATH);
        //GarbageCollector s_gc = GarbageCollector(SUBS_GC_PATH);
        IndexTable* u_ind = new IndexTable(USERS_IND_PATH);

        std::cout << u_ind->indexMap.size() << std::endl;
        std::cout << u_gc->address.size() << std::endl;

        std::string phone = "0123456789";
        std::string fullName = "Nastya T";
        std::string birthDate = "13052006";
        User* u1 = new User(0, 0, 3, phone.data(), fullName.data(), birthDate.data());

        insert_m(u_ind, u_gc, u1);
        ut_m(std::cout);
        delete u_ind;
        delete u_gc;
    }

}