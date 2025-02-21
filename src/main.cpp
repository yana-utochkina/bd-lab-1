#include <iostream>
#include <cstring>
#include "constants.h"
#include "Models/Visit.h"
#include "Models/User.h"
#include "files.h"
#include "Models/GarbageCollector.h"
#include "Models/IndexTable.h"
#include "functions.h"
#include "Menu.h"


int main() {
    {


        Menu menu = Menu();
        menu.start();


        while (true)
        {
            try
            {
                std::string command = menu.getCommand();
                menu.executeCommand(command);
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }



        // std::string phone1 = "0674527841";
        // std::string fullName1 = "Oleg Shevchenko";
        // std::string birthDate1 = "25081995";
        //
        // User* u1 = new User(-1, 0, 1, phone1.data(), fullName1.data(), birthDate1.data());
        // insert_m(user_ind, user_gc, u1);

        // std::string phone2 = "0987654321";
        // std::string fullName2 = "Daria Naumenko";
        // std::string birthDate2 = "04122000";
        //
        // User* u2 = new User(-1, 0, 2, phone2.data(), fullName2.data(), birthDate2.data());
        // insert_m(user_ind, user_gc, u2);

        // std::string phone3 = "5678901234";
        // std::string fullName3 = "Ivan Ogar";
        // std::string birthDate3 = "30061992";
        //
        // User* u3 = new User(-1, 0, 3, phone3.data(), fullName3.data(), birthDate3.data());
        // insert_m(user_ind, user_gc, u3);

        // std::string phone4 = "4321098765";
        // std::string fullName4 = "Lubov Pavliuk";
        // std::string birthDate4 = "15101988";
        // //
        // User* u4 = new User(-1, 0, 4, phone4.data(), fullName4.data(), birthDate4.data());
        // update_m(u4, user_ind, 4);

        // std::string phone5 = "8765432109";
        // std::string fullName5 = "Sergiy Paley";
        // std::string birthDate5 = "02031997";
        //
        // User* u5 = new User(-1, 0, 5, phone5.data(), fullName5.data(), birthDate5.data());
        // insert_m(user_ind, user_gc, u5);

        //update_m(u5, user_ind, 5);

        //User 1

        // std::string date1_1 = "14022025";
        // std::string startTime1_1 = "1205";
        // std::string endTime1_1 = "1501";
        // Visit* v1_1 = new Visit(11, date1_1.data(), startTime1_1.data(), endTime1_1.data());
        // insert_s(user_ind, visit_gc, v1_1, 1);

        // std::string date1_2 = "16022025";
        // std::string startTime1_2 = "1030";
        // std::string endTime1_2 = "1245";
        // Visit* v1_2 = new Visit(12, date1_2.data(), startTime1_2.data(), endTime1_2.data());
        // insert_s(user_ind, visit_gc, v1_2, 1);

        // User 2

        // std::string date2_1 = "15022025";
        // std::string startTime2_1 = "0900";
        // std::string endTime2_1 = "1130";
        // Visit* v2_1 = new Visit(21, date2_1.data(), startTime2_1.data(), endTime2_1.data());
        // insert_s(user_ind, visit_gc, v2_1, 2);
        //
        // std::string date2_2 = "18022025";
        // std::string startTime2_2 = "1400";
        // std::string endTime2_2 = "1630";
        // Visit* v2_2 = new Visit(22, date2_2.data(), startTime2_2.data(), endTime2_2.data());
        // insert_s(user_ind, visit_gc, v2_2, 2);
        //
        // std::string date2_3 = "19022025";
        // std::string startTime2_3 = "1015";
        // std::string endTime2_3 = "1230";
        // Visit* v2_3 = new Visit(23, date2_3.data(), startTime2_3.data(), endTime2_3.data());
        // insert_s(user_ind, visit_gc, v2_3, 2);

        // User 3
        // std::string date3_1 = "17022025";
        // std::string startTime3_1 = "0800";
        // std::string endTime3_1 = "1000";
        // Visit* v3_1 = new Visit(31, date3_1.data(), startTime3_1.data(), endTime3_1.data());
        // insert_s(user_ind, visit_gc, v3_1, 3);
        //
        // std::string date3_2 = "20022025";
        // std::string startTime3_2 = "1300";
        // std::string endTime3_2 = "1530";
        // Visit* v3_2 = new Visit(32, date3_2.data(), startTime3_2.data(), endTime3_2.data());
        // insert_s(user_ind, visit_gc, v3_2, 3);

        //update_s(v3_2, user_ind, 3, 32);



        //del_s(visit_gc, user_ind, 2, 21);
        //del_m(user_gc, visit_gc, user_ind, 2);
        //ut_m(std::cout);
        //ut_s(std::cout);
        //ut_s(std::cout);
    }

}