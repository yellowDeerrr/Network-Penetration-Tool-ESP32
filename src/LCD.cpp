#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiNetwork.h>
#include <vector>
#include <Menu.h>

uint8_t arrow[8] = {0x00, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00}; //Send 0,4,6,1F,6,4,0 for the arrow

LiquidCrystal_I2C lcd(0x27, 20, 4);

void initDisplay(){
    Wire.begin(41, 42);

    lcd.init();           // Initialize LCD
    lcd.backlight();      // Turn on backlight

    lcd.createChar(0, arrow);

    lcd.setCursor(0, 0);
    lcd.write(0);

    lcd.setCursor(1, 0);
    lcd.print("Scan Networks");
    lcd.setCursor(1, 2);
}

bool displayingNetworks = false;

void displayNetworks(std::vector<WiFiNetwork>& nets){
    lcd.clear();

    if (nets.empty()) {
        lcd.setCursor(0, 0);
        lcd.print("No networks found");
        return;
    }

    lcd.setCursor(0, 0);
    lcd.printf("Found: %d", nets.size());

    for(int i = 0; i < 3; i++){
        lcd.setCursor(1, i + 1);
        lcd.printf("%s", nets[i].ssid);
    }    
    displayingNetworks = true;
}

void displayCounter(int counter){
    if(displayingNetworks) return;

    lcd.setCursor(0, 1);
    lcd.print("Count: ");
    lcd.print(counter);
    lcd.print("   ");
}


// void drawMainMenu(String menuItems[], int currentScreen, int currentPointedMenuItem){
//     lcd.clear();
//     for(int i = 0; i < 4; i++){
//         lcd.setCursor(1, i);
//         lcd.printf(menuItems[i].c_str());
//     }

//     lcd.setCursor(0, currentPointedMenuItem);
//     lcd.write(0);
// }


// void count