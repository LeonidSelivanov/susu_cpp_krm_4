#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

enum Platform
{
    PC,
    MOBILE,
    GAMEPAD
};

struct GenreSet
{
    bool rpg;
    bool strategy;
    bool racing;
    bool simulator;
    bool shooter;
    bool action;
    bool adventure;
    bool puzzle;
};

struct Game
{
    char title[50];
    char studio[50];
    float sub_cost;
    int audience;
    Platform platform;
    GenreSet genres;
};

bool compareByPlatform(const Game& a, const Game& b)
{
    return a.platform > b.platform;
}

bool compareByCostDesc(const Game& a, const Game& b)
{
    return a.sub_cost < b.sub_cost;
}

bool compareByAudience(const Game& a, const Game& b)
{
    return a.audience > b.audience;
}

void bubbleSort(Game arr[], int size, bool (*comp)(const Game&, const Game&))
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (comp(arr[j], arr[j + 1]))
            {
                Game temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

bool hasSimulator(const GenreSet& gs)
{
    return gs.simulator;
}

bool hasStrategy(const GenreSet& gs)
{
    return gs.strategy;
}

void printGenres(const GenreSet& gs)
{
    cout << "Жанры: ";
    if (gs.rpg) cout << "RPG ";
    if (gs.strategy) cout << "Стратегия ";
    if (gs.racing) cout << "Гонки ";
    if (gs.simulator) cout << "Симулятор ";
    if (gs.shooter) cout << "Шутер ";
    if (gs.action) cout << "Экшен ";
    if (gs.adventure) cout << "Приключения ";
    if (gs.puzzle) cout << "Головоломка ";
    cout << endl;
}

void init(Game games[])
{
    Game temp[20] =
    {
        {"FlightSim X", "AeroSoft", 59.99f, 1500000, PC, {false, false, false, true, false, false, false, false}},
        {"War Thunder", "Gaijin", 0.0f, 12000000, PC, {false, false, false, true, true, true, false, false}},
        {"DCS World", "Eagle", 79.99f, 500000, PC, {false, false, false, true, false, true, false, false}},
        {"X-Plane 12", "Laminar", 59.99f, 2000000, PC, {false, false, false, true, false, false, false, false}},
        {"Star Citizen", "CIG", 45.0f, 3500000, PC, {true, false, false, true, true, true, true, false}},
        {"Starcraft 2", "Blizzard", 0.0f, 5000000, PC, {false, true, false, false, false, false, false, false}},
        {"Civ VI", "Firaxis", 59.99f, 8000000, PC, {false, true, false, false, false, false, false, false}},
        {"Age of Empires 4", "Relic", 39.99f, 4000000, PC, {false, true, false, false, false, false, false, false}},
        {"Candy Crush", "King", 0.0f, 250000000, MOBILE, {false, false, false, false, false, false, false, true}},
        {"Clash of Clans", "Supercell", 0.0f, 150000000, MOBILE, {false, true, false, false, false, false, false, false}},
        {"Need for Speed", "EA", 69.99f, 3000000, PC, {false, false, true, false, false, true, false, false}},
        {"Forza Horizon 5", "Playground", 59.99f, 20000000, PC, {false, false, true, false, false, true, true, false}},
        {"Mario Kart", "Nintendo", 59.99f, 50000000, GAMEPAD, {false, false, true, false, false, true, false, false}},
        {"Witcher 3", "CDPR", 39.99f, 40000000, PC, {true, false, false, false, false, true, true, false}},
        {"Skyrim", "Bethesda", 39.99f, 30000000, PC, {true, false, false, false, false, true, true, false}},
        {"Doom Eternal", "id", 39.99f, 10000000, PC, {false, false, false, false, true, true, false, false}},
        {"COD MW2", "Activision", 69.99f, 25000000, PC, {false, false, false, false, true, true, false, false}},
        {"PUBG Mobile", "Tencent", 0.0f, 1000000000, MOBILE, {false, false, false, false, true, true, false, false}},
        {"Angry Birds", "Rovio", 0.0f, 500000000, MOBILE, {false, false, false, true, false, false, false, true}},
        {"Real Flight", "Horizon", 99.99f, 1500000, PC, {false, false, false, true, false, false, false, false}}
    };
    for (int i = 0; i < 20; ++i)
    {
        games[i] = temp[i];
    }
}

void filterSimulators(Game games[], int size, Game result[], int& res_size)
{
    res_size = 0;
    for (int i = 0; i < size; ++i)
    {
        if (hasSimulator(games[i].genres) && games[i].audience >= 1000000)
        {
            result[res_size++] = games[i];
        }
    }
}

void printGame(const Game& g)
{
    cout << "Название: " << g.title << endl;
    cout << "Студия: " << g.studio << endl;
    cout << "Стоимость: " << g.sub_cost << endl;
    cout << "Аудитория: " << g.audience << endl;
    cout << "Платформа: ";
    if (g.platform == PC)
    {
        cout << "PC";
    }
    else if (g.platform == MOBILE)
    {
        cout << "Mobile";
    }
    else
    {
        cout << "Gamepad";
    }
    cout << endl;
    printGenres(g.genres);
    cout << "------------------------" << endl;
}

void printByTitle(Game games[], int size, const char* title)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(games[i].title, title) == 0)
        {
            printGame(games[i]);
            return;
        }
    }
    cout << "Игра не найдена." << endl;
}

