#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class AnimationSystem {
public:
    static void loadingDots(int count = 3, int speed = 200) {
        for(int i = 0; i < count; i++) {
            cout << "." << flush;
            sleep_for(milliseconds(speed));
        }
        cout << endl;
    }

    static void shimmerText(const string& text, int iterations = 2) {
        for(int i = 0; i < iterations; i++) {
            cout << "\r" << text << " *" << flush;
            sleep_for(milliseconds(100));
            cout << "\r" << text << "  " << flush;
            sleep_for(milliseconds(100));
        }
        cout << "\r" << text << endl;
    }

    static void fadeIn(const string& text, int stepDelay = 20) {
        for(size_t i = 0; i <= text.length(); i++) {
            cout << "\r" << text.substr(0, i) << flush;
            sleep_for(milliseconds(stepDelay));
        }
        cout << endl;
    }

    static void typewriter(const string& text, int speed = 30, bool newline = true) {
        for(char c : text) {
            cout << c << flush;
            sleep_for(milliseconds(speed + (rand() % 10)));
        }
        if(newline) cout << endl;
    }

    static void pulseBorder(int width = 60, int height = 3, int pulses = 3) {
        for(int p = 0; p < pulses; p++) {
            clearScreen();
            string border(width, '#');
            cout << "\n" << border << endl;
            for(int h = 0; h < height; h++) {
                cout << "#" << string(width-2, ' ') << "#" << endl;
            }
            cout << border << endl;
            sleep_for(milliseconds(200));

            clearScreen();
            border = string(width, '=');
            cout << "\n" << border << endl;
            for(int h = 0; h < height; h++) {
                cout << "=" << string(width-2, ' ') << "=" << endl;
            }
            cout << border << endl;
            sleep_for(milliseconds(200));
        }
    }

    static void progressBar(const string& label, int duration = 2000, int width = 40) {
        cout << "\n" << label << " [";
        for(int i = 0; i < width; i++) {
            cout << "=" << flush;
            sleep_for(milliseconds(duration/width));
        }
        cout << "] 100%" << endl;
    }

    static void explodeText(const string& text) {
        vector<string> fragments = {"*", "+", "!", "~"};
        string temp = text;

        for(int i = 0; i < 5; i++) {
            clearScreen();
            cout << "\n\n";
            for(char c : temp) {
                if(rand() % 3 == 0) {
                    cout << fragments[rand() % fragments.size()] << " ";
                } else {
                    cout << c << " ";
                }
            }
            cout << endl;
            sleep_for(milliseconds(100));
        }
        clearScreen();
        cout << "\n\n" << text << endl;
    }

    static void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    static void slideIn(const string& text, int speed = 20) {
        int width = 60;
        int spaces = -static_cast<int>(text.length());

        for(int i = 0; i < width; i++) {
            clearScreen();
            cout << string(abs(spaces), ' ') << text << flush;
            spaces++;
            sleep_for(milliseconds(speed));
        }
        cout << endl;
    }

    static void printCentered(const string& text) {
        int width = 60;
        int padding = (width - text.length()) / 2;
        if (padding < 0) padding = 0;
        cout << string(padding, ' ') << text << endl;
    }
};

class Anitom {
private:
    map<string, bool> flags;
    map<string, int> counters;
    map<string, string> relationships;
    vector<string> journalEntries;
    string protagonistName;

public:
    Anitom(string name = "Robert") : protagonistName(name) {
        initializeCoreMetrics();
    }

    void initializeCoreMetrics() {
        flags["isMerciful"] = false;
        flags["romanticPathActive"] = false;
        flags["injuredSeverely"] = false;
        flags["tacticalMastery"] = false;
        flags["publicHero"] = false;
        flags["underworldRespected"] = false;

        counters["blazerAffinity"] = 0;
        counters["heroReputation"] = 5;
        counters["villainFear"] = 0;
        counters["moralBalance"] = 0;
        counters["combatEfficiency"] = 0;
        counters["dispatchReadiness"] = 0;

        relationships["blondeBlazer"] = "neutral";
        relationships["flambae"] = "neutral";
        relationships["soothingGoon"] = "unknown";
        relationships["dispatchHQ"] = "pending";
    }

