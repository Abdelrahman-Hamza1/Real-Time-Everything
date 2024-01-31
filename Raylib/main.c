#include <raylib.h>


typedef struct MESSAGEGUI{
  long msgtype;
  int customerId;
  int cashierId;
  int val;
  int sentBy; // 0 = cashier, 1 = customer
  int flag; //  0 = nothing , 1 = leaving 
} MessageGui;

typedef struct Ents{
  int id;
  int total;
  int queue;
} Entity;

int main(void) {

  int screenWidth = 800;
  int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Supermarket");
  
  Entity customers[100];
  Entity cashiers[100];
  int customerCounter = 4, cashierCounter = 8;

  for (int i = 0 ; i < customerCounter ; i++){
    Entity ent;
    ent.id = i;
    ent.queue = 5555;
    ent.total = -10;
    customers[i] = ent; 
  }
  for (int i = 0 ; i < cashierCounter ; i++){
    Entity ent;
    ent.id = i;
    ent.queue = 5555;
    ent.total = -10;
    cashiers[i] = ent; 
  }  

  Color rectangleColor = SKYBLUE;
  Color textColor = BLACK;

  Font font = LoadFontEx("Arial", 20, 0, 0); 
  // const char *text = "Id = 1 1 1";
  // const char *text2 = "Id = 2 2 2";

  // Define rectangle position and size
  int width = 100;
  int height = 50;

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    /* LOGIC FOR RECIEVING MESSAGE!
    MessageGui msg; 

    if (msg.sentBy == 0){
      // cahsier sent msg 
      if(msg.flag == 1){
        // removal!
        removeEntry(cashiers,100,msg.cashierId);
        cashierCounter--;
        break;
      }
      else if (msg.flag == 2){
        // means im updating the total for some customer! -> find customer based off id and update cost!
        for (int i = 0; i < 100; i++){
          if(customers[i].id == msg.customerId){
            customers[i].total = msg.val;
            break;
          }
        }
        break;
      }
      else if (msg.flag == 0){ // addition!
        Entity ent;
        ent.id = msg.cashierId;
        ent.queue = msg.val;
        cashiers[cashierCounter] = ent;
        cashierCounter++;
      }
    }
    else if (msg.sentBy == 1){
      // customer sent msg 
      if(msg.flag == 1){
        // removal!
        removeEntry(customers,100,msg.customerId);
        customerCounter--;
        break;
      }
      else if (msg.flag == 0){
        Entity ent;
        ent.id = msg.customerId;
        customers[customerCounter] = ent;
        customerCounter++;
      }
      else if (msg.flag == 2){ // customer is setting his queue
        for (int i = 0; i < 100; i++){
          if(customers[i].id == msg.customerId){
            customers[i].queue = msg.val;
            break;
          }
        }
      }
    }
    */
    char **customerStrings = (char **)malloc(customerCounter * sizeof(char *));
    char **cashierStrings = (char **)malloc(cashierCounter * sizeof(char *));

    for (int i = 0; i < customerCounter; ++i) {
        customerStrings[i] = (char *)malloc(100);
        snprintf(customerStrings[i], 100, "id: %d, total: %d, queue: %d", customers[i].id, customers[i].total, customers[i].queue);
    }

    for (int i = 0; i < cashierCounter; ++i) {
        cashierStrings[i] = (char *)malloc(100);
        snprintf(cashierStrings[i], 100, "id: %d, total: %d, queue: %d", cashiers[i].id, cashiers[i].total, cashiers[i].queue);
    }


    if(customerCounter > 0){
      int baseX = 100;
      int baseY = 10;
      int stepSizeCustomer = 600 / customerCounter; // assuming 600 is constant & counter is always larger than 1. 
      for (int i = 0 ; i < customerCounter ; i++){
        /* FOR EACH CUSTOMER:  CALCULATE LOCATION &  PLACE IT WITH IT'S TEXT! */

          DrawRectangle(baseX, ( baseY  + stepSizeCustomer*(i+1)) % 600 , width, height, rectangleColor);
          int textWidth = MeasureTextEx(font, customerStrings[i], font.baseSize, 0).x;
          int textHeight = MeasureTextEx(font, customerStrings[i], font.baseSize, 0).y;
          DrawTextEx(font, customerStrings[i], (Vector2){baseX + (width - textWidth) / 2, ( baseY  + stepSizeCustomer*(i+1)) % 600  + (height - textHeight) / 2}, font.baseSize, 0.0f, textColor);
      }
    }

    if (cashierCounter > 0){
      int baseCASHX = 600;
      int baseCASHY = 10;
      int stepSizeCashier = 600 / cashierCounter; // assuming 600 is constant & counter is always larger than 1. 
      for (int i = 0 ; i < cashierCounter ; i++){
        /* FOR EACH CUSTOMER:  CALCULATE LOCATION &  PLACE IT WITH IT'S TEXT! */
          DrawRectangle(baseCASHX, ( baseCASHY  + stepSizeCashier*(i+1)) % 600 , width, height, rectangleColor);
          int textWidth2 = MeasureTextEx(font, cashierStrings[i], font.baseSize, 0).x;
          int textHeight2 = MeasureTextEx(font, cashierStrings[i], font.baseSize, 0).y;
          DrawTextEx(font, cashierStrings[i], (Vector2){baseCASHX + (width - textWidth2) / 2, ( baseCASHY  + stepSizeCashier*(i+1)) % 600  + (height - textHeight2) / 2}, font.baseSize, 0.0f, textColor);
      }
    }

    EndDrawing();
  }

  UnloadFont(font);
  CloseWindow();
  return 0;
}

void removeEntry(Entity arr[], int size, int entry) {
  int i;
  for (i = 0; i < size; ++i) {
    if (arr[i].id == entry) {
      break;
    }
  }

  if (i == size) {
    return; // Entry not found
  }

  for (int j = i + 1; j < size; ++j) {
    arr[j - 1] = arr[j];
  }
}