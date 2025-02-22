#include "Menu.h"
#include <iostream>
#include "functions.h"
#include <regex>

Menu::~Menu()
{
    delete this->user_gc;
    delete this->visit_gc;
    delete this->user_ind;
}

void Menu::start()
{
    std::cout << "Enter one command from list: \n";
    help();
}

std::string Menu::getCommand()
{
    std::cin.clear();

    std::string command;
    std::cin >> command;
    command = std::regex_replace(command, std::regex("[ \n\t]"), "");
    return command;
}

void Menu::executeCommand(const std::string& command) const
{
    if (command == "help") help();
    else if (command == "exit") exit(0);
    else if (command == "get_m") this->getM();
    else if (command == "get_s") this->getS();
    else if (command == "del_m") this->delM();
    else if (command == "del_s") this->delS();
    else if (command == "update_m") this->updateM();
    else if (command == "update_s") this->updateS();
    else if (command == "insert_m") this->insertM();
    else if (command == "insert_s") this->insertS();
    else if (command == "calc_m") this->calcM();
    else if (command == "calc_s") this->calcS();
    else if (command == "ut_m") this->utM();
    else if (command == "ut_s") this->utS();
    else throw std::invalid_argument("Invalid command");
}

void Menu::getM() const
{
    int userId;
    std::cin >> userId;
    User* user = new User();
    get_m(user, this->user_ind, userId);
    std::cout << *user << std::endl;
    delete user;
}

void Menu::getS() const
{
    int userId, visitId;
    std::cin >> userId >> visitId;
    Visit* visit = new Visit();
    get_s(visit, this->user_ind, userId, visitId);
    std::cout << *visit << std::endl;
    delete visit;
}

void Menu::delM() const
{
    int userId;
    std::cin >> userId;
    del_m(this->user_gc, this->visit_gc, this->user_ind, userId);
    std::cout << "Successfully deleted" << std::endl;
}

void Menu::delS() const
{
    int userId, visitId;
    std::cin >> userId >> visitId;
    del_s(this->visit_gc, this->user_ind, userId, visitId);
    std::cout << "Successfully deleted" << std::endl;
}

void Menu::updateM() const
{
    int userId;
    std::string phone, fullname, birthDay;
    std::cin >> userId >> phone >> fullname >> birthDay;
    User* user = new User(userId, phone.data(), fullname.data(), birthDay.data());
    update_m(user, this->user_ind, userId);
    delete user;
    std::cout << "Successfully updated" << std::endl;

}

void Menu::updateS() const
{
    int userId, visitId;
    std::string data, startTime, endTime;
    std::cin >> userId >> visitId >> data >> startTime >> endTime;
    Visit* visit = new Visit(userId, data.data(), startTime.data(), endTime.data());
    update_s(visit, this->user_ind, userId, visitId);
    delete visit;
    std::cout << "Successfully updated" << std::endl;
}

void Menu::insertM() const
{
    int userId;
    std::string phone, fullname, birthDay;
    std::cin >> userId >> phone >> fullname >> birthDay;
    User* user = new User(userId, phone.data(), fullname.data(), birthDay.data());
    insert_m(this->user_ind, this->user_gc, user);
    delete user;
    std::cout << "Successfully added" << std::endl;

}

void Menu::insertS() const
{
    int userId, visitId;
    std::string data, startTime, endTime;
    std::cin >> userId >> visitId >> data >> startTime >> endTime;
    Visit* visit = new Visit(visitId, data.data(), startTime.data(), endTime.data());
    insert_s(this->user_ind, this->visit_gc, visit, userId);
    delete visit;
    std::cout << "Successfully added" << std::endl;
}

void Menu::calcM() const
{
    std::cout << calc_m(this->user_ind) << std::endl;
}

void Menu::calcS() const
{
    int userId;
    std::cin >> userId;
    calc_s(this->user_ind, userId);
}

void Menu::utM()
{
    ut_m(std::cout);
}

void Menu::utS()
{
    ut_s(std::cout);
}

void Menu::help()
{
    help_get_m();
    help_get_s();

    help_del_m();
    help_del_s();

    help_update_m();
    help_update_s();

    help_insert_m();
    help_insert_s();

    help_calc_m();
    help_calc_s();

    help_ut_m();
    help_ut_s();
}

void Menu::help_get_m()
{
    std::cout << "get_m <UserID>\n";
}

void Menu::help_get_s()
{
    std::cout << "get_s <UserID> <VisitID>\n";
}

void Menu::help_del_m()
{
    std::cout << "del_m <UserID>\n";
}

void Menu::help_del_s()
{
    std::cout << "del_s <UserID> <VisitID>\n";
}

void Menu::help_update_m()
{
    std::cout << "update_m <UserID> <phone> <fullname> <birthDay[DDMMYYYY]>\n";
}

void Menu::help_update_s()
{
    std::cout << "update_s <UserID> <VisitID> <date> <startTime[HHMM]> <endTime[HHMM]>\n";
}

void Menu::help_insert_m()
{
    std::cout << "insert_m <UserID> <phone> <fullName> <birthDay[DDMMYYYY]>\n";
}

void Menu::help_insert_s()
{
    std::cout << "insert_s <UserID> <VisitID> <date> <startTime[HHMM]> <endTime[HHMM]>\n";
}

void Menu::help_calc_m()
{
    std::cout << "calc_m\n";
}

void Menu::help_calc_s()
{
    std::cout << "calc_s <UserID>\n";
}

void Menu::help_ut_m()
{
    std::cout << "ut_m\n";
}

void Menu::help_ut_s()
{
    std::cout << "ut_s\n";
}