    void setFlag(string flagName, bool value) {
        flags[flagName] = value;
        AnimationSystem::shimmerText("[SYSTEM] Flag updated: " + flagName);
    }

    bool getFlag(string flagName) {
        return flags.count(flagName) ? flags[flagName] : false;
    }

    void adjustCounter(string counterName, int delta, int minVal = -100, int maxVal = 100) {
        if (counters.count(counterName)) {
            counters[counterName] += delta;
            counters[counterName] = min(max(counters[counterName], minVal), maxVal);

            string arrow = delta > 0 ? "UP" : "DOWN";
            AnimationSystem::typewriter("[STAT] " + counterName + " " + arrow + " " + to_string(abs(delta)), 15);
        }
    }

    int getCounter(string counterName) {
        return counters.count(counterName) ? counters[counterName] : 0;
    }

    void setRelationship(string character, string state) {
        relationships[character] = state;
        AnimationSystem::typewriter("[RELATIONSHIP] " + character + " -> " + state, 20);
    }

    string getRelationship(string character) {
        return relationships.count(character) ? relationships[character] : "unknown";
    }

    void addJournalEntry(string entry) {
        string timestamp = "[" + getCurrentTime() + "] ";
        journalEntries.push_back(timestamp + entry);

        AnimationSystem::loadingDots(1, 100);
        cout << "> Journal updated" << endl;
    }

    void displayJournal() {
        AnimationSystem::pulseBorder(50, 2, 1);
        cout << "\n          MISSION JOURNAL\n" << endl;
        for (const auto& entry : journalEntries) {
            AnimationSystem::typewriter("  * " + entry, 10);
        }
        AnimationSystem::typewriter("\n  Total entries: " + to_string(journalEntries.size()), 20);
    }

    string calculateAlignment() {
        if (counters["moralBalance"] >= 3) return "Paragon";
        if (counters["moralBalance"] <= -3) return "Renegade";
        return "Pragmatist";
    }

    string calculateHeroStyle() {
        if (flags["tacticalMastery"] && flags["isMerciful"]) return "Strategic Guardian";
        if (flags["tacticalMastery"] && !flags["isMerciful"]) return "Calculated Enforcer";
        if (!flags["tacticalMastery"] && flags["isMerciful"]) return "Compassionate Defender";
        return "Brutal Enforcer";
    }

private:
    string getCurrentTime() {
        return "22:45";
    }
};

class GameUI {
public:
    static void displaySceneHeader(const string& title) {
        AnimationSystem::clearScreen();

        string border = "============================================================";
        AnimationSystem::printCentered(border);
        AnimationSystem::printCentered("  " + title + "  ");
        AnimationSystem::printCentered(border);

        cout << endl;

        sleep_for(milliseconds(500));
    }

    static void displayStats(Anitom& anitom) {
        cout << "\n+-------------------[ STATUS ]-------------------+" << endl;
        cout << "| " << left << setw(20) << "Alignment:" << anitom.calculateAlignment() << " |" << endl;
        cout << "| " << left << setw(20) << "Style:" << anitom.calculateHeroStyle() << " |" << endl;
        cout << "| " << left << setw(20) << "Blazer:" << anitom.getRelationship("blondeBlazer") << " |" << endl;

        int moral = anitom.getCounter("moralBalance");
        string moralBar = getBar(moral, 10);
        cout << "| Moral: " << moralBar << " |" << endl;

        int rep = anitom.getCounter("heroReputation");
        string repBar = getBar(rep, 10);
        cout << "| Rep:   " << repBar << " |" << endl;

        cout << "+-------------------------------------------------+" << endl;
    }

