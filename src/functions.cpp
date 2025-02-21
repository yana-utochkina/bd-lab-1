#include "functions.h"

#include <fstream>
#include <sstream>

std::string dateToString(const char* d)
{
    std::ostringstream oss;
    oss << d[0] << d[1] << '.' << d[2] << d[3] << '.' << d[4] << d[5] << d[6] << d[7];
    return oss.str();
}

std::string timeToString(const char* t)
{
    std::ostringstream oss;
    oss << t[0] << t[1] << ':' << t[2] << t[3];
    return oss.str();
}

std::string phoneNumberToString(const char* p)
{
    std::ostringstream oss;
    oss << p[0] << p[1] << p[2] << '-' << p[3] << p[4] << p[5] << '-' << p[6] << p[7] << '-' << p[8] << p[9];
    return oss.str();
}

int get_m(User* user, IndexTable* indexTable, int key)
{
    std::fstream file;
    openFile(file, USERS_FL_PATH);

    int row = indexTable->get_address(key);
    seekToUsersRow(file, row, 1);
    user->Load(file);

    file.close();
    return row;
}

int get_s(Visit* visit, IndexTable* indexTable, int m_key, int s_id)
{
    User* user = new User();
    get_m(user, indexTable, m_key);

    std::fstream file;
    openFile(file, VISITS_FL_PATH);
    seekToVisitsRow(file, user->firstVisitAdress, 1);

    int visitAdress = user->firstVisitAdress;
    for (int i = 0; i < user->sizeOfVisits; i++)
    {
        visit->Load(file);
        if (visit->id == s_id) break;
        if (i < user->firstVisitAdress - 1)
        {
            seekToUsersRow(file, visit->nextAddress, 1);
            visitAdress = visit->nextAddress;
        }
    }

    if (visit->id != s_id)
    {
        throw std::invalid_argument("Invalid Visit id");
    }

    file.close();
    delete user;
    return visitAdress;
}

void update_m(User* user, IndexTable* indexTable, int key)
{
    User* tempUser = new User();
    get_m(tempUser, indexTable, key);

    user->id = tempUser->id;
    user->firstVisitAdress = tempUser->firstVisitAdress;
    user->sizeOfVisits = tempUser->sizeOfVisits;

    std::fstream file;
    openFile(file, USERS_FL_PATH);
    seekToUsersRow(file, indexTable->get_address(key), 1);
    user->Save(file);

    delete tempUser;
}

void update_s(Visit* visit, IndexTable* indexTable, int m_key, int s_id)
{
    Visit* tempVisit = new Visit();
    int visitAddress = get_s(tempVisit, indexTable, m_key, s_id);

    visit->id = tempVisit->id;
    visit->prevAddress = tempVisit->prevAddress;
    visit->nextAddress = tempVisit->nextAddress;

    std::fstream file;
    openFile(file, VISITS_FL_PATH);
    seekToVisitsRow(file, visitAddress, 1);
    visit->Save(file);

    delete tempVisit;
}

void insert_m(IndexTable* indexTable, GarbageCollector* users_gc, User* user)
{
    std::fstream file;
    bool empty = isEmptyFile(USERS_FL_PATH);
    openFile(file, USERS_FL_PATH);

    int userAddress;
    int address = 0;

    // If file is empty then write to the beginning of file 'Index after end' as 0
    if (empty)
    {
        userAddress = 0;
        file.write(reinterpret_cast<char*>(&address), sizeof(int));
        file.seekg(0, std::ios::beg);
    }

    // Read 'Index after end'
    file.read(reinterpret_cast<char*>(&address), sizeof(int));
    // Checking whether GarbageCollector is empty
    if (users_gc->isEmpty())
    {
        userAddress = address;
        address++;

        file.seekp(0, std::ios::beg);
        file.write(reinterpret_cast<char*>(&address), sizeof(int)); // Incrementing 'Index after end'
        file.seekp(0, std::ios::end); // Seek to the end
    }
    else
    {
        userAddress = users_gc->pop_first();  // Getting optimal address to store
        seekToUsersRow(file, userAddress);
    }
    indexTable->add(user->id, userAddress);

    markAsAdded(file);

    user->firstVisitAdress = -1;
    user->sizeOfVisits = 0;

    user->Save(file);
    file.close();
}

