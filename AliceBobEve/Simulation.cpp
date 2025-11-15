#include <semaphore>
#include <array>
#include <thread>
#include "MathHelper.h"
#include "ECHelper.h"

#include "EC.h"

enum class Sender { Alice, Bob };

ostream& operator<<(ostream& os, const Sender& sender) {
    os << (sender == Sender::Alice ? "Alice" : "Bob") << "\n";
    return os;
}

struct Message {
    Sender sender = Sender::Alice;
    string text;
};

ostream& operator<<(ostream& os, const Message& msg) {
    os << "-------------------\n";
    os << "From: " << msg.sender;
    os << "Text: " << msg.text << "\n";
    os << "-------------------\n";
    return os;
}

struct Simulation {
    string simulation_name;
    EC curve = EC();
    LL n;
    Point g = {curve};

    counting_semaphore<1> semAlice;
    counting_semaphore<1> semEve;
    counting_semaphore<1> semBob;

    mutex mailboxMutex;
    Message mailbox;
    void curve_init() {
        array<LL, 2> factored{};
        while (factored[0] == 0) {
            curve = EC();
            LL curve_order = find_order(curve);
            factored = factor(curve_order);
        }
        g = find_generator(curve, factored);
        n = factored[1];
    }

    Simulation() : semAlice(1), semBob(0), semEve(0) {
        curve_init();
    }

    void run() {
        cout << simulation_name << " start\n\n";

        thread tA(&Simulation::alice, this);
        thread tE(&Simulation::eve, this);
        thread tB(&Simulation::bob, this);

        tA.join();
        tE.join();
        tB.join();

        cout << "\n" << simulation_name << " end\n";
    }

    virtual void alice() {}
    virtual void bob() {}
    virtual void eve() {}
};