    static int displayChoices(const vector<string>& choices, const string& prompt = "Choose your action:") {
        AnimationSystem::typewriter("\n" + prompt, 25);

        cout << "\n+==============================================+" << endl;
        for (size_t i = 0; i < choices.size(); i++) {
            string number = "[" + to_string(i+1) + "] ";
            cout << "| " << left << setw(40) << (number + choices[i]) << " |" << endl;
        }
        cout << "+==============================================+" << endl;

        cout << "\n-> Enter choice (1-" << choices.size() << "): ";

        int choice;
        while(!(cin >> choice) || choice < 1 || choice > (int)choices.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            AnimationSystem::typewriter("Invalid input! Please enter 1-" + to_string(choices.size()) + ": ", 20, false);
        }

        AnimationSystem::typewriter("Selected: " + choices[choice-1], 15);
        AnimationSystem::loadingDots(3, 100);

        return choice;
    }

    static void sceneTransition(const string& from, const string& to) {
        AnimationSystem::clearScreen();
        AnimationSystem::progressBar("Transitioning: " + from + " -> " + to, 1500);
        sleep_for(milliseconds(300));
    }

private:
    static string getBar(int value, int maxWidth) {
        int width = (abs(value) * maxWidth) / 10;
        width = min(max(width, 0), maxWidth);

        string bar;
        if(value >= 0) {
            bar = string(width, '#') + string(maxWidth - width, '.');
        } else {
            bar = string(maxWidth - width, '.') + string(width, '#');
        }

        return bar + " " + (value >= 0 ? "+" : "") + to_string(value);
    }
};

Anitom storyEngine;

void scene_interrogation() {
    GameUI::displaySceneHeader("APARTMENT INTERROGATION");

    AnimationSystem::slideIn("RAIN PATTERS AGAINST THE WINDOW");
    AnimationSystem::typewriter("\nThe Soothing Goon's fingers slip on the wet railing.", 35);
    AnimationSystem::typewriter("Fourteen stories below, the city twinkles indifferently.", 35);

    AnimationSystem::typewriter("\nGOON: 'I'LL TALK! I SWEAR! PLEASE!'", 30);
    AnimationSystem::typewriter("His eyes are wide with primal fear.", 35);

    GameUI::displayStats(storyEngine);

    vector<string> choices = {
        "Pull him to safety - Show mercy",
        "Let him fall - Make an example",
        "Demand more information first",
        "Signal for police extraction"
    };

    int choice = GameUI::displayChoices(choices, "What does Robert do?");

    switch(choice) {
        case 1:
            AnimationSystem::typewriter("\nYour grip tightens. Muscles strain.", 30);
            AnimationSystem::typewriter("With one powerful heave, you haul him over the railing.", 30);
            AnimationSystem::typewriter("He collapses, gasping like a landed fish.", 30);

            AnimationSystem::shimmerText("MERCY ACTIVATED");
            storyEngine.setFlag("isMerciful", true);
            storyEngine.adjustCounter("moralBalance", 3);
            storyEngine.addJournalEntry("Saved Soothing Goon. Gained valuable intel on EMP devices.");
            break;

        case 2:
            AnimationSystem::typewriter("\nYou maintain eye contact.", 40);
            AnimationSystem::typewriter("His grip fails finger by finger.", 40);
            AnimationSystem::typewriter("The scream fades into the storm.", 40);

            AnimationSystem::explodeText("RUTHLESS REPUTATION ESTABLISHED");
            storyEngine.setFlag("isMerciful", false);
            storyEngine.adjustCounter("villainFear", 4);
            storyEngine.addJournalEntry("Eliminated Soothing Goon. Message sent to underworld.");
            break;
    }

    AnimationSystem::progressBar("Processing consequences", 1000);
}