void insert_s(IndexTable* indexTable, GarbageCollector* visits_gc, Visit* visit, int key)
{
    User* user = new User();
    get_m(user, indexTable, key);

    std::fstream file_s;
    bool empty = isEmptyFile(VISITS_FL_PATH);
    openFile(file_s, VISITS_FL_PATH);

    int visitAddress;
    int address = 0;

    // If file is empty then write to the beginning of file 'Index after end' as 0
    if (empty)
    {
        visitAddress = 0;
        file_s.write(reinterpret_cast<char*>(&address), sizeof(int));
        file_s.seekg(0, std::ios::beg);
    }

    // Read 'Index after end'
    file_s.read(reinterpret_cast<char*>(&address), sizeof(int));
    // Checking whether GarbageCollector is empty
    if (visits_gc->isEmpty())
    {
        visitAddress = address;
        address++;

        file_s.seekp(0, std::ios::beg);
        file_s.write(reinterpret_cast<char*>(&address), sizeof(int));
        file_s.seekp(0, std::ios::end);
    }
    else
    {
        visitAddress = visits_gc->pop_first();
        seekToVisitsRow(file_s, visitAddress);
    }

    markAsAdded(file_s);
    int prevVisitAddress = user->firstVisitAdress;
    visit->prevAddress = -1;
    visit->nextAddress = prevVisitAddress;
    visit->Save(file_s);

    seekToVisitsRow(file_s, prevVisitAddress, 1);
    visit->Load(file_s);
    visit->prevAddress = visitAddress;
    seekToVisitsRow(file_s, prevVisitAddress, 1);
    visit->Save(file_s);
    file_s.close();

    user->firstVisitAdress = visitAddress;
    user->sizeOfVisits++;

    std::fstream file_m;
    openFile(file_m, USERS_FL_PATH);
    seekToUsersRow(file_m, indexTable->get_address(key));
    markAsAdded(file_m);
    user->Save(file_m);
    file_m.close();

    delete user;
}

void del_m(GarbageCollector* user_gc, GarbageCollector* visit_gc, IndexTable* indexTable, int key)
{
    User* user = new User();
    get_m(user, indexTable, key);
    int userAddress = indexTable->get_address(key);

    std::fstream file_m;
    openFile(file_m, USERS_FL_PATH);
    seekToUsersRow(file_m, userAddress);
    markAsDeleted(file_m);

    Visit* visit = new Visit();

    std::fstream file_s;
    openFile(file_s, VISITS_FL_PATH);
    seekToVisitsRow(file_s, user->firstVisitAdress, 1);

    int size = user->sizeOfVisits;

    for (int i = 0; i < size; i++)
    {
        visit->Load(file_s);
        del_s(visit_gc, indexTable, key, visit->id);
        seekToVisitsRow(file_s, visit->nextAddress, 1);
    }

    indexTable->remove(key);
    user_gc->add(userAddress);
    delete user;
    delete visit;
}

