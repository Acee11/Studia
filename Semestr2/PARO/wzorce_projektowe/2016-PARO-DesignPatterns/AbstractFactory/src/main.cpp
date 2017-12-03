#include <iostream>
#include <GnomeWidgetsFactory.hpp>
#include <WindowsWidgetsFactory.hpp>
#include <KdeWidgetsFactory.hpp>
#include <UnsupportedSystemException.hpp>
#include <Display.hpp>
#include <algorithm>


inline void printHelp()
{
    std::cout << "Usage: ./AbstractFactory [WINDOWS|GNOME|KDE]\n";
}

//Hi! I've just added a Gnome widgets. Help me to support this GUI

inline std::string getSystemName(const char** argv)
{
    std::string systemName(argv[1]);
    return systemName;
}

int main(int argc, const char** argv)
try
{
    if(argc != 2) { printHelp(); return 1; }

    const std::string system = getSystemName(argv);
    std::shared_ptr<WidgetsFactory> widgetsFactory;
    if(system == "WINDOWS")
        widgetsFactory = std::shared_ptr<WidgetsFactory>(new WindowsWidgetsFactory);
    else if(system == "GNOME")
        widgetsFactory = std::shared_ptr<WidgetsFactory>(new GnomeWidgetsFactory);
    else if(system == "KDE")
        widgetsFactory = std::shared_ptr<WidgetsFactory>(new KdeWidgetsFactory);
    else
        throw UnsupportedSystem(system);
    Display display(widgetsFactory);
    display.display();

    return 0;
}
catch(const UnsupportedSystem& e)
{
    std::cout << "Unsupported system: " << e.getSystemName() << std::endl;
    printHelp();
}