void scene_street_fight() {
    GameUI::sceneTransition("Apartment", "Dark Alley");
    GameUI::displaySceneHeader("ALLEY AMBUSH");

    AnimationSystem::typewriter("\nThe smell hits first: wet garbage and ozone.", 35);
    AnimationSystem::typewriter("Shadows detach from shadows. Two against one.", 35);

    cout << "\n";
    AnimationSystem::slideIn("THUG 1: 'BOSS SAID MAKE IT HURT'");

    AnimationSystem::typewriter("\nCrowbar glints under flickering neon.", 35);
    AnimationSystem::typewriter("Taser crackles with blue-white energy.", 35);

    vector<string> choices = {
        "Right cross - Direct and powerful",
        "Low sweep - Technical takedown",
        "Improvised weapon - Use environment",
        "Feign injury - Tactical deception"
    };

    if(storyEngine.getCounter("dispatchReadiness") > 2) {
        choices.push_back("Signal Dispatch - Coordinate response");
    }

    int choice = GameUI::displayChoices(choices, "Combat analysis:");

    bool success = (rand() % 100) < (70 + storyEngine.getCounter("combatEfficiency"));

    if(choice == 1) {
        if(success) {
            AnimationSystem::typewriter("\nFist meets jaw with satisfying CRUNCH.", 30);
            AnimationSystem::typewriter("Second thug hesitates. Opening created.", 30);
            storyEngine.adjustCounter("combatEfficiency", 2);
        } else {
            AnimationSystem::typewriter("\nFEINT! The crowbar arcs toward your ribs-", 25);
            AnimationSystem::typewriter("\n*** CRACK ***", 100);
            AnimationSystem::typewriter("\nWhite-hot pain. Something breaks.", 40);

            AnimationSystem::pulseBorder(60, 3, 2);
            AnimationSystem::typewriter("\nINJURY TRACKING...", 100);
            AnimationSystem::progressBar("Damage assessment", 2000);

            storyEngine.setFlag("injuredSeverely", true);
            storyEngine.adjustCounter("dispatchReadiness", 4);
            storyEngine.addJournalEntry("Sustained critical injury in alley fight.");
        }
    }
    else if(choice == 5 && choices.size() > 4) {
        AnimationSystem::typewriter("\n'Dispatch, alley on 5th. Two hostiles. Armed.'", 30);
        AnimationSystem::typewriter("Sirens approach in perfect sync.", 30);
        AnimationSystem::typewriter("Professional. Efficient. The future.", 40);

        storyEngine.adjustCounter("dispatchReadiness", 3);
        storyEngine.addJournalEntry("First successful field coordination with Dispatch.");
    }

    sleep_for(seconds(2));
}

void scene_bar_flambae() {
    GameUI::sceneTransition("Alley", "The Incognito Bar");
    GameUI::displaySceneHeader("THE INCOGNITO BAR");

    AnimationSystem::typewriter("\nSmoke, laughter, the clink of glasses.", 35);
    AnimationSystem::typewriter("A sanctuary where masks come off.", 40);

    cout << "\n";
    AnimationSystem::slideIn("FLAMBAE: 'AND THEN I SAID- OH CRAP!'");

    AnimationSystem::typewriter("\nHer hair erupts in crimson flames.", 30);
    AnimationSystem::typewriter("Panic ripples through the crowd.", 30);
    AnimationSystem::typewriter("All eyes turn to you.", 40);

    GameUI::displayStats(storyEngine);

    vector<string> choices = {
        "Water pitcher - Practical solution",
        "Fire blanket - Bar safety protocol",
        "Premium whiskey - 'Go big or go home'",
        "Distract with story - Psychological approach"
    };

    if(storyEngine.getCounter("heroReputation") > 6) {
        choices.push_back("Command authority - Take control");
    }

    int choice = GameUI::displayChoices(choices, "Crisis response:");

    switch(choice) {
        case 1:
            AnimationSystem::typewriter("\nWater meets fire with a dramatic HISS.", 30);
            AnimationSystem::typewriter("Steam clouds the room. Problem solved.", 30);
            storyEngine.adjustCounter("blazerAffinity", 1);
            break;

        case 3:
            AnimationSystem::typewriter("\nYou grab the 25-year-old Scotch.", 30);
            AnimationSystem::typewriter("'If we're burning, let's make it expensive!'", 30);

            AnimationSystem::loadingDots(5, 100);
            AnimationSystem::explodeText("WHOOSH! FIREBALL!");

            AnimationSystem::typewriter("\nThe entire bar erupts in cheers.", 30);
            AnimationSystem::typewriter("Flambae takes a dramatic bow, flames dancing.", 30);

            AnimationSystem::shimmerText("LEGEND BORN");
            storyEngine.adjustCounter("blazerAffinity", 4);
            storyEngine.setFlag("publicHero", true);
            storyEngine.addJournalEntry("Created legendary bar moment with Flambae.");
            break;
    }

    AnimationSystem::typewriter("\nBlonde Blazer watches from her corner.", 40);
    AnimationSystem::typewriter("Martini glass tilted in silent appraisal.", 40);

    int affinity = storyEngine.getCounter("blazerAffinity");
    if(affinity >= 8) storyEngine.setRelationship("blondeBlazer", "Admiring");
    else if(affinity >= 5) storyEngine.setRelationship("blondeBlazer", "Interested");

    sleep_for(seconds(1));
}

