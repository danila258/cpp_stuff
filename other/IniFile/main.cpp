#include "IniFile.h"

int main()
{
    IniFile cfg("../config.ini");

    assert(cfg.read<bool>("general", "fullscreen") == true);

    assert(cfg.read<std::string>("player", "name") == "John Doe");
    assert(cfg.read<int>("player", "x") == 100);
    assert(cfg.read<int>("player", "y") == 200);

    assert(cfg.read<int>("player", "z") == 0);
    assert(cfg.read<int>("player", "z", 500) == 500);

    assert(cfg.sectionExists("general") == true);
    assert(cfg.sectionExists("player") == true);
    assert(cfg.sectionExists("AAAAAA") != true);

    assert(cfg.keyExists("general", "windowWidth") == true);
    assert(cfg.keyExists("general", "windowHeight") == true);
    assert(cfg.keyExists("general", "windowDepth") == false);
    assert(cfg.keyExists("asdasdadasd", "windowWidth") == false);

    std::vector<std::string> a = { "general", "player" };
    cfg.sections() == a;

    std::vector<std::string> b = {"windowWidth", "windowHeight", "fullscreen"};
    cfg.keys("general") == b;

    cfg.write<std::string>("player", "name", "Ivan Petrov Vasilevish");
    cfg.write<bool>("player", "bool", true);
    cfg.write<int>("newSection", "value", 137);
    cfg.save();

    return 0;
}
