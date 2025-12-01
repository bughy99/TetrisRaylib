#pragma once
#include "queue_manager.hpp"
#include "includes.hpp"


class GameManager
{
public:
    GameManager(){};
    void Update();
private:
    Playfield playfield = Playfield(20);
    QueueManager queue_manager = QueueManager(playfield);
};


