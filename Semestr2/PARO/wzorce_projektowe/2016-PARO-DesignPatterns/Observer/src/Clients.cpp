#include <Clients.hpp>
#include <iostream>


Chart::Chart(Database &db)
    :database(db)
{
	id = database.observer.subscribe(std::bind(&Chart::plot, this));
}

Chart::~Chart()
{
	database.observer.unsubscribe(id);
}

Calculator::Calculator(Database &db)
    :database(db)
{
	database.observer.subscribe(std::bind(&Calculator::recalculate, this));
}

Calculator::~Calculator()
{
	database.observer.unsubscribe(id);
}

EmailSender::EmailSender(Database &db)
    :database(db)
{
	database.observer.subscribe(std::bind(&EmailSender::send, this));
}

EmailSender::~EmailSender()
{
	database.observer.unsubscribe(id);
}

void Calculator::recalculate()
{
    std::cout << "Calculator::recalculate()   " << database.getData("calculator") << "\n";
}

void EmailSender::send()
{
    std::cout << "EmailSender::send()   " << database.getData("email") << "\n";
}

void Chart::plot()
{
    std::cout << "Chart::plot()   " << database.getData("chart") << "\n";
}