void scene_billboard() {
    GameUI::sceneTransition("Bar", "City Rooftops");
    GameUI::displaySceneHeader("BILLBOARD HEIGHTS");

    AnimationSystem::typewriter("\nThe city breathes below you.", 50);
    AnimationSystem::typewriter("A thousand lights like scattered diamonds.", 50);
    AnimationSystem::typewriter("Wind whispers secrets between buildings.", 50);

    AnimationSystem::typewriter("\nBLONDE BLAZER: 'Remember when everything felt possible?'", 40);
    AnimationSystem::typewriter("Her shoulder brushes yours. Electricity arcs.", 40);
    AnimationSystem::typewriter("Not metaphorical. Literal static discharge.", 40);

    bool highTension = storyEngine.getCounter("blazerAffinity") >= 5;

    vector<string> choices = {
        "Lean in - Seize the moment",
        "Step back - Professional distance",
        "Make a joke - Defuse tension",
        "Share truth - Vulnerability"
    };

    if(highTension) {
        choices.push_back("Let her lead - Follow her cues");
    }

    int choice = GameUI::displayChoices(choices, "The moment stretches:");

    if(choice == 1) {
        AnimationSystem::typewriter("\nDistance closes.", 80);
        AnimationSystem::typewriter("Lips meet.", 100);
        AnimationSystem::typewriter("The city holds its breath.", 120);

        AnimationSystem::shimmerText("ROMANTIC PATH ACTIVATED");

        AnimationSystem::typewriter("\nShe pulls back, breathless.", 40);
        AnimationSystem::typewriter("'About damn time, Robert.'", 40);

        storyEngine.setFlag("romanticPathActive", true);
        storyEngine.adjustCounter("blazerAffinity", 5);
        storyEngine.addJournalEntry("Shared kiss with Blonde Blazer on billboard.");
    }
    else if(choice == 5 && highTension) {
        AnimationSystem::typewriter("\nYou wait.", 100);
        AnimationSystem::typewriter("She closes the distance.", 80);
        AnimationSystem::typewriter("Her kiss tastes like lightning and regret.", 60);

        AnimationSystem::explodeText("CONNECTION ESTABLISHED");

        storyEngine.setFlag("romanticPathActive", true);
        storyEngine.adjustCounter("blazerAffinity", 6);
    }

    AnimationSystem::progressBar("Processing emotional data", 1500);
}

