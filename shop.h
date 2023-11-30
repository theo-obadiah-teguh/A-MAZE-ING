#include "plotting.h"
#include <string>
#include <iostream>
#ifndef SHOP_H
#define SHOP_H

// Function to handle different purchase requests from players
void purchaseOptions(int & monsterHunt, int & monsterCount, playerObject & player);

// Function to direct player to the shop and ask for purchase options
void visitShop(int & monsterHunt, int & monsterCount, playerObject & player, string exitPoint);

#endif
