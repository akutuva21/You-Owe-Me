#include "../headers/Interface.h"

const int WINDOW_HEIGHT = 900;
const int WINDOW_WIDTH = 1000;

void GenerateInterface()
{
    // Load Font
    sf::Font font;
    font.loadFromFile("./assets/fonts/Segoe_UI.ttf");
    // Creates window object
    Interface window(WINDOW_WIDTH, WINDOW_HEIGHT, "You Owe Me");
    // All objects within the window
    // Logo Background
    // window.AddTextBox("LogoBack", make_pair(0.35, 0), make_pair(0.3, 0.1), "", font, 0, false);
    // Images
    window.AddSprite("IRS Logo", "IRS_Logo", make_pair(0.5, 0.05), make_pair(0.07, 0.075));
    window.AddSprite("WallStreetBets", "WallStreetBets", make_pair(0.12, 0.95), make_pair(0.65, 0.65));
    window.AddSprite("Green Arrow", "Green_Arrow", make_pair(0.535, 0.385), make_pair(0.08, 0.08));
    window.AddSprite("Dollar Sign", "Dollar_Sign", make_pair(0.745, 0.385), make_pair(0.12, 0.12));
    window.AddSprite("Background", "Background", make_pair(0.5, 0.5), make_pair(2.5, 2.5));
    // Load TextBoxes/Buttons
    // Import
    window.AddTextBox("ImportTitle", make_pair(0.05, 0.2), make_pair(0.4, 0.075), "Input Transactions File Path Here:", font);
    window.AddTextBox("Import", make_pair(0.450, 0.2), make_pair(0.425, 0.075), "", font, 3);
    window.AddTextBox("ImportButton", make_pair(0.9, 0.2), make_pair(0.082, 0.075), "Import", font, 3, false, true);
    // Insert Edges
    window.AddTextBox("AddButton", make_pair(0.9, 0.35), make_pair(0.082, 0.075), " Insert", font, 3, false, true);
    window.AddTextBox("AddEdgeTitle", make_pair(0.05, 0.35), make_pair(0.3, 0.075), "Add a New Transaction:", font);
    window.AddTextBox("AddEdge1", make_pair(0.355, 0.35), make_pair(0.15, 0.075), "", font, 3);
    window.AddTextBox("AddEdge2", make_pair(0.565, 0.35), make_pair(0.15, 0.075), "", font, 3);
    window.AddTextBox("AddEdgeAmount", make_pair(0.775, 0.35), make_pair(0.1, 0.075), "", font, 3);
    // Simplify, Leaderboard, Export
    window.AddTextBox("SimplifyButton", make_pair(0.15, 0.5), make_pair(0.1, 0.075), "Simplify", font, 3, false, true);
    window.AddTextBox("LeaderboardButton", make_pair(0.39, 0.5), make_pair(0.22, 0.075), " View Leaderboards", font, 3, false, true);
    window.AddTextBox("Export", make_pair(0.75, 0.5), make_pair(0.1, 0.075), "  Export", font, 3, false, true);

    // Displays window
    window.GenerateWindow();
}

int main()
{
    GenerateInterface();
    return 0;
}
