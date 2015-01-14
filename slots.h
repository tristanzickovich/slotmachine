#ifndef SLOTS_H
#define SLOTS_H

class slots
{
    private:
        string welcome;
        int tokens;
        int wager;
        int slotOne;
        int slotTwo;
        int slotThree;
        string oneFruit;
        string twoFruit;
        string threeFruit;
        
        void spin();
        void roundOutcome();
        void wagerSetup();
        string spinTOfruit(int x);
        void spinOutput();
    
    public:
        slots();
        void run_slots();
    
};

#endif
