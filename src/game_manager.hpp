#pragma once
#include "queue_manager.hpp"
#include "includes.hpp"


class GameManager
{
public:
    GameManager(){};
    void Update();
    void DeleteCurrent();
    void ReInstantiate();
private:
    bool game_over = true;
    bool first_time = false;
    Playfield playfield = Playfield(20);
    QueueManager *queue_manager = new QueueManager(playfield);
};