void printTop3Expensive(Game games[], int size)
{
    Game sorted[20];
    for (int i = 0; i < size; ++i) sorted[i] = games[i];
    bubbleSort(sorted, size, compareByCostDesc);
    cout << "Топ 3 самых дорогих игр:" << endl;
    int limit = (size < 3) ? size : 3;
    for (int i = 0; i < limit; ++i)
    {
        printGame(sorted[i]);
    }
}

void changeGame(Game games[], int size, const char* title)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(games[i].title, title) == 0)
        {
            strcpy_s(games[i].studio, "New Studio Inc.");
            games[i].sub_cost = 19.99f;
            games[i].audience = 2500000;
            games[i].platform = PC;
            games[i].genres.rpg = false;
            games[i].genres.strategy = true;
            games[i].genres.racing = false;
            games[i].genres.simulator = false;
            games[i].genres.shooter = false;
            games[i].genres.action = false;
            games[i].genres.adventure = false;
            games[i].genres.puzzle = false;
            cout << "Игра обновлена." << endl;
            return;
        }
    }
    cout << "Игра для обновления не найдена." << endl;
}

void filterPCStrategy(Game games[], int size, Game result[], int& res_size)
{
    res_size = 0;
    for (int i = 0; i < size; ++i)
    {
        if (hasStrategy(games[i].genres) && games[i].platform == PC)
        {
            result[res_size++] = games[i];
        }
    }
}

void printFiltered(Game arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printGame(arr[i]);
    }
}

void readBinaryGames(const char* filename, Game games[], int& size)
{
    ifstream in(filename, ios::binary | ios::in);
    if (!in.is_open())
    {
        size = 0;
        return;
    }
    size = 0;
    while (in.read((char*)&games[size], sizeof(Game)))
    {
        size++;
    }
    in.close();
}

void writeBinaryGames(const char* filename, Game games[], int size)
{
    ofstream out(filename, ios::binary | ios::out);
    if (!out.is_open()) return;
    for (int i = 0; i < size; ++i)
    {
        out.write((char*)&games[i], sizeof(Game));
    }
    out.close();
}

void readTextCosts(const char* filename, Game games[], int size)
{
    ifstream fin(filename);
    if (!fin.is_open()) return;
    char title[50];
    float cost;
    while (fin >> title >> cost)
    {
        for (int i = 0; i < size; ++i)
        {
            if (strcmp(games[i].title, title) == 0)
            {
                games[i].sub_cost = cost;
                break;
            }
        }
    }
    fin.close();
}

int main()
{
    setlocale(LC_ALL, "");

    Game games[20];
    init(games);

    Game sims[20];
    int sims_count = 0;
    filterSimulators(games, 20, sims, sims_count);
    bubbleSort(sims, sims_count, compareByPlatform);

    cout << "Отфильтрованные и отсортированные симуляторы с аудиторией более 1 миллиона:" << endl;
    printFiltered(sims, sims_count);

    cout << "\nПоиск игры DCS World:" << endl;
    printByTitle(games, 20, "DCS World");

    cout << "\nТоп 3 самых дорогих игр:" << endl;
    printTop3Expensive(games, 20);

    cout << "\nИзменение игры DCS World:" << endl;
    changeGame(games, 20, "DCS World");
    printByTitle(games, 20, "DCS World");

    Game strats[20];
    int strats_count = 0;
    filterPCStrategy(games, 20, strats, strats_count);
    cout << "\nОтфильтрованные стратегии для PC:" << endl;
    printFiltered(strats, strats_count);

    writeBinaryGames("games.dat", games, 20);

    Game loaded[20];
    int loaded_count = 0;
    readBinaryGames("games.dat", loaded, loaded_count);

    cout << "\nЗагружено из бинарного файла:" << endl;
    for (int i = 0; i < loaded_count; ++i)
    {
        printGame(loaded[i]);
    }

    ofstream costFile("costs.txt");
    costFile << "FlightSim X 99.99\n";
    costFile << "DCS World 89.99\n";
    costFile << "Witcher 3 49.99\n";
    costFile.close();

    readTextCosts("costs.txt", loaded, loaded_count);

    cout << "\nПосле обновления стоимости из текстового файла:" << endl;
    printGame(loaded[0]);
    printGame(loaded[2]);
    printGame(loaded[13]);

    return 0;
}
