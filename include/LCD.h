#pragma once
#include <vector>
#include "WiFiNetwork.h"

void initDisplay();
void displayNetworks(std::vector<WiFiNetwork>& nets);
void displayCounter(int counter);