void scene_combat_toxic() {
    GameUI::sceneTransition("Rooftop", "Industrial District");
    GameUI::displaySceneHeader("TOXIC'S LAIR");

    AnimationSystem::typewriter("\nChemical stench burns your nostrils.", 35);
    AnimationSystem::typewriter("Vats bubble with neon-green sludge.", 35);
    AnimationSystem::typewriter("Toxic lies defeated in his own poison.", 40);

    cout << "\n";
    AnimationSystem::slideIn("TOXIC: 'FINISH IT! OR ARE YOU TOO NOBLE?'");

    AnimationSystem::typewriter("\nHe spits acid that sizzles on concrete.", 35);
    AnimationSystem::typewriter("Final move. What defines you?", 50);

    GameUI::displayStats(storyEngine);

    vector<string> choices = {
        "Punt into sewer - Creative disposal",
        "Stomp into ground - Brutal finality",
        "Neutralize chemically - Scientific approach",
        "Call containment - Dispatch protocol"
    };

    if(storyEngine.getFlag("romanticPathActive")) {
        choices.push_back("Signal Blazer - Coordinated finish");
    }

    int choice = GameUI::displayChoices(choices, "Finishing move:");

    switch(choice) {
        case 1:
            AnimationSystem::typewriter("\nYou line up the shot.", 40);
            AnimationSystem::typewriter("'Fore!'", 30);

            AnimationSystem::loadingDots(3, 200);
            AnimationSystem::typewriter("\n*THWOCK*", 100);
            AnimationSystem::typewriter("Toxic sails through the air.", 40);
            AnimationSystem::typewriter("*SPLASH*", 150);
            AnimationSystem::typewriter("Silence.", 200);

            storyEngine.adjustCounter("heroReputation", 2);
            break;

        case 5:
            AnimationSystem::typewriter("\n'Blazer, execute pincer. Now.'", 30);
            AnimationSystem::typewriter("She drops from the ceiling.", 40);
            AnimationSystem::typewriter("Perfect synchronization.", 50);

            AnimationSystem::shimmerText("PERFECT TEAMWORK");

            AnimationSystem::typewriter("\nShe winks as Toxic is contained.", 40);
            AnimationSystem::typewriter("'Not bad for an old guy.'", 40);

            storyEngine.adjustCounter("blazerAffinity", 3);
            storyEngine.adjustCounter("dispatchReadiness", 3);
            break;
    }

    AnimationSystem::progressBar("Mission completion", 2000);
}