void del_s(GarbageCollector* visit_gc, IndexTable* indexTable, int m_key, int s_key)
{
    Visit* visit = new Visit();
    get_s(visit, indexTable, m_key, s_key);

    std::fstream file_s;
    openFile(file_s, VISITS_FL_PATH);

    Visit* nextVisit = new Visit();
    Visit* prevVisit = new Visit();
    int visitAddress;

    User *user = new User();
    get_m(user, indexTable, m_key);

    if (visit->nextAddress != -1 && visit->prevAddress != -1)
    {
        seekToVisitsRow(file_s, visit->nextAddress, 1);
        nextVisit->Load(file_s);

        seekToVisitsRow(file_s, visit->prevAddress, 1);
        prevVisit->Load(file_s);

        visitAddress = prevVisit->nextAddress;
        prevVisit->nextAddress = visit->nextAddress;
        nextVisit->prevAddress = visit->prevAddress;

        seekToVisitsRow(file_s, visit->prevAddress, 1);
        prevVisit->Save(file_s);

        seekToVisitsRow(file_s, visit->nextAddress, 1);
        nextVisit->Save(file_s);

        seekToVisitsRow(file_s, visitAddress);
        markAsDeleted(file_s);
        // Change info in master file
        user->sizeOfVisits--;
    }
    else if (visit->nextAddress == -1 && visit->prevAddress != -1)
    {
        seekToVisitsRow(file_s, visit->prevAddress, 1);
        prevVisit->Load(file_s);

        visitAddress = prevVisit->nextAddress;
        prevVisit->nextAddress = -1;

        seekToVisitsRow(file_s, visit->prevAddress, 1);
        prevVisit->Save(file_s);

        seekToVisitsRow(file_s, visitAddress);
        markAsDeleted(file_s);
        // Change info in master file
        user->sizeOfVisits--;
    }
    else if (visit->nextAddress != -1 && visit->prevAddress == -1)
    {
        seekToVisitsRow(file_s, visit->nextAddress, 1);
        nextVisit->Load(file_s);

        visitAddress = nextVisit->prevAddress;
        nextVisit->prevAddress = -1;

        seekToVisitsRow(file_s, visit->nextAddress, 1);
        nextVisit->Save(file_s);

        seekToVisitsRow(file_s, visitAddress);
        markAsDeleted(file_s);

        // Change info in master file
        user->sizeOfVisits--;
        user->firstVisitAdress = visit->nextAddress;
    }
    else if (visit->nextAddress == -1 && visit->prevAddress == -1)
    {
        visitAddress = user->firstVisitAdress;
        seekToVisitsRow(file_s, user->firstVisitAdress);
        markAsDeleted(file_s);

        user->sizeOfVisits = 0;
        user->firstVisitAdress = -1;
    }
    std::fstream file_m;
    openFile(file_m, USERS_FL_PATH);
    seekToUsersRow(file_m, indexTable->get_address(m_key), 1);
    user->Save(file_m);
    file_m.close();

    delete user;
    delete nextVisit;
    delete prevVisit;

    visit_gc->add(visitAddress);
}

std::ostream& ut_m(std::ostream& os) {
    std::fstream file;
    openFile(file, USERS_FL_PATH);

    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));
    os << "Index of next after end record: " << size << std::endl;
    os << "______________________________________" << std::endl;

    User* user = new User();

    char isExist;
    for (int i = 0; i < size; i++)
    {
        file.read(&isExist, sizeof(char));
        os << "Exist: " << isExist << std::endl;
        user->Load(file);
        os << "Index of first Visit in Visits.fl: " << user->firstVisitAdress << std::endl;
        os << "Size of Visits records: " << user->sizeOfVisits << std::endl;
        os << *user;
        os << "________________________________________" << std::endl;
    }

    delete user;
    return os;
}

std::ostream& ut_s(std::ostream& os) {
    std::fstream file;
    openFile(file, VISITS_FL_PATH);

    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));
    os << "Index of next after end record: " << size << std::endl;
    os << "______________________________________" << std::endl;

    Visit* visit = new Visit();

    char isExist;
    for (int i = 0; i < size; i++)
    {
        file.read(&isExist, sizeof(char));
        os << "Exist: " << isExist << std::endl;
        visit->Load(file);
        os << "Address of previous visit: " << visit->prevAddress << std::endl;
        os << "Address of next visit: " << visit->nextAddress << std::endl;
        os << *visit;
        os << "________________________________________" << std::endl;
    }

    delete visit;
    return os;
}

int calc_m(IndexTable* indexTable)
{
    return indexTable->indexMap.size();
}

int calc_s(IndexTable* indexTable, int key)
{
    User* user = new User();

    get_m(user, indexTable, key);

    return user->sizeOfVisits;
}