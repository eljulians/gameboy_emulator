#pragma once

class GameBoy;

class GPU {
    public:
        GPU(GameBoy& gameBoy);
    
    private:
        GameBoy& gameBoy;
};