void epilogue_summary() {
    GameUI::sceneTransition("Field", "Dispatch HQ");
    GameUI::displaySceneHeader("SIX MONTHS LATER");

    AnimationSystem::typewriter("\nThe command center hums with quiet energy.", 40);
    AnimationSystem::typewriter("Monitors display city sectors.", 40);
    AnimationSystem::typewriter("Hero deployments. Crisis alerts.", 40);
    AnimationSystem::typewriter("Your city. Your responsibility.", 50);

    AnimationSystem::pulseBorder(60, 4, 1);

    cout << "\n";
    AnimationSystem::slideIn("FINAL ASSESSMENT REPORT");
    cout << "\n";

    string style = storyEngine.calculateHeroStyle();
    string alignment = storyEngine.calculateAlignment();
    bool romantic = storyEngine.getFlag("romanticPathActive");
    bool injured = storyEngine.getFlag("injuredSeverely");
    int readiness = storyEngine.getCounter("dispatchReadiness");

    AnimationSystem::typewriter("\n* Hero Classification: " + style, 25);
    AnimationSystem::typewriter("* Moral Alignment: " + alignment, 25);
    AnimationSystem::typewriter("* Dispatch Readiness: " + to_string(readiness) + "/10", 25);

    cout << "\n";
    AnimationSystem::printCentered("------------------------------");
    cout << "\n";

    if(romantic) {
        AnimationSystem::typewriter("\nPERSONAL NOTE:", 30);
        AnimationSystem::typewriter("Blonde Blazer requested permanent field liaison position.", 25);
        AnimationSystem::typewriter("Coffee appears on your desk every morning.", 30);
        AnimationSystem::typewriter("Extra shot. Just how you like it.", 40);

        AnimationSystem::shimmerText("PARTNERSHIP ACTIVE");
    }

    if(injured) {
        AnimationSystem::typewriter("\nMEDICAL ASSESSMENT:", 30);
        AnimationSystem::typewriter("Field work no longer viable.", 40);
        AnimationSystem::typewriter("The injury forced the pivot.", 50);
        AnimationSystem::typewriter("But from this chair...", 60);
        AnimationSystem::typewriter("...you save more lives.", 80);
    }

    cout << "\n";
    AnimationSystem::printCentered("------------------------------");
    cout << "\n";

    AnimationSystem::typewriter("\nHEADLINE ANALYSIS:", 30);
    if(storyEngine.getFlag("isMerciful")) {
        AnimationSystem::typewriter("'From Street Hero to Compassionate Commander'", 25);
        AnimationSystem::typewriter("- The Herald, front page", 30);
    } else {
        AnimationSystem::typewriter("'Fear the Man Behind the Screens'", 25);
        AnimationSystem::typewriter("- Underworld graffiti analysis", 30);
    }

    AnimationSystem::progressBar("Generating career projection", 2500);

    cout << "\n";
    AnimationSystem::explodeText("THE PIVOT COMPLETE");

    if(romantic && readiness >= 8 && storyEngine.getCounter("heroReputation") >= 9) {
        cout << "\n";
        AnimationSystem::pulseBorder(50, 3, 3);
        AnimationSystem::typewriter("\n* ULTIMATE ENDING: PERFECT BALANCE *", 30);
        AnimationSystem::typewriter("Love. Command. Purpose.", 50);
        AnimationSystem::typewriter("You became the hero the city needed most.", 40);
    }

    cout << "\nView mission journal? (y/n): ";
    char choice;
    cin >> choice;
    if(tolower(choice) == 'y') {
        storyEngine.displayJournal();
    }

    AnimationSystem::typewriter("\n\nThank you for playing ROBERT'S PIVOT", 30);
    AnimationSystem::loadingDots(5, 200);
}

void titleSequence() {
    AnimationSystem::clearScreen();

    vector<string> titleArt = {
        " _____   ____   _____   _____   _______   _____  ",
        "|  __ \\ |  _ \\ |  __ \\ |_   _| |__   __| / ____| ",
        "| |__) || |_) || |__) |  | |      | |   | (___  ",
        "|  _  / |  _ < |  _  /   | |      | |    \\___ \\ ",
        "| | \\ \\ | |_) || | \\ \\  _| |_     | |    ____) |",
        "|_|  \\_\\|____/ |_|  \\_\\|_____|    |_|   |_____/ "
    };

    for(const auto& line : titleArt) {
        AnimationSystem::fadeIn(line, 5);
    }

    sleep_for(seconds(1));

    AnimationSystem::printCentered("ROBERT'S PIVOT: EPISODE 1");
    AnimationSystem::typewriter("\nA Dispatch Visual Novel Experience\n", 40);

    AnimationSystem::progressBar("Initializing ANITOM System", 2000);

    cout << "\nPress Enter to begin your transformation...";
    cin.ignore();
    cin.get();
}

int main() {
    srand(time(0));

    titleSequence();

    storyEngine = Anitom("Robert");

    scene_interrogation();
    scene_street_fight();
    scene_bar_flambae();
    scene_billboard();
    scene_combat_toxic();
    epilogue_summary();

    AnimationSystem::clearScreen();

    vector<string> credits = {
        "ANITOM System v2.3 - Narrative Engine",
        "Dynamic Choice Architecture",
        "Relationship State Machine",
        "Real-time Consequence Tracking",
        "",
        "Created for Dispatch Universe",
        "",
        "Your journey continues in",
        "Episode 2: 'Lines of Command'"
    };

    for(const auto& line : credits) {
        AnimationSystem::printCentered(line);
        sleep_for(milliseconds(300));
    }

    AnimationSystem::typewriter("\n\n", 100);
    AnimationSystem::loadingDots(10, 150);

    return 0;
}
