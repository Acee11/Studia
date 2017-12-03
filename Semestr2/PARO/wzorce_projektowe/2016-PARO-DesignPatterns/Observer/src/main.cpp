#include <Clients.hpp>
#include <Database.hpp>

int main()
{
    Database database;

    Chart chart(database);
    Calculator calculator(database);

    {
        EmailSender emailSender(database);

        database.changeData("top sectret");
    }

    database.changeData("other sectret"); // what is wrong with this code?
                                            // I expect to no email sending, but application crashed... ;(